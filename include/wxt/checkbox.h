#pragma once

#include "control.h"
#include "theme.h"

#include <wx/wx.h>

namespace wxt
{
    class Checkbox : public Control, public wxCheckBox
    {
    public:
        static constexpr char CheckboxType[] = "checkbox";

    public:
        Checkbox();
        Checkbox(wxWindow* parent,
            wxWindowID id,
            const wxString& label,
            const wxPoint& pos = wxDefaultPosition,
            const wxSize& size = wxDefaultSize,
            long style = 0,
            const wxValidator& validator = wxDefaultValidator,
            const wxString& name = wxASCII_STR(wxCheckBoxNameStr));

    virtual Selector getSelector() const override;

    protected:
        void setup();
        void processTheme();
        void processLanguage();

    private:
        void eventThemeChanged(ThemeEvent& event);
        void eventLanguageChanged(LanguageEvent& event);

    protected:
        Selector selector;

    private:
        wxString originalLabel;

        wxColour defaultBackgroundColor;
        wxColour defaultTextColor;
    };
}