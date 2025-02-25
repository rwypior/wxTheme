#ifndef _h_wxtheme_wxterminal
#define _h_wxtheme_wxterminal

#include "wxt/text.h"

#include <wxterminal/terminalCtrl.h>

namespace wxt
{
    // TODO - this is almost exact copy of TextCtrl. This needs to be refactored.

	class Terminal : public Control, public TerminalCtrl
	{
    public:
        static constexpr char TextType[] = "terminal";

    public:
        Terminal();
        Terminal(wxWindow* parent, wxWindowID id,
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
        void eventThemeChanged(ThemeEvent& event) override;

    private:
        Selector selector;

        wxColour defaultBackgroundColor;
        wxColour defaultTextColor;
	};
}

#endif