#include "wxt/button.h"
#include "wxt/utils.h"

#include <wx/cshelp.h>

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
    Button::Button(wxWindow* parent,
        wxWindowID id,
        const wxString& label,
        const wxPoint& pos,
        const wxSize& size,
        long style,
        const wxValidator& validator,
        const wxString& name)
        : wxButton(parent, id, label, pos, size, getStyle(style), validator, name)
    {
        this->originalCaption = this->GetLabel();

        this->Bind(wxEVT_PAINT, &Button::eventPaint, this);
        this->Bind(wxEVT_LEFT_DOWN, &Button::eventLmbDown, this);
        this->Bind(wxEVT_LEFT_UP, &Button::eventLmbUp, this);
        this->Bind(wxEVT_ENTER_WINDOW, &Button::eventMouseHover, this);
        this->Bind(wxEVT_LEAVE_WINDOW, &Button::eventMouseLeave, this);
        this->Bind(wxtEVT_LANGUAGE_CHANGED, &Button::eventLanguageChanged, this);

        this->processLanguage();

        this->selector.type = ButtonType;
    }

    Selector Button::getSelector() const
    {
        return this->selector;
    }

    void Button::DoSetToolTipText(const wxString& tip)
    {
        if (this->originalTooltip.empty())
            this->originalTooltip = tip;

        wxButton::DoSetToolTipText(translate(tip));
    }
    
    void Button::processLanguage()
    {
        this->SetLabel(translate(this->originalCaption));
        this->SetToolTip(translate(this->originalTooltip));
    }

    void Button::eventPaint(wxPaintEvent& event)
    {
        Theme& theme = Theme::getInstance();
        if (theme.isEnabled())
        {
            wxPaintDC dc(this);

            Theme::State state = Theme::State::Default;
            if (!this->IsEnabled())
                state = Theme::State::Disabled;
            else if (this->state & ButtonState::Pressed)
                state = Theme::State::Pressed;
            else if (this->state & ButtonState::Hover)
                state = Theme::State::Hover;

            auto backgroundColor = theme.getBackgroundColor(this->getSelector(), state);
            auto borderColor = theme.getBorderColor(this->getSelector(), state);
            auto textColor = theme.getTextColor(this->getSelector(), state);

            if (backgroundColor)
                dc.SetBrush(wxBrush(*backgroundColor));

            if (borderColor)
                dc.SetPen(wxPen(*borderColor));

            if (textColor)
                dc.SetTextForeground(*textColor);
            else if (wxWindow* parent = this->GetParent())
                dc.SetTextForeground(parent->GetForegroundColour());

            dc.SetFont(this->GetFont());

            wxSize size = dc.GetSize();
            wxSize textSize = dc.GetTextExtent(this->GetLabel());
            wxPoint textPoint = calcOriginPoint(size, textSize);

            dc.DrawRectangle(size);
            dc.DrawText(this->GetLabel(), textPoint);

            wxBitmap bmp = this->GetBitmap();
            if (bmp.IsOk())
            {
                dc.DrawBitmap(bmp, this->GetRect().width / 2 - bmp.GetWidth() / 2, this->GetRect().height / 2 - bmp.GetHeight() / 2);
            }
        }
        else
            event.Skip();
    }

    void Button::eventLmbDown(wxMouseEvent& event)
    {
        this->state |= ButtonState::Pressed;
        event.Skip();
    }

    void Button::eventLmbUp(wxMouseEvent& event)
    {
        this->state &= ~ButtonState::Pressed;
        event.Skip();
    }

    void Button::eventMouseHover(wxMouseEvent& event)
    {
        this->state |= ButtonState::Hover;
        event.Skip();
    }

    void Button::eventMouseLeave(wxMouseEvent& event)
    {
        this->state &= ~ButtonState::Hover;
        event.Skip();
    }

    void Button::eventLanguageChanged(LanguageEvent& event)
    {
        this->processLanguage();
    }

    // Small button
	SmallButton::SmallButton()
	{
        this->selector.type = SmallButtonType;
	}

	SmallButton::SmallButton(wxWindow* parent,
        wxWindowID id,
        const wxBitmapBundle& bitmap,
        const wxPoint& pos,
        const wxSize& size,
        long style,
        const wxValidator& validator,
        const wxString& name)
		: wxBitmapButton(parent, id, bitmap, pos, size, style, validator, name)
	{
        this->selector.type = SmallButtonType;

        this->Bind(wxEVT_PAINT, &SmallButton::eventPaint, this);
        this->Bind(wxEVT_LEFT_DOWN, &SmallButton::eventLmbDown, this);
        this->Bind(wxEVT_LEFT_UP, &SmallButton::eventLmbUp, this);
        this->Bind(wxEVT_ENTER_WINDOW, &SmallButton::eventMouseHover, this);
        this->Bind(wxEVT_LEAVE_WINDOW, &SmallButton::eventMouseLeave, this);
        this->Bind(wxtEVT_LANGUAGE_CHANGED, &SmallButton::eventLanguageChanged, this);
	}
  
    Selector SmallButton::getSelector() const
    {
        return this->selector;
    }    
	
	void SmallButton::DoSetToolTipText(const wxString& tip)
    {
        if (this->originalTooltip.empty())
            this->originalTooltip = tip;

        wxBitmapButton::DoSetToolTipText(translate(tip));
    }
    
    void SmallButton::processLanguage()
    {
        this->SetToolTip(translate(this->originalTooltip));
    }

    void SmallButton::eventPaint(wxPaintEvent& event)
    {
        Theme& theme = Theme::getInstance();
        if (theme.isEnabled())
        {
            wxPaintDC dc(this);

            Theme::State state = Theme::State::Default;
            if (!this->IsEnabled())
                state = Theme::State::Disabled;
            else if (this->state & ButtonState::Pressed)
                state = Theme::State::Pressed;
            else if (this->state & ButtonState::Hover)
                state = Theme::State::Hover;

            auto backgroundColor = theme.getBackgroundColor(this->getSelector(), state);
            auto borderColor = theme.getBorderColor(this->getSelector(), state);

            if (backgroundColor)
                dc.SetBrush(wxBrush(*backgroundColor));

            if (borderColor)
                dc.SetPen(wxPen(*borderColor));
 
            wxSize size = dc.GetSize();
 			dc.DrawRectangle(size);

            wxBitmap bmp = this->GetBitmap();
            if (bmp.IsOk())
            {
                dc.DrawBitmap(bmp, this->GetRect().width / 2 - bmp.GetWidth() / 2, this->GetRect().height / 2 - bmp.GetHeight() / 2);
            }
        }
        else
            event.Skip();
    }

    void SmallButton::eventLmbDown(wxMouseEvent& event)
    {
        this->state |= ButtonState::Pressed;
        event.Skip();
    }

    void SmallButton::eventLmbUp(wxMouseEvent& event)
    {
        this->state &= ~ButtonState::Pressed;
        event.Skip();
    }

    void SmallButton::eventMouseHover(wxMouseEvent& event)
    {
        this->state |= ButtonState::Hover;
        event.Skip();
    }

    void SmallButton::eventMouseLeave(wxMouseEvent& event)
    {
        this->state &= ~ButtonState::Hover;
        event.Skip();
    }

    void SmallButton::eventLanguageChanged(LanguageEvent& event)
    {
        this->processLanguage();
    }

}
