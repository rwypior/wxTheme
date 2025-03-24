#include "wxt/menu.h"

#include <wx/wx.h>

#ifdef WXT_WINDOWS
#   include <dwmapi.h>
#   include <Uxtheme.h>
#   include <vsstyle.h>

#   pragma comment(lib, "uxtheme.lib")

namespace
{
    static HTHEME g_menuTheme = nullptr;
}
#endif

namespace wxt
{
    // Menu bar renderer
    
    MenuBar* MenuBar::MenuBarRenderer::currentMenuBar = nullptr;

    MenuBar::MenuBarRenderer::MenuBarRenderer(MenuBar* menubar)
    {
        currentMenuBar = menubar;
    }

    MenuBar::MenuBarRenderer::~MenuBarRenderer()
    {
        currentMenuBar = nullptr;
    }

    MenuBar* MenuBar::MenuBarRenderer::getCurrentMenuBar()
    {
        return currentMenuBar;
    }

    // Menu bar

    MenuBar::MenuBar()
        : wxMenuBar()
    {
        this->setup();
    }

    MenuBar::MenuBar(long style)
        : wxMenuBar(style)
    {
        this->setup();
    }

    MenuBar::MenuBar(size_t n, wxMenu* menus[], const wxString titles[], long style)
        : wxMenuBar(n, menus, titles, style)
    {
        this->setup();
    }

    Selector MenuBar::getSelector() const
    {
        return this->selector;
    }

    Selector MenuBar::getSelectorItem() const
    {
        return this->selectorItem;
    }

    bool MenuBar::Append(wxMenu* menu, const wxString& title)
    {
        Language& lang = Language::getInstance();

        bool res = wxMenuBar::Append(menu, title);
        this->createDictionary(menu);

        this->translateMenu(menu);

        return res;
    }

    void MenuBar::setup()
    {
        this->selector.type = MenuType;
        this->selectorItem.type = MenuItemType;

        this->Bind(wxtEVT_LANGUAGE_CHANGED, &MenuBar::eventLanguageChanged, this);
    }

    void MenuBar::createDictionary(wxMenu* menu)
    {
        this->menuDictionary[menu] = menu->GetTitle();

        for (auto& item : menu->GetMenuItems())
        {
            this->createDictionary(item);

            if (wxMenu* menu = item->GetSubMenu())
                this->createDictionary(menu);
        }
    }

    void MenuBar::createDictionary(wxMenuItem* menu)
    {
        this->menuItemDictionary[menu] = menu->GetItemLabel();
    }

    void MenuBar::translateMenu(wxMenu* menu)
    {
        // NOTE: menu->SetTitle doesn't work, it needs to be done this way

        for (size_t i = 0; i < this->GetMenuCount(); i++)
        {
            if (this->GetMenu(i) == menu)
            {
                this->SetMenuLabel(i, translate(this->menuDictionary[menu]));
            }
        }

        for (auto& item : menu->GetMenuItems())
        {
            wxString newLabel = this->menuItemDictionary[item];
            size_t tabpos = newLabel.find_first_of(wxT("\t"));
            if (tabpos == wxNOT_FOUND)
                newLabel = translate(newLabel);
            else
            {
                wxString label = newLabel.substr(0, tabpos);
                newLabel.erase(0, tabpos);
                newLabel = translate(label) + newLabel;
            }

            wxString translation = translate(newLabel);
            if (!translation.empty())
                item->SetItemLabel(translation);

            if (wxMenu* menu = item->GetSubMenu())
                this->translateMenu(menu);
        }

        if (this->GetHandle())
        {
            this->Update();
            this->UpdateMenus();
            this->UpdateWindowUI(wxUPDATE_UI_RECURSE);
        }

        if (this->IsAttached())
            this->Refresh();
    }

    void MenuBar::processLanguage()
    {
        for (size_t i = 0; i < this->GetMenuCount(); i++)
        {
            wxMenu* menu = this->GetMenu(i);
            this->translateMenu(menu);
        }
    }

    void MenuBar::eventLanguageChanged(LanguageEvent& event)
    {
        this->processLanguage();
    }

#ifdef WXT_WINDOWS
    // Menu theming

    void UAHDrawMenuNCBottomLine(HWND hWnd, MenuBar& menubar)
    {
        MENUBARINFO mbi = { sizeof(mbi) };
        if (!GetMenuBarInfo(hWnd, OBJID_MENU, 0, &mbi))
            return;

        RECT rcClient = { 0 };
        GetClientRect(hWnd, &rcClient);
        MapWindowPoints(hWnd, nullptr, (POINT*)&rcClient, 2);

        RECT rcWindow = { 0 };
        GetWindowRect(hWnd, &rcWindow);

        OffsetRect(&rcClient, -rcWindow.left, -rcWindow.top);

        RECT rc = rcClient;
        rc.bottom = rc.top;
        rc.top--;

        Theme& theme = Theme::getInstance();

        if (auto bg = theme.getBackgroundColor(menubar.getSelector()))
        {
            HBRUSH brush = CreateSolidBrush(bg->GetRGB());
            HDC hdc = GetWindowDC(hWnd);
            FillRect(hdc, &rc, brush);
            ReleaseDC(hWnd, hdc);
            DeleteObject(brush);
        }
    }

