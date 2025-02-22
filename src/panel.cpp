#include "wxt/panel.h"
#include "wxt/utils.h"

namespace wxt
{
    Panel::Panel(wxWindow* parent,
        wxWindowID winid,
        const wxPoint& pos,
        const wxSize& size,
        long style,
        const wxString& name)
        : wxPanel(parent, winid, pos, size, style, name)
    {
        this->setup();
    }

    Selector Panel::getSelector() const
    {
        return this->selector;
    }

    wxColour Panel::getPanelBackgroundColor() const
    {
        Theme& theme = Theme::getInstance();
        return *theme.getBackgroundColor(this->getSelector());
    }

    void Panel::setup()
    {
        this->selector.type = PanelType;

        this->defaultBackgroundColor = this->GetBackgroundColour();
        this->defaultTextColor = this->GetForegroundColour();

        this->Bind(wxtEVT_THEME_CHANGED, &Panel::eventThemeChanged, this);
        this->Bind(wxEVT_PAINT, &Panel::eventPaint, this);

        this->processTheme();
    }

    void Panel::processTheme()
    {
        Theme& theme = Theme::getInstance();
        this->SetBackgroundColour(theme.isEnabled() ? this->getPanelBackgroundColor() : this->defaultBackgroundColor);
        this->SetForegroundColour(
            theme.isEnabled() ? 
            either(theme.getTextColor(this->getSelector()), this->GetParent() ? this->GetParent()->GetForegroundColour() : this->defaultTextColor) : 
            this->defaultTextColor
        );
    }

    void Panel::eventThemeChanged(ThemeEvent& event)
    {
        this->processTheme();
    }

    void Panel::eventPaint(wxPaintEvent& event)
    {
        Theme& theme = Theme::getInstance();
        if (theme.isEnabled())
        {
            wxPaintDC dc(this);
            wxRect rect = this->GetClientRect();

            dc.SetPen(this->getPanelBackgroundColor());
            dc.SetBrush(this->getPanelBackgroundColor());
            dc.DrawRectangle(rect);
        }
    }

    // Info panel

    InfoPanel::InfoPanel(wxWindow* parent,
        wxWindowID winid,
        const wxPoint& pos,
        const wxSize& size,
        long style,
        const wxString& name)
        : Panel(parent, winid, pos, size, style, name)
    {
        this->selector.type = InfoPanelType;
    }

    Selector InfoPanel::getSelector() const
    {
        return this->selector;
    }

    wxColour InfoPanel::getPanelBackgroundColor() const
    {
        Theme& theme = Theme::getInstance();
        return *theme.getBackgroundColor(this->getSelector());
    }
}