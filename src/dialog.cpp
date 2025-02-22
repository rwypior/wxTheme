#include "wxt/dialog.h"
#include "wxt/menu.h"
#include "wxt/utils.h"

#include <dwmapi.h>

#include <wx/artprov.h>

namespace wxt
{
    // Aui helper

    bool AuiHelper::hasPane(const wxString& paneName)
    {
        return this->paneData.count(paneName);
    }

    AuiHelper::PaneData* AuiHelper::getPane(const wxString& paneName)
    {
        auto it = this->paneData.find(paneName);
        if (it != this->paneData.end())
            return &it->second;
        return nullptr;
    }

    AuiHelper::PaneData* AuiHelper::addPane(const wxString& paneName)
    {
        if (!this->hasPane(paneName))
            this->paneData[paneName] = {};

        return &this->paneData.at(paneName);
    }

    AuiHelper::PaneData* AuiHelper::addPane(wxAuiPaneInfo& pane)
    {
        PaneData* p = this->addPane(pane.name);

        p->hasCloseButton = pane.HasCloseButton();
        p->hasPinButton = pane.HasPinButton();

        pane.CloseButton(false);
        pane.PinButton(false);

        return p;
    }

    // Window

    Frame::Frame()
        : wxFrame()
    {
        this->setup();
    }

    Frame::Frame(wxWindow* parent,
        wxWindowID id,
        const wxString& title,
        const wxPoint& pos,
        const wxSize& size,
        long style,
        const wxString& name)
        : wxFrame(parent, id, title, pos, size, style, name)
    {
        this->setup();
    }

    Selector Frame::getSelector() const
    {
        return this->selector;
    }

    void Frame::setup()
    {
        this->selector.type = FrameType;

        this->defaultBackgroundColor = this->GetBackgroundColour();
        this->defaultTextColor = this->GetForegroundColour();

        this->titlebarSelector.type = TitlebarType;
        this->dockPanelHeaderSelector.type = DockPanelButtonType;
        this->dockPanelButtonSelector.type = DockPanelButtonType;

        this->Bind(wxtEVT_THEME_CHANGED, &Frame::eventThemeChanged, this);

        this->processTheme();
    }

    void Frame::enableAuiTheming(wxAuiManager& mgr)
    {
        mgr.Bind(wxEVT_AUI_RENDER, &Frame::eventAuiRender, this);
    }

    void Frame::enableStatusBarTheming(wxStatusBar* statusBar)
    {
        this->statusbarManager.registerStatusBar(statusBar);
        this->statusbarManager.setup();
    }

    void Frame::enableMenuBarTheming(MenuBar* menuBar)
    {
        this->themedMenu = menuBar;
    }

    Selector Frame::getTitlebarSelector() const
    {
        return this->titlebarSelector;
    }

    Selector Frame::getDockPanelHeaderSelector() const
    {
        return this->DockPanelHeaderType;
    }

    Selector Frame::getDockPanelButtonSelector() const
    {
        return this->DockPanelButtonType;
    }

    void Frame::processTheme()
    {
#ifdef WXT_WINDOWS
        BOOL themeEnabled = FALSE;

        Theme& theme = Theme::getInstance();
        if (theme.isEnabled() && theme.getMode(this->getTitlebarSelector()) == "dark")
        {
            themeEnabled = TRUE;
        }
        
        auto defaultbg = either(theme.getBackgroundColor(theme.getDefaultSelector()), this->defaultBackgroundColor);
        auto defaultfg = either(theme.getTextColor(theme.getDefaultSelector()), this->defaultTextColor);

        this->SetBackgroundColour(theme.isEnabled() ? either(theme.getBackgroundColor(this->getSelector()), defaultbg) : this->defaultBackgroundColor);
        this->SetForegroundColour(theme.isEnabled() ? either(theme.getTextColor(this->getSelector()), defaultfg) : this->defaultTextColor);

        this->statusbarManager.applyTheme();

        this->SetThemeEnabled(themeEnabled);
        DwmSetWindowAttribute(this->GetHWND(), DWMWA_USE_IMMERSIVE_DARK_MODE, &themeEnabled, sizeof(themeEnabled));
        
        this->Refresh();
        this->Update();

        updateNc();

        if (this->themedMenu)
        {
            this->themedMenu->Refresh();
            this->themedMenu->Update();
        }
#endif
    }

    void Frame::eventThemeChanged(ThemeEvent& event)
    {
        this->processTheme();
    }

