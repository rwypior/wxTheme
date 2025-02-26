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

        this->Bind(wxtEVT_THEME_CHANGED, &StaticBox::eventThemeChanged, this);
        this->Bind(wxtEVT_LANGUAGE_CHANGED, &StaticBox::eventLanguageChanged, this);

        this->processTheme();
        this->processLanguage();
    }

    void StaticBox::processTheme()
    {
        Theme& theme = Theme::getInstance();
        this->SetBackgroundColour(either(theme.getBackgroundColor(this->getSelector()), this->defaultBackgroundColor));
        this->SetForegroundColour(either(theme.getTextColor(this->getSelector()), this->defaultTextColor));
    }

    void StaticBox::processLanguage()
    {
        this->SetLabel(translate(this->originalLabel));
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