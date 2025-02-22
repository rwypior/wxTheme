#include "wxt/checkbox.h"

namespace wxt
{
    Checkbox::Checkbox(wxWindow* parent,
        wxWindowID id,
        const wxString& label,
        const wxPoint& pos,
        const wxSize& size,
        long style,
        const wxValidator& validator,
        const wxString& name)
        : wxCheckBox(parent, id, label, pos, size, style, validator, name)
    {
        this->originalLabel = label;

        this->setup();

        this->selector.type = CheckboxType;
    }

    void Checkbox::setup()
    {
        this->Bind(wxtEVT_THEME_CHANGED, &Checkbox::eventThemeChanged, this);
        this->Bind(wxtEVT_LANGUAGE_CHANGED, &Checkbox::eventLanguageChanged, this);

        this->defaultBackgroundColor = this->GetBackgroundColour();
        this->defaultTextColor = this->GetForegroundColour();

        Theme& theme = Theme::getInstance();
        if (theme.isEnabled())
        {
            this->processTheme();
        }

        this->processLanguage();
    }

    Selector Checkbox::getSelector() const
    {
        return this->selector;
    }

    void Checkbox::processTheme()
    {
        Theme& theme = Theme::getInstance();
        
        auto bg = theme.getBackgroundColor(this->getSelector());
        this->SetBackgroundColour(bg ? *bg : this->defaultBackgroundColor);

        auto fg = theme.getTextColor(this->getSelector());
        this->SetForegroundColour(fg ? *fg : this->defaultTextColor);
    }

    void Checkbox::processLanguage()
    {
        this->SetLabel(translate(this->originalLabel));
    }

    void Checkbox::eventThemeChanged(ThemeEvent& event)
    {
        this->processTheme();
    }

    void Checkbox::eventLanguageChanged(LanguageEvent& event)
    {
        this->processLanguage();
    }
}