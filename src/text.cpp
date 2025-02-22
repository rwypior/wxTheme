#include "wxt/text.h"

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
    TextCtrl::TextCtrl()
        : wxTextCtrl()
    {
        this->setup();
    }

    TextCtrl::TextCtrl(wxWindow* parent, wxWindowID id,
        const wxString& value,
        const wxPoint& pos,
        const wxSize& size,
        long style,
        const wxValidator& validator,
        const wxString& name)
        : wxTextCtrl(parent, id, value, pos, size, getStyle(style), validator, name)
    {
        this->setup();
    }

    Selector TextCtrl::getSelector() const
    {
        return this->selector;
    }

    void TextCtrl::setup()
    {
        this->selector.type = TextType;

        this->defaultBackgroundColor = this->GetBackgroundColour();
        this->defaultTextColor = this->GetForegroundColour();

        this->Bind(wxtEVT_THEME_CHANGED, &TextCtrl::eventThemeChanged, this);
        this->Bind(wxEVT_NC_PAINT, &TextCtrl::eventNcPaint, this);

        Theme& theme = Theme::getInstance();
        if (theme.isEnabled())
        {
            this->processTheme();
        }
    }

    void TextCtrl::processTheme()
    {
        Theme& theme = Theme::getInstance();
        this->SetBackgroundColour(theme.isEnabled() ? *theme.getBackgroundColor(this->selector) : this->defaultBackgroundColor);
        this->SetForegroundColour(theme.isEnabled() ? *theme.getTextColor(this->selector) : this->defaultTextColor);

        wxTextAttr attr(this->GetForegroundColour(), this->GetBackgroundColour());
        this->SetStyle(0, this->GetValue().length(), attr);
        this->SetDefaultStyle(attr);
    }

    void TextCtrl::eventNcPaint(wxNcPaintEvent& event)
    {
        Theme& theme = Theme::getInstance();
        if (theme.isEnabled())
        {
            wxWindowDC dc(this);
            dc.SetBrush(*wxTRANSPARENT_BRUSH);
            dc.SetPen(wxPen(*theme.getBorderColor(this->selector), 3));
            dc.DrawRectangle(this->GetClientRect());
        }
    }

    void TextCtrl::eventThemeChanged(ThemeEvent& event)
    {
        this->processTheme();
    }
}