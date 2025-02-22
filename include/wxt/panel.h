#pragma once

#include "control.h"
#include "theme.h"

#include <wx/wx.h>
#include <wx/aui/aui.h>

namespace wxt
{
    class Panel : public Control, public wxPanel
    {
    public:
        static constexpr char PanelType[] = "panel";

    public:
        Panel(wxWindow* parent,
            wxWindowID winid = wxID_ANY,
            const wxPoint& pos = wxDefaultPosition,
            const wxSize& size = wxDefaultSize,
            long style = wxTAB_TRAVERSAL | wxNO_BORDER,
            const wxString& name = wxASCII_STR(wxPanelNameStr));

        virtual Selector getSelector() const override;
        virtual wxColour getPanelBackgroundColor() const;

    protected:
        void setup();
        void processTheme();

    private:
        void eventThemeChanged(ThemeEvent& event) override;
        void eventPaint(wxPaintEvent& event);

        Selector selector;

        wxColour defaultBackgroundColor;
        wxColour defaultTextColor;
    };

    class InfoPanel : public Panel
    {
    public:
        static constexpr char InfoPanelType[] = "infopanel";

    public:
        InfoPanel(wxWindow* parent,
            wxWindowID winid = wxID_ANY,
            const wxPoint& pos = wxDefaultPosition,
            const wxSize& size = wxDefaultSize,
            long style = wxTAB_TRAVERSAL | wxNO_BORDER,
            const wxString& name = wxASCII_STR(wxPanelNameStr));

        virtual Selector getSelector() const override;
        virtual wxColour getPanelBackgroundColor() const;

        Selector selector;
    };
}