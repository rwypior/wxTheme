#include "wxt/staticbox.h"
#include "wxt/utils.h"

namespace wxt
{
    StaticBox::StaticBox()
        : wxStaticBox()
    {
        this->setup();
    }

    StaticBox::StaticBox(wxWindow* parent, wxWindowID id,
        const wxString& label,
        const wxPoint& pos,
        const wxSize& size,
        long style,
        const wxString& name)
        : wxStaticBox(parent, id, label, pos, size, style, name)
    {
        this->originalLabel = label;

        this->setup();
    }

    Selector StaticBox::getSelector() const
    {
        return this->selector;
    }

    void StaticBox::setup()
    {
        this->selector.type = StaticBoxType;
        
        this->defaultBackgroundColor = this->GetBackgroundColour();
        this->defaultTextColor = this->GetForegroundColour();

        this->Bind(wxEVT_NC_PAINT, &StaticBox::eventNcPaint, this);
        this->Bind(wxtEVT_THEME_CHANGED, &StaticBox::eventThemeChanged, this);
        this->Bind(wxtEVT_LANGUAGE_CHANGED, &StaticBox::eventLanguageChanged, this);

        this->processTheme();
        this->processLanguage();
    }

    void StaticBox::processTheme()
    {
        Theme& theme = Theme::getInstance();
        this->SetOwnBackgroundColour(either(theme.getBackgroundColor(this->getSelector()), this->defaultBackgroundColor));
        this->SetOwnForegroundColour(either(theme.getTextColor(this->getSelector()), this->defaultTextColor));

        Refresh();
        Update();
    }

    void StaticBox::processLanguage()
    {
        this->SetLabel(translate(this->originalLabel));
    }

    void StaticBox::eventNcPaint(wxNcPaintEvent& event)
    {
        Theme& theme = Theme::getInstance();
        if (theme.isEnabled())
        {
            wxWindowDC dc(this);

            if (auto borderColor = theme.getBorderColor(this->getSelector()))
            {
                wxSize ext = dc.GetTextExtent(this->GetLabel());

                wxRect rct = this->GetClientRect();
                int top = rct.GetTop() + ext.GetHeight() / 2;
                int labelLeft = 7;
                int labelRight = labelLeft + 4;
                int bottom = rct.GetBottom() - 1;

                dc.SetPen(wxPen(*borderColor));

                dc.DrawLine({ rct.GetLeft(), top}, {labelLeft, top});
                dc.DrawLine({ labelRight + ext.GetWidth(), top}, {rct.GetRight(), top});
                dc.DrawLine({ rct.GetRight(), top}, {rct.GetRight(), bottom + 1});
                dc.DrawLine({ rct.GetRight(), bottom }, { rct.GetLeft(), bottom });
                dc.DrawLine({ rct.GetLeft(), bottom }, { rct.GetLeft(), top });
            }
        }
    }

    void StaticBox::eventThemeChanged(ThemeEvent& event)
    {
        this->processTheme();
    }

    void StaticBox::eventLanguageChanged(LanguageEvent& event)
    {
        this->processLanguage();
    }
}