#include "wxt/combobox.h"
#include "wxt/utils.h"

#include <wx/settings.h>

namespace wxt
{
    ComboBox::ComboBox(wxWindow* parent, wxWindowID id,
        const wxString& value,
        const wxPoint& pos,
        const wxSize& size,
        int n, const wxString choices[],
        long style,
        const wxValidator& validator,
        const wxString& name)
        : wxComboBox(parent, id, value, pos, size, n, choices, style, validator, name)
    {
        this->setup();
    }

    ComboBox::ComboBox(wxWindow* parent, wxWindowID id,
        const wxString& value,
        const wxPoint& pos,
        const wxSize& size,
        const wxArrayString& choices,
        long style,
        const wxValidator& validator,
        const wxString& name)
        : wxComboBox(parent, id, value, pos, size, choices, style, validator, name)
    {
        this->setup();
    }

    void ComboBox::setup()
    {
        this->defaultBackgroundColor = this->GetBackgroundColour();
        this->defaultTextColor = this->GetForegroundColour();

        this->Bind(wxEVT_PAINT, &ComboBox::eventPaint, this);
        this->Bind(wxtEVT_THEME_CHANGED, &ComboBox::eventThemeChanged, this);

        this->processTheme();
        
        this->selector.type = ComboboxType;
        this->selectorbutton.type = ComboboxButtonType;
    }

    Selector ComboBox::getSelector() const
    {
        return this->selector;
    }

    Selector ComboBox::getSelectorButton() const
    {
        return this->selectorbutton;
    }

    wxRect ComboBox::getButtonRect()
    {
        wxRect rect = this->GetClientRect();

        wxSystemSettings sets;
        int buttonWidth = sets.GetMetric(wxSYS_VSCROLL_X, this);
        if (buttonWidth == -1)
            buttonWidth = 18;
        else
            buttonWidth += 2; // Need to find a better metric, or find out why the difference

        int border = getWidgetBorder(*this);
        wxRect buttonrect = rect;
        buttonrect.x = buttonrect.GetRight() - buttonWidth;
        buttonrect.SetWidth(buttonWidth);
        buttonrect.y -= border;
        buttonrect.height += border * 2;

        return buttonrect;
    }

    void ComboBox::processTheme()
    {
        Theme& theme = Theme::getInstance();

        this->SetBackgroundColour(
            theme.isEnabled() ? 
            either(theme.getBackgroundColor(this->getSelector()), this->GetParent() ? this->GetParent()->GetForegroundColour() : this->defaultTextColor) :
            this->defaultBackgroundColor);

        this->SetForegroundColour(
            theme.isEnabled() ?
            either(theme.getTextColor(this->getSelector()), this->GetParent() ? this->GetParent()->GetForegroundColour() : this->defaultTextColor) : 
            this->defaultTextColor
        );
    }

    void ComboBox::eventPaint(wxPaintEvent& event)
    {
        static constexpr int DefaultButtonWidth = 18; // Seems to look ok

        Theme& theme = Theme::getInstance();
        if (theme.isEnabled())
        {
            wxPaintDC dc(this);

            int border = getWidgetBorder(*this);

            wxRect rect = this->GetClientRect();

            // Border
            dc.SetBrush(*wxTRANSPARENT_BRUSH);
            dc.SetPen(wxPen(*theme.getBackgroundColor(this->getSelector()), border));
            dc.DrawRectangle(rect);

            // Button
            dc.SetBrush(wxBrush(*theme.getBackgroundColor(this->getSelectorButton())));
            if (auto bordercolor = theme.getBorderColor(this->getSelector()))
                dc.SetPen(wxPen(*bordercolor, border));

            wxSystemSettings sets;
            int buttonWidth = sets.GetMetric(wxSYS_VSCROLL_X, this);
            if (buttonWidth == -1)
                buttonWidth = DefaultButtonWidth;

            wxRect buttonrect = this->getButtonRect();
            dc.DrawRectangle(buttonrect);

            // Triangle
            dc.SetBrush(wxBrush(*theme.getTextColor(this->getSelectorButton())));
            dc.SetPen(wxNullPen);
            wxPoint pts[] = {
                { buttonrect.x + 4, buttonrect.y + 14 },
                { buttonrect.GetRight() - 4, buttonrect.y + 14},
                { buttonrect.x + buttonrect.width / 2, buttonrect.GetBottom() - 11}
            };
            dc.DrawPolygon(3, pts);
        }
        else
            event.Skip();
    }

    void ComboBox::eventThemeChanged(ThemeEvent& event)
    {
        this->processTheme();
    }
}