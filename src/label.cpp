#include "wxt/label.h"
#include "wxt/utils.h"

namespace wxt
{
    Label::Label(wxWindow* parent,
        wxWindowID id,
        const wxString& label,
        const wxPoint& pos,
        const wxSize& size,
        long style,
        const wxString& name)
        : wxStaticText(parent, id, label, pos, size, style, name)
        , originalString(label)
    {
        this->setup();
    }

    void Label::setup()
    {
        this->selector.type = LabelType;

        this->defaultBackgroundColor = this->GetBackgroundColour();
        this->defaultTextColor = this->GetForegroundColour();

        this->Bind(wxtEVT_THEME_CHANGED, &Label::eventThemeChanged, this);
        this->Bind(wxtEVT_LANGUAGE_CHANGED, &Label::eventLanguageChanged, this);

        this->processTheme();
        this->processLanguage();
    }

    Selector Label::getSelector() const
    {
        return this->selector;
    }

    void Label::processTheme()
    {
        Theme& theme = Theme::getInstance();

        auto bg = theme.getBackgroundColor(this->getSelector());
        auto qweqwe = this->GetParent();
        auto asdasd = this->GetParent()->GetBackgroundColour();
        this->SetBackgroundColour(bg ? *bg : (this->GetParent() ? this->GetParent()->GetBackgroundColour() : this->defaultBackgroundColor));

        auto fg = theme.getTextColor(this->getSelector());
        this->SetForegroundColour(fg ? *fg : this->defaultTextColor);
    }

    void Label::processLanguage()
    {
        wxString translation = translate(this->originalString);
        if (!translation.empty())
            this->SetLabel(translation);
    }

    void Label::eventThemeChanged(ThemeEvent& event)
    {
        this->processTheme();
    }

    void Label::eventLanguageChanged(LanguageEvent& event)
    {
        this->processLanguage();
    }

    // Auto wrapping label

    LabelAutoWrap::LabelAutoWrap(wxWindow* parent,
        wxWindowID id,
        const wxString& label,
        const wxPoint& pos,
        const wxSize& size,
        long style,
        const wxString& name)
        : Label(parent, id, label, pos, size, style, name)
    {
        this->Bind(wxEVT_SIZE, &LabelAutoWrap::eventSize, this);
    }

    void LabelAutoWrap::SetLabel(const wxString& label)
    {
        this->isUpdatingText = true;

        wxWindow* parent = this->GetParent();
        if (parent && !this->isWrapping)
        {
            int width = parent->GetClientSize().GetWidth();

            Wrapper wrapper(this, label, width);
            Label::SetLabel(wrapper.getText());
        }
        else
            Label::SetLabel(label);

        if (!this->isWrapping)
        {
            this->originalText = label;
        }

        this->isUpdatingText = false;
    }

    void LabelAutoWrap::wrapText()
    {
        wxWindow* parent = this->GetParent();
        if (!parent)
            return;

        int width = parent->GetClientSize().GetWidth();

        this->isWrapping = true;
        Wrapper wrapper(this, this->originalText, width);
        this->SetLabel(wrapper.getText());
        this->isWrapping = false;
    }

    void LabelAutoWrap::eventSize(wxSizeEvent& event)
    {
        if (!this->autoWrap || this->isUpdatingText || this->isWrapping)
            return;

        this->wrapText();
    }
}