#pragma once

#include "control.h"
#include "theme.h"

#include "wx/treelist.h"
#include "wx/dataview.h"

namespace wxt
{
    class Toolbar : public Control, public wxToolBar
    {
    public:
        static constexpr char ToolbarType[] = "toolbar";

    public:
        Toolbar();
        Toolbar(wxWindow* parent,
            wxWindowID id,
            const wxPoint& pos = wxDefaultPosition,
            const wxSize& size = wxDefaultSize,
            long style = wxTB_DEFAULT_STYLE,
            const wxString& name = wxASCII_STR(wxToolBarNameStr));

        virtual Selector getSelector() const override;

    protected:
        void setup();
        void processTheme();

    private:
        void eventThemeChanged(ThemeEvent& event) override;

        void eventNcPaint(wxNcPaintEvent& event);
        void eventPaint(wxPaintEvent& event);

    private:
        Selector selector;

        wxColour defaultBackgroundColor;
        wxColour defaultTextColor;
    };
}