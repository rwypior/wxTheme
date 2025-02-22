#pragma once

#include "control.h"
#include "theme.h"

#include <wx/wx.h>

namespace wxt
{
    class Label : public Control, public wxStaticText
    {
    public:
        static constexpr char LabelType[] = "label";

    public:
        Label(wxWindow* parent,
            wxWindowID id,
            const wxString& label,
            const wxPoint& pos = wxDefaultPosition,
            const wxSize& size = wxDefaultSize,
            long style = 0,
            const wxString& name = wxASCII_STR(wxStaticTextNameStr));

        virtual Selector getSelector() const override;

    protected:
        void setup();
        void processTheme();
        void processLanguage();

    private:
        virtual void eventThemeChanged(ThemeEvent& event) override;
        virtual void eventLanguageChanged(LanguageEvent& event) override;

    private:
        Selector selector;

        wxColour defaultBackgroundColor;
        wxColour defaultTextColor;

        wxString originalString;
    };

    class LabelAutoWrap : public Label
    {
    public:
        bool autoWrap = true;

    public:
        LabelAutoWrap(wxWindow* parent,
            wxWindowID id,
            const wxString& label,
            const wxPoint& pos = wxDefaultPosition,
            const wxSize& size = wxDefaultSize,
            long style = 0,
            const wxString& name = wxASCII_STR(wxStaticTextNameStr));

        virtual void SetLabel(const wxString& label) override;

        void wrapText();

    private:
        void eventSize(wxSizeEvent& event);

    private:
        bool isWrapping = false;
        bool isUpdatingText = false;
        wxString originalText;
    };
}