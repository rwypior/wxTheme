#ifndef _h_wxtheme_staticline
#define _h_wxtheme_staticline

#include "control.h"
#include "theme.h"
#include "utils.h"

#include <wx/wx.h>
#include <wx/statline.h>

namespace wxt
{
    class StaticLine : public Control, public wxStaticLine
    {
    public:
        static constexpr char LineType[] = "line";

    public:
        StaticLine();
        StaticLine(wxWindow* parent,
            wxWindowID id = wxID_ANY,
            const wxPoint& pos = wxDefaultPosition,
            const wxSize& size = wxDefaultSize,
            long style = wxLI_HORIZONTAL,
            const wxString& name = wxASCII_STR(wxStaticLineNameStr));

        virtual Selector getSelector() const override;

    protected:
        void setup();

    private:
        void paint(wxDC& dc);

    private:
        void eventPaint(wxPaintEvent& event);
        void eventNcPaint(wxNcPaintEvent& event);

    private:
        Selector selector;

        wxColour defaultBackgroundColor;
    };
}

#endif