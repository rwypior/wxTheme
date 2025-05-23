#ifndef _h_wxtheme_combobox
#define _h_wxtheme_combobox

#include "control.h"
#include "theme.h"
#include "utils.h"

#include <wx/wx.h>

namespace wxt
{
    class ComboBox : public Control, public wxComboBox
    {
    public:
        static constexpr char ComboboxType[] = "combobox";
        static constexpr char ComboboxButtonType[] = "comboboxbutton";

    public:
        ComboBox(wxWindow* parent, wxWindowID id,
            const wxString& value = wxEmptyString,
            const wxPoint& pos = wxDefaultPosition,
            const wxSize& size = wxDefaultSize,
            int n = 0, const wxString choices[] = nullptr,
            long style = 0,
            const wxValidator& validator = wxDefaultValidator,
            const wxString& name = wxASCII_STR(wxComboBoxNameStr));

        ComboBox(wxWindow* parent, wxWindowID id,
            const wxString& value,
            const wxPoint& pos,
            const wxSize& size,
            const wxArrayString& choices,
            long style = 0,
            const wxValidator& validator = wxDefaultValidator,
            const wxString& name = wxASCII_STR(wxComboBoxNameStr));

        virtual Selector getSelector() const override;
        Selector getSelectorButton() const;

        wxRect getButtonRect();

    protected:
        void setup();

        void processTheme();

    private:
        void eventPaint(wxPaintEvent& event);
        void eventThemeChanged(ThemeEvent& event);

    private:
        Selector selector;
        Selector selectorbutton;

        wxColour defaultBackgroundColor;
        wxColour defaultTextColor;
    };
}

#endif