    bool UAHWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam, LRESULT* lr)
    {
        Theme& theme = Theme::getInstance();
        if (!theme.isEnabled())
            return false;

        MenuBar* menubar = MenuBar::MenuBarRenderer::getCurrentMenuBar();
        if (!menubar)
            return false;

        switch (message)
        {
        case WM_UAHDRAWMENU:
        {
            if (auto bg = theme.getBackgroundColor(menubar->getSelector()))
            {
                UAHMENU* pUDM = (UAHMENU*)lParam;

                MENUBARINFO mbi = { sizeof(mbi) };
                GetMenuBarInfo(hWnd, OBJID_MENU, 0, &mbi);

                RECT rcWindow;
                GetWindowRect(hWnd, &rcWindow);

                RECT rc = mbi.rcBar;
                OffsetRect(&rc, -rcWindow.left, -rcWindow.top);

                HBRUSH brush = CreateSolidBrush(bg->GetRGB());
                FillRect(pUDM->hdc, &rc, brush);
                DeleteObject(brush);
            }

            return true;
        }
        case WM_UAHDRAWMENUITEM:
        {
            UAHDRAWMENUITEM* pUDMI = (UAHDRAWMENUITEM*)lParam;

            HBRUSH bg;
            HBRUSH bgActive;
            HBRUSH bgSelected;

            auto fg = theme.getTextColor(menubar->getSelectorItem());
            auto fgDisabled = theme.getTextColor(menubar->getSelectorItem(), wxt::Theme::State::Disabled);

            if (auto colbg = theme.getBackgroundColor(menubar->getSelectorItem()))
                bg = CreateSolidBrush(colbg->GetRGB());
            else
                bg = CreateSolidBrush(GetSysColor(COLOR_MENU));

            if (auto colbgactive = theme.getBackgroundColor(menubar->getSelectorItem(), Theme::State::Active))
                bgActive = CreateSolidBrush(colbgactive->GetRGB());
            else
                bgActive = CreateSolidBrush(GetSysColor(COLOR_MENUHILIGHT));

            if (auto colbgselected = theme.getBackgroundColor(menubar->getSelectorItem(), Theme::State::Selected))
                bgSelected = CreateSolidBrush(colbgselected->GetRGB());
            else
                bgSelected = CreateSolidBrush(GetSysColor(COLOR_MENUHILIGHT));

            HBRUSH* currentBg = &bg;

            wchar_t text[256] = { 0 };
            MENUITEMINFO mii = { sizeof(mii), MIIM_STRING };
            mii.dwTypeData = text;
            mii.cch = (sizeof(text) / 2) - 1;
            GetMenuItemInfo(pUDMI->um.hmenu, pUDMI->umi.iPosition, TRUE, &mii);

            DWORD dwFlags = DT_CENTER | DT_SINGLELINE | DT_VCENTER;

            int iTextStateID = 0;
            int iBackgroundStateID = 0;
            if ((pUDMI->dis.itemState & ODS_INACTIVE) | (pUDMI->dis.itemState & ODS_DEFAULT))
            {
                // default
                iTextStateID = MPI_NORMAL;
                iBackgroundStateID = MPI_NORMAL;
            }

            if (pUDMI->dis.itemState & ODS_HOTLIGHT)
            {
                // hovered
                iTextStateID = MPI_HOT;
                iBackgroundStateID = MPI_HOT;

                currentBg = &bgActive;
            }

            if (pUDMI->dis.itemState & ODS_SELECTED)
            {
                // active
                iTextStateID = MPI_HOT;
                iBackgroundStateID = MPI_HOT;

                currentBg = &bgSelected;
            }

            if ((pUDMI->dis.itemState & ODS_GRAYED) || (pUDMI->dis.itemState & ODS_DISABLED))
            {
                // disabled
                iTextStateID = MPI_DISABLED;
                iBackgroundStateID = MPI_DISABLED;
            }

            if (pUDMI->dis.itemState & ODS_NOACCEL)
            {
                // No accelerator
                dwFlags |= DT_HIDEPREFIX;
            }

            if (!g_menuTheme)
                g_menuTheme = OpenThemeData(hWnd, L"Menu");

            FillRect(pUDMI->um.hdc, &pUDMI->dis.rcItem, *currentBg);

            DTTOPTS opts = { sizeof(opts), DTT_TEXTCOLOR,
                iTextStateID != MPI_DISABLED ?
                (fgDisabled ? fgDisabled->GetRGB() : GetSysColor(COLOR_GRAYTEXT)) :
                (fg ? fg->GetRGB() : GetSysColor(COLOR_MENUTEXT))
            };
            
            DrawThemeTextEx(g_menuTheme, pUDMI->um.hdc, MENU_BARITEM, MBI_NORMAL, text, mii.cch, dwFlags, &pUDMI->dis.rcItem, &opts);

            DeleteObject(bg);
            DeleteObject(bgActive);
            DeleteObject(bgSelected);

            return true;
        }
        case WM_UAHMEASUREMENUITEM:
        {
            UAHMEASUREMENUITEM* pMmi = (UAHMEASUREMENUITEM*)lParam;
            //pMmi->mis.itemWidth = (pMmi->mis.itemWidth * 4) / 3;

            *lr = DefWindowProc(hWnd, message, wParam, lParam);

            return true;
        }
        case WM_THEMECHANGED:
        {
            if (g_menuTheme)
            {
                CloseThemeData(g_menuTheme);
                g_menuTheme = nullptr;
            }
            return false;
        }
        case WM_NCPAINT:
        case WM_NCACTIVATE:
            *lr = DefWindowProc(hWnd, message, wParam, lParam);
            UAHDrawMenuNCBottomLine(hWnd, *menubar);
            return true;
        default:
            return false;
        }
    }
#endif
}
