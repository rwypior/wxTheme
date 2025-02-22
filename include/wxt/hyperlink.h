#pragma once

#include "control.h"
#include "theme.h"

#include <wx/wx.h>
#include <wx/hyperlink.h>

namespace wxt
{
    class HyperlinkCtrl : public Control, public wxHyperlinkCtrl
    {
    public:
        static constexpr char HyperlinkType[] = "hyperlink";

    public:
        HyperlinkCtrl(wxWindow* parent,
            wxWindowID id,
            const wxString& label, const wxString& url,
            const wxPoint& pos = wxDefaultPosition,
            const wxSize& size = wxDefaultSize,
            long style = wxHL_DEFAULT_STYLE,
            const wxString& name = wxASCII_STR(wxHyperlinkCtrlNameStr));

        virtual Selector getSelector() const override;

    protected:
        void setup();
        void processTheme();

    private:
        void eventThemeChanged(ThemeEvent& event);
        void eventPaint(wxPaintEvent& event);

    private:
        Selector selector;

        wxColour defaultBackgroundColor;
    };
}