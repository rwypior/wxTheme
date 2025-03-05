#include "wxt/panel.h"
#include "wxt/utils.h"

namespace wxt
{
    Panel::Panel(wxWindow* parent,
        wxWindowID winid,
        const wxPoint& pos,
        const wxSize& size,
        long style,
        const wxString& name,
        bool performsetup)
        : wxPanel(parent, winid, pos, size, style, name)
    {
        this->selector.type = PanelType;
        if (performsetup)
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

    bool Panel::SetBackgroundColour(const wxColour& colour)
    {
        if (this->themeWatch)
            return wxPanel::SetBackgroundColour(colour);
        else
        {
            this->defaultBackgroundColor = colour;
            if (!Theme::getInstance().isEnabled())
                return wxPanel::SetBackgroundColour(colour);
        }
        return true;
    }

    void Panel::setup()
    {
        this->defaultBackgroundColor = this->GetBackgroundColour();
        this->defaultTextColor = this->GetForegroundColour();

        this->Bind(wxtEVT_THEME_CHANGED, &Panel::eventThemeChanged, this);
        this->Bind(wxEVT_PAINT, &Panel::eventPaint, this);
        this->Bind(wxEVT_NC_PAINT, &Panel::eventNcPaint, this);

        this->processTheme();
    }

    void Panel::processTheme()
    {
        auto watcher = this->themeWatch();
        Theme& theme = Theme::getInstance();
        this->SetOwnBackgroundColour(theme.isEnabled() ? this->getPanelBackgroundColor() : this->defaultBackgroundColor);
        this->SetOwnForegroundColour(
            either(theme.getTextColor(this->getSelector()), this->GetParent() ? this->GetParent()->GetForegroundColour() : this->defaultTextColor)
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

    void Panel::eventNcPaint(wxNcPaintEvent& event)
    {
        Theme& theme = Theme::getInstance();
        if (theme.isEnabled())
        {
            wxWindowDC dc(this);

            if (auto borderColor = theme.getBorderColor(this->getSelector()))
            {
                if (this->GetWindowStyle() & wxBORDER_THEME)
                {
                    auto borderSize = this->GetWindowBorderSize();
                    wxRect rct = this->GetClientRect();
                    rct.width += borderSize.x;
                    rct.height += borderSize.y;

                    dc.SetPen(wxPen(*borderColor, borderSize.x));
                    dc.DrawLine(rct.GetRight(), rct.GetTop(), rct.GetRight(), rct.GetBottom());
                    dc.DrawLine(rct.GetRight(), rct.GetBottom(), rct.GetLeft(), rct.GetBottom());
                    dc.DrawLine(rct.GetLeft(), rct.GetBottom(), rct.GetLeft(), rct.GetTop());
                    dc.DrawLine(rct.GetLeft(), rct.GetTop(), rct.GetRight(), rct.GetTop());
                }
            }
        }
    }

    // Info panel

    InfoPanel::InfoPanel(wxWindow* parent,
        wxWindowID winid,
        const wxPoint& pos,
        const wxSize& size,
        long style,
        const wxString& name)
        : Panel(parent, winid, pos, size, style, name, false)
    {
        this->selector.type = InfoPanelType;
        this->setup();
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