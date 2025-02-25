#ifndef _h_wxtheme_button
#define _h_wxtheme_button

#include "control.h"
#include "theme.h"
#include "utils.h"

#include <wx/wx.h>

namespace wxt
{
    class Button : public Control, public wxButton
    {
    public:
        static constexpr char ButtonType[] = "button";

        enum class ButtonState
        {
            Normal = 0x00,
            Pressed = 0x01,
            Hover = 0x02
        };

    public:
        Button(wxWindow* parent,
            wxWindowID id,
            const wxString& label = wxEmptyString,
            const wxPoint& pos = wxDefaultPosition,
            const wxSize& size = wxDefaultSize,
            long style = 0,
            const wxValidator& validator = wxDefaultValidator,
            const wxString& name = wxASCII_STR(wxButtonNameStr));

        virtual Selector getSelector() const override;

    protected:
        virtual void DoSetToolTipText(const wxString& tip) override;

    private:
        void processLanguage();

        void eventPaint(wxPaintEvent& event);
        void eventLmbDown(wxMouseEvent& event);
        void eventLmbUp(wxMouseEvent& event);
        void eventMouseHover(wxMouseEvent& event);
        void eventMouseLeave(wxMouseEvent& event);
        void eventLanguageChanged(LanguageEvent& event);

    protected:
        Selector selector;

    private:
        ButtonState state = ButtonState::Normal;

        wxString originalCaption;
        wxString originalTooltip;
    };

    class SmallButton : public Button
    {
    public:
        static constexpr char SmallButtonType[] = "smallbutton";

    public:
        SmallButton(wxWindow* parent,
            wxWindowID id,
            const wxString& label = wxEmptyString,
            const wxPoint& pos = wxDefaultPosition,
            const wxSize& size = wxDefaultSize,
            long style = 0,
            const wxValidator& validator = wxDefaultValidator,
            const wxString& name = wxASCII_STR(wxButtonNameStr));

        virtual Selector getSelector() const override;
    };
}

DEFINE_BITFIELD(wxt::Button::ButtonState);

#endif