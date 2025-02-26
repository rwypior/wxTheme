#pragma once

#include "control.h"
#include "theme.h"

#include <wx/wx.h>
#include <wx/aui/aui.h>

namespace wxt
{
    class StaticBox : public Control, public wxStaticBox
    {
    public:
        static constexpr char StaticBoxType[] = "groupbox";

    public:
        StaticBox();
        StaticBox(wxWindow* parent, wxWindowID id,
            const wxString& label,
            const wxPoint& pos = wxDefaultPosition,
            const wxSize& size = wxDefaultSize,
            long style = 0,
            const wxString& name = wxASCII_STR(wxStaticBoxNameStr));

        virtual Selector getSelector() const override;

    protected:
        void setup();
        void processTheme();
        void processLanguage();

    private:
        void eventThemeChanged(ThemeEvent& event);
        void eventLanguageChanged(LanguageEvent& event);

    private:
        wxString originalLabel;

        Selector selector;

        wxColour defaultBackgroundColor;
        wxColour defaultTextColor;
    };
}