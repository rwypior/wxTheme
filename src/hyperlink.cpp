#include "wxt/hyperlink.h"

namespace wxt
{
    HyperlinkCtrl::HyperlinkCtrl(wxWindow* parent,
        wxWindowID id,
        const wxString& label, const wxString& url,
        const wxPoint& pos,
        const wxSize& size,
        long style,
        const wxString& name)
        : wxHyperlinkCtrl(parent, id, label, url, pos, size, style, name)
    {
        this->setup();
    }

    void HyperlinkCtrl::setup()
    {
        this->selector.type = HyperlinkType;

        this->defaultBackgroundColor = this->GetBackgroundColour();

        this->Bind(wxtEVT_THEME_CHANGED, &HyperlinkCtrl::eventThemeChanged, this);
        this->Bind(wxEVT_PAINT, &HyperlinkCtrl::eventPaint, this);
        this->processTheme();
    }

    Selector HyperlinkCtrl::getSelector() const
    {
        return this->selector;
    }

    void HyperlinkCtrl::processTheme()
    {
        Theme& theme = Theme::getInstance();

        auto bg = theme.getBackgroundColor(this->getSelector());
        this->SetBackgroundColour(bg ? *bg : this->defaultBackgroundColor);
    }

    void HyperlinkCtrl::eventThemeChanged(ThemeEvent& event)
    {
        this->processTheme();
    }

    void HyperlinkCtrl::eventPaint(wxPaintEvent& event)
    {
        Theme& theme = Theme::getInstance();
        if (theme.isEnabled())
        {
            wxPaintDC dc(this);
            if (auto fg = theme.getTextColor(this->getSelector()))
                dc.SetTextForeground(*fg);
            dc.DrawText(this->GetLabel(), this->GetLabelRect().x, this->GetLabelRect().y);
        }
        else
            event.Skip();
    }
}