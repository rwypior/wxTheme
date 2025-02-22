#include "wxt/combobox.h"
#include "wxt/utils.h"

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

        this->Bind(wxtEVT_THEME_CHANGED, &ComboBox::eventThemeChanged, this);

        this->processTheme();
        
        this->selector.type = ButtonType;
    }

    Selector ComboBox::getSelector() const
    {
        return this->selector;
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

    void ComboBox::eventThemeChanged(ThemeEvent& event)
    {
        this->processTheme();
    }
}