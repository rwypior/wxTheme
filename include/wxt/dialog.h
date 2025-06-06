#pragma once

#include "control.h"
#include "theme.h"
#include "statusbar.h"
#include "menu.h"
#include "wxt/wxt.h"

#include <wx/wx.h>
#include <wx/aui/aui.h>

#include <unordered_map>

namespace wxt
{
    class AuiHelper
    {
    public:
        struct PaneData
        {
            bool hasCloseButton;
            bool hasPinButton;
        };

    public:
        bool hasPane(const wxString& paneName);
        PaneData* getPane(const wxString& paneName);
        PaneData* addPane(const wxString& paneName);
        PaneData* addPane(wxAuiPaneInfo& pane);

    private:
        std::unordered_map<wxString, PaneData> paneData;
    };

    // TODO - Frame and Dialog classes will share a great deal of code
    // Find a way to prevent duplication

    class Frame : public Control, public wxFrame
    {
    public:
        static constexpr char FrameType[] = "window";
        static constexpr char TitlebarType[] = "titlebar";
        static constexpr char DockPanelHeaderType[] = "dockpanelheader";
        static constexpr char DockPanelButtonType[] = "dockpanelbutton";

    public:
        Frame();
        Frame(wxWindow* parent,
            wxWindowID id,
            const wxString& title,
            const wxPoint& pos = wxDefaultPosition,
            const wxSize& size = wxDefaultSize,
            long style = wxDEFAULT_FRAME_STYLE,
            const wxString& name = wxASCII_STR(wxFrameNameStr));

        Selector getSelector() const;
        Selector getTitlebarSelector() const;
        Selector getDockPanelHeaderSelector() const;
        Selector getDockPanelButtonSelector() const;

#ifdef WXT_WINDOWS
        WXLRESULT MSWWindowProc(WXUINT message, WXWPARAM wParam, WXLPARAM lParam) override;
        void updateNc();
#endif

    protected:
        void setup();
        void processTheme();
        void processLanguage();

        void enableAuiTheming(wxAuiManager& mgr);
        void enableStatusBarTheming(wxStatusBar* statusBar);
        void enableMenuBarTheming(MenuBar* menuBar);
        void enableMenuBarLanguage(MenuBar* menuBar);

        // Events
        void eventAuiRender(wxAuiManagerEvent& event);
        void eventThemeChanged(ThemeEvent& event);
        void eventLanguageChanged(LanguageEvent& event);

    private:
        Selector selector;
        Selector titlebarSelector;
        Selector dockPanelHeaderSelector;
        Selector dockPanelButtonSelector;

        wxColour defaultBackgroundColor;
        wxColour defaultTextColor;

        AuiHelper auiHelper;
        StatusBarManager statusbarManager;

        MenuBar* themedMenu = nullptr;
        MenuBar* translatedMenu = nullptr;
    };

    class Dialog : public Control, public wxDialog
    {
    public:
        static constexpr char DialogType[] = "window";

    public:
        enum class NcButton
        {
            Minimize = 2,
            Maximize = 3,
            Help = 4,
            Close = 5
        };

    public:
        Dialog(wxWindow* parent, wxWindowID id,
            const wxString& title,
            const wxPoint& pos = wxDefaultPosition,
            const wxSize& size = wxDefaultSize,
            long style = wxDEFAULT_DIALOG_STYLE,
            const wxString& name = wxASCII_STR(wxDialogNameStr));

        Selector getSelector() const;
        Selector getTitlebarSelector() const;

#ifdef WXT_WINDOWS
        WXLRESULT MSWWindowProc(WXUINT message, WXWPARAM wParam, WXLPARAM lParam) override;
        void updateNc();
        wxRect getNcButtonRect(NcButton btn);
#endif

        wxRect getInnerClientRect() const;
        wxRect getOuterClientRect() const;
        wxRect getTitlebarRect() const;

        wxPoint getNcPoint(wxPoint pt);

    protected:
        void processTheme();

    private:
        //void closeButtonHover(bool hovered);

        //void paintNc();
        //int ncHitTest(wxPoint pt);
        //int ncLButtonUp(wxPoint pt, int hittest);

        // Events
        void eventThemeChanged(ThemeEvent& event);
        void eventPaint(wxPaintEvent& event);

    private:
        Selector selector;
        Selector titlebarSelector;

        bool isActive = true;
        bool closeButtonHovered = false;
    };
}