    void Frame::eventAuiRender(wxAuiManagerEvent& event)
    {
        Theme& theme = Theme::getInstance();
        if (theme.isEnabled())
        {
            auto& dc = event.dc;

            std::optional<wxBrush> brush;
            std::optional<wxBrush> buttonBrush;
            std::optional<wxBrush> buttonBrushHovered;

            if (auto bg = theme.getBackgroundColor(this->dockPanelHeaderSelector))
                brush = wxBrush(*bg);

            if (auto bg = theme.getBackgroundColor(this->dockPanelButtonSelector))
                buttonBrush = wxBrush(*bg);

            if (auto bg = theme.getBackgroundColor(this->dockPanelHeaderSelector, Theme::State::Hover))
                buttonBrushHovered = wxBrush(*bg);

            if (auto fg = theme.getTextColor(this->dockPanelHeaderSelector))
                dc->SetTextForeground(*fg);

            wxAuiPaneInfoArray& panes = event.manager->GetAllPanes();
            for (unsigned int i = 0; i < panes.size(); i++)
            {
                wxAuiPaneInfo& pane = panes[i];

                const wxRect globalRect = pane.rect;
                const wxRect rect(wxPoint(0, 0), globalRect.GetSize());
                wxRect paneRect = pane.window->GetRect();

                int titleHeight = wxSystemSettings::GetMetric(wxSYS_CAPTION_Y, pane.window);
                wxPoint wtf = pane.window->GetClientAreaOrigin();

                int captionHeight = wxSystemSettings::GetMetric(wxSYS_CAPTION_Y, pane.window);
                int frameHeight = wxSystemSettings::GetMetric(wxSYS_FRAMESIZE_Y, pane.window) + 1;

                wxRect paneGlobalRect = paneRect;
                paneGlobalRect.x -= wxSystemSettings::GetMetric(wxSYS_FRAMESIZE_X, pane.window);
                paneGlobalRect.width += wxSystemSettings::GetMetric(wxSYS_FRAMESIZE_X, pane.window) * 2;
                paneGlobalRect.y -= captionHeight - frameHeight;
                paneGlobalRect.height += wxSystemSettings::GetMetric(wxSYS_CAPTION_Y, pane.window) + wxSystemSettings::GetMetric(wxSYS_BORDER_Y, pane.window);

                //int iconSpacingX = wxSystemSettings::GetMetric(wxSYS_ICONSPACING_X, pane.window);
                //int iconWidth = wxSystemSettings::GetMetric(wxSYS_SMALLICON_X, pane.window);
                //int iconHeight = wxSystemSettings::GetMetric(wxSYS_SMALLICON_Y, pane.window);

                //wxRegion reg(paneGlobalRect);
                //int buttonCount = pane.HasCloseButton() + pane.HasPinButton() + pane.HasMaximizeButton() + pane.HasMinimizeButton();
                //for (int i = 0; i < buttonCount; i++)
                //{
                //    wxRect buttonRect(paneRect.x + paneRect.width - iconWidth * (i + 1), paneRect.y - captionHeight + frameHeight, iconWidth, iconHeight);
                //    reg.Subtract(buttonRect);
                //}
                //
                //dc->SetDeviceClippingRegion(reg);

                if (brush)
                    dc->SetBrush(*brush);
                dc->DrawRectangle(paneGlobalRect);

                const wxString& caption = pane.caption;
                wxSize textSize = dc->GetTextExtent(caption);
                dc->DrawText(caption, wxPoint(paneRect.GetLeft() + wxSystemSettings::GetMetric(wxSYS_BORDER_X, pane.window), paneRect.GetTop() - titleHeight / 2 - textSize.y / 2));

                int iconSpacingX = wxSystemSettings::GetMetric(wxSYS_ICONSPACING_X, pane.window);
                int iconWidth = wxSystemSettings::GetMetric(wxSYS_SMALLICON_X, pane.window);
                int iconHeight = wxSystemSettings::GetMetric(wxSYS_SMALLICON_Y, pane.window);

                wxPoint mousePos = this->ScreenToClient(wxGetMousePosition());

                //MvAuiHelper::PaneData *panedata = this->auiHelper.addPane(pane);

                wxRect buttonRect(paneRect.x + paneRect.width - iconWidth, paneRect.y - captionHeight + frameHeight, iconWidth, iconHeight);
                if (buttonRect.Contains(mousePos))
                {
                    if (buttonBrushHovered)
                        dc->SetBrush(*buttonBrushHovered);
                }
                else
                {
                    if (buttonBrush)
                        dc->SetBrush(*buttonBrush);
                    dc->DrawRectangle(buttonRect);

                    dc->SetBrush(wxBrush(wxColour(255, 0, 0)));

                    wxBitmap bmp = wxArtProvider::GetBitmap(wxART_CROSS_MARK, wxART_BUTTON);
                    dc->DrawBitmap(bmp, buttonRect.GetX() + buttonRect.GetWidth() / 2 - bmp.GetWidth() / 2, buttonRect.GetY() + buttonRect.GetHeight() / 2 - bmp.GetHeight() / 2, true);
                }
            }
        }
        else
        {
            event.Skip();
        }
    }

#ifdef WXT_WINDOWS
    WXLRESULT Frame::MSWWindowProc(WXUINT message, WXWPARAM wParam, WXLPARAM lParam)
    {
        if (this->themedMenu)
        {
            MenuBar::MenuBarRenderer mbrender(themedMenu);
            LRESULT lr = 0;

            if (UAHWndProc(this->GetHWND(), message, wParam, lParam, &lr))
                return lr;
        }

        return wxFrame::MSWWindowProc(message, wParam, lParam);
    }

    void Frame::updateNc()
    {
        SendMessage(GetHWND(), WM_NCACTIVATE, FALSE, FALSE);
        SendMessage(GetHWND(), WM_NCACTIVATE, TRUE, FALSE);
    }
#endif

    // Dialog

    Dialog::Dialog(wxWindow* parent, wxWindowID id,
        const wxString& title,
        const wxPoint& pos,
        const wxSize& size,
        long style,
        const wxString& name)
        : wxDialog(parent, id, title, pos, size, style, name)
    {
        this->selector.type = DialogType;

        Theme& theme = Theme::getInstance();
        if (theme.isEnabled())
        {
            BOOL value = TRUE;
            DwmSetWindowAttribute(this->GetHWND(), DWMWA_USE_IMMERSIVE_DARK_MODE, &value, sizeof(value));
            this->Bind(wxEVT_PAINT, &Dialog::eventPaint, this);
        }
    }

    Selector Dialog::getSelector() const
    {
        return this->selector;
    }

    void Dialog::eventPaint(wxPaintEvent& event)
    {
        Theme& theme = Theme::getInstance();
        if (theme.isEnabled())
        {
            wxPaintDC dc(this);

            if (auto bg = theme.getBackgroundColor(this->getSelector(), Theme::State::Pressed))
                dc.SetBrush(wxBrush(*bg));

            wxSize size = dc.GetSize();

            dc.DrawRectangle(dc.GetSize());
        }
        else
        {
            event.Skip();
        }
    }

    wxRect Dialog::getInnerClientRect() const
    {
        wxPoint clientPos = -this->ScreenToClient(this->GetPosition());
        wxSize clientSize = this->GetClientSize();
        return wxRect(clientPos.x, clientPos.y, clientSize.x, clientSize.y);
    }

    wxRect Dialog::getOuterClientRect() const
    {
        wxSize windowSize = this->GetSize();
        return wxRect(0, 0, windowSize.x, windowSize.y);
    }

    wxRect Dialog::getTitlebarRect() const
    {
        wxPoint clientPos = -this->ScreenToClient(this->GetPosition());
        wxSize clientSize = this->GetClientSize();
        return wxRect(0, 0, clientSize.x, clientPos.y);
    }

    wxRect Dialog::getNcButtonRect(NcButton btn)
    {
        TITLEBARINFOEX ti{ 0 };
        ti.cbSize = sizeof(TITLEBARINFOEX);
        SendMessage(this->GetHWND(), WM_GETTITLEBARINFOEX, 0, reinterpret_cast<LPARAM>(&ti));

        int btnWidth = GetSystemMetrics(SM_CXSIZE);
        int btnHeight = GetSystemMetrics(SM_CYSIZE);
        int frameWidth = GetSystemMetrics(SM_CXFRAME);
        int frameHeight = GetSystemMetrics(SM_CYFRAME);
        if (!(ti.rgstate[static_cast<int>(btn)] & STATE_SYSTEM_INVISIBLE)) // !rect.IsEmpty())
        {
            wxRect outer = this->getOuterClientRect();
            return wxRect(
                wxPoint(outer.GetRight() - btnWidth - frameWidth, frameHeight),
                wxSize(btnWidth, btnHeight)
            );
        }
        return wxRect();
    }

    wxPoint Dialog::getNcPoint(wxPoint pt)
    {
        wxRect innerRect = this->getInnerClientRect();
        pt = ScreenToClient(pt);
        pt.x += innerRect.x;
        pt.y += innerRect.y;
        return pt;
    }

    //void Dialog::paintNc()
    //{
    //    wxWindowDC dc(this);
    //    
    //    wxRect windowRect = this->getOuterClientRect();
    //
    //    wxRegion reg(windowRect);
    //    reg.Subtract(this->getInnerClientRect());
    //
    //    dc.DestroyClippingRegion();
    //    dc.SetDeviceClippingRegion(reg);
    //
    //    wxColour frameColor;
    //    
    //    if (this->isActive)
    //        frameColor = wxColour(20, 20, 20, 255);
    //    else
    //        frameColor = wxColour(50, 50, 50, 255);
    //
    //    wxBrush brush(frameColor);
    //    dc.SetBrush(brush);
    //    
    //    dc.SetTextForeground(wxColour(200, 200, 200, 255));
    //
    //    dc.DrawRectangle(windowRect);
    //
    //    wxRect titlebarRect = this->getTitlebarRect();
    //    wxSize textSize = dc.GetTextExtent(this->GetLabel());
    //
    //    dc.DrawText(this->GetTitle(), wxPoint(10, titlebarRect.height / 2 - textSize.GetHeight() / 2));
    //
    //    wxRect closeRect = this->getNcButtonRect(NcButton::Close);
    //    if (!closeRect.IsEmpty())
    //    {
    //        wxColour closeButtonColor;
    //        if (this->closeButtonHovered)
    //            closeButtonColor = wxColour(255, 0, 0, 255);
    //        else
    //            closeButtonColor = frameColor;
    //
    //        wxBrush closebrush(closeButtonColor);
    //        dc.SetBrush(closebrush);
    //        dc.DrawRectangle(closeRect);
    //
    //        wxBitmap bmp;
    //        bool s = bmp.LoadFile("C:\\Users\\robwy\\Pictures\\icons\\close.png", wxBITMAP_TYPE_PNG);
    //        wxSize bmpSize = bmp.GetSize();
    //        float scale = static_cast<float>(closeRect.height) / static_cast<float>(bmpSize.y) * 0.5;
    //        wxBitmap::Rescale(bmp, bmpSize * scale);
    //        bmpSize = bmp.GetSize();
    //        dc.DrawBitmap(bmp, closeRect.GetTopLeft() + closeRect.GetSize() / 2 - bmpSize / 2);// wxPoint(500, 5));
    //        
    //        
    //        //bmp.SetMask()
    //    }
    //}
    //
    //void Dialog::closeButtonHover(bool hovered)
    //{
    //    bool needRedraw = hovered != this->closeButtonHovered;
    //    this->closeButtonHovered = hovered;
    //
    //    if (needRedraw)
    //        RedrawWindow(this->GetHWND(), NULL, NULL, RDW_FRAME | RDW_INVALIDATE | RDW_UPDATENOW);
    //}
    //
    //int Dialog::ncHitTest(wxPoint pt)
    //{
    //    wxPoint cpt = getNcPoint(pt);
    //    wxRect closeRect = this->getNcButtonRect(NcButton::Close);
    //    if (closeRect.Contains(cpt))
    //    {
    //        this->closeButtonHover(true);
    //        return HTBORDER;
    //    }
    //
    //    this->closeButtonHover(false);
    //
    //    int res = wxDialog::MSWWindowProc(WM_NCHITTEST, 0, MAKELONG(pt.x, pt.y));
    //    switch (res)
    //    {
    //    case HTCLOSE:
    //        return 0;
    //    }
    //    
    //    return res;
    //}
    //
    //int Dialog::ncLButtonUp(wxPoint pt, int hittest)
    //{
    //    wxPoint cpt = getNcPoint(pt);
    //    wxRect closeRect = this->getNcButtonRect(NcButton::Close);
    //    if (closeRect.Contains(cpt))
    //    {
    //        this->Close();
    //        return 0;
    //    }
    //
    //    return wxDialog::MSWWindowProc(WM_NCHITTEST, hittest, MAKELONG(pt.x, pt.y));
    //}
    //

#ifdef WXT_WINDOWS
    WXLRESULT Dialog::MSWWindowProc(WXUINT message, WXWPARAM wParam, WXLPARAM lParam)
    {
        /*switch (message)
        {
        case WM_CREATE:
        {
            BOOL value = TRUE;
            DwmSetWindowAttribute(this->GetHWND(), DWMWA_USE_IMMERSIVE_DARK_MODE, &value, sizeof(value));
            break;
        }

        case WM_NCPAINT:
            DefWindowProc(this->GetHWND(), message, wParam, lParam);
            this->paintNc();
            return 1;

        case WM_NCACTIVATE:
            this->isActive = static_cast<bool>(wParam);
            RedrawWindow(this->GetHWND(), NULL, NULL, RDW_FRAME | RDW_INVALIDATE | RDW_UPDATENOW);
            this->paintNc();
            return 1;

        case WM_NCHITTEST:
            return this->ncHitTest(wxPoint(LOWORD(lParam), HIWORD(lParam)));

        case WM_NCLBUTTONUP:
            return this->ncLButtonUp(wxPoint(LOWORD(lParam), HIWORD(lParam)), wParam);
        }*/

        //switch (message)
        //{
        //case WM_DRAWITEM:
        //{
        //    LPDRAWITEMSTRUCT itemStruct = (LPDRAWITEMSTRUCT)lParam;
        //    break;
        //}
        //}

        return wxDialog::MSWWindowProc(message, wParam, lParam);
    }
#endif
}