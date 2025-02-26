#pragma once

#include "control.h"
#include "theme.h"

#include <wx/wx.h>
#include <wx/aui/aui.h>

namespace wxt
{
    class TextCtrl : public Control, public wxTextCtrl
    {
    public:
        static constexpr char TextType[] = "editbox";

    public:
        TextCtrl();
        TextCtrl(wxWindow* parent, wxWindowID id,
            const wxString& value = wxEmptyString,
            const wxPoint& pos = wxDefaultPosition,
            const wxSize& size = wxDefaultSize,
            long style = 0,
            const wxValidator& validator = wxDefaultValidator,
            const wxString& name = wxASCII_STR(wxTextCtrlNameStr));

        Selector getSelector() const;

    protected:
        void setup();
        void processTheme();

    private:
        void eventNcPaint(wxNcPaintEvent& event);
        void eventThemeChanged(ThemeEvent& event);

    private:
        Selector selector;

        wxColour defaultBackgroundColor;
        wxColour defaultTextColor;
    };
}