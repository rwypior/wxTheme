#include "wxt/ext/terminalctrl.h"
#include "wxt/utils.h"

namespace
{
    long getStyle(long style)
    {
        wxt::Theme& theme = wxt::Theme::getInstance();
        if (theme.isEnabled())
        {
            style |= wxNO_BORDER;
        }

        return style;
    }
}

namespace wxt
{
    Terminal::Terminal()
        : TerminalCtrl()
    {
        this->setup();
    }

    Terminal::Terminal(wxWindow* parent, wxWindowID id,
        const wxString& value,
        const wxPoint& pos,
        const wxSize& size,
        long style,
        const wxValidator& validator,
        const wxString& name)
        : TerminalCtrl(parent, id, value, pos, size, getStyle(style), validator, name)
    {
        this->setup();
    }

    Selector Terminal::getSelector() const
    {
        return this->selector;
    }

    void Terminal::setup()
    {
        this->selector.type = TextType;

        this->defaultBackgroundColor = this->GetBackgroundColour();
        this->defaultTextColor = this->GetForegroundColour();

        this->Bind(wxtEVT_THEME_CHANGED, &Terminal::eventThemeChanged, this);
        this->Bind(wxEVT_NC_PAINT, &Terminal::eventNcPaint, this);

        Theme& theme = Theme::getInstance();
        if (theme.isEnabled())
        {
            this->processTheme();
        }
    }

    void Terminal::processTheme()
    {
        Theme& theme = Theme::getInstance();
        this->SetBackgroundColour(theme.isEnabled() ? either(theme.getBackgroundColor(this->selector), this->defaultBackgroundColor) : this->defaultBackgroundColor);
        this->SetForegroundColour(theme.isEnabled() ? either(theme.getTextColor(this->selector), this->defaultBackgroundColor) : this->defaultTextColor);

        wxTextAttr attr(this->GetForegroundColour(), this->GetBackgroundColour());
        this->SetStyle(0, this->GetValue().length(), attr);
        this->SetDefaultStyle(attr);
    }

    void Terminal::eventNcPaint(wxNcPaintEvent& event)
    {
        Theme& theme = Theme::getInstance();
        if (theme.isEnabled())
        {
            wxWindowDC dc(this);
            dc.SetBrush(*wxTRANSPARENT_BRUSH);
            if (auto bordercolor = theme.getBorderColor(this->selector))
                dc.SetPen(wxPen(*bordercolor, 3));
            dc.DrawRectangle(this->GetClientRect());
        }
    }

    void Terminal::eventThemeChanged(ThemeEvent& event)
    {
        this->processTheme();
    }
}