#include "wxt/list.h"
#include "wxt/utils.h"

#include <wx/wx.h>
#include <wx/textwrapper.h>

#include <vector>

namespace wxt
{
    List::List(wxWindow* parent, const wxString& emptyMessage, wxWindowID id, const wxPoint& pos, const wxSize& size, long style, const wxValidator& validator, const wxString& name)
        : wxListCtrl(parent, id, pos, size, style, validator, name)
        , emptyMessage(emptyMessage)
    {
        this->setup();
    }

    List::List(wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style, const wxValidator& validator, const wxString& name)
        : wxListCtrl(parent, id, pos, size, style, validator, name)
    {
        this->setup();
    }

    void List::setup()
    {
        this->selector.type = ListType;

        this->defaultBackgroundColor = this->GetBackgroundColour();
        this->defaultTextColor = this->GetForegroundColour();

        this->Bind(wxEVT_PAINT, &List::eventPaint, this);
        this->Bind(wxEVT_NC_PAINT, &List::eventNcPaint, this);
        this->Bind(wxtEVT_THEME_CHANGED, &List::eventThemeChanged, this);
        this->Bind(wxtEVT_LANGUAGE_CHANGED, &List::eventLanguageChanged, this);

        Theme& theme = Theme::getInstance();
        if (theme.isEnabled())
        {
            this->processTheme();
        }
    }

    void List::processTheme()
    {
        Theme& theme = Theme::getInstance();

        auto bg = theme.getBackgroundColor(this->getSelector());
        this->SetBackgroundColour(bg ? *bg : this->defaultBackgroundColor);

        auto fg = theme.getTextColor(this->getSelector());
        this->SetForegroundColour(fg ? *fg : this->defaultTextColor);
    }

    void List::processLanguage()
    {
        this->Refresh();
    }

    void List::eventPaint(wxPaintEvent& event)
    {
        if (this->GetItemCount() == 0)
        {
            int width = this->GetClientRect().GetWidth();

            Wrapper wrapper(this, translate(this->emptyMessage), width);
            const std::vector<wxString>& lines = wrapper.getLines();

            wxPaintDC dc(this);

            unsigned int y = 20;
            int margin = 2;
            for (const wxString& line : lines)
            {
                wxSize lineSize = dc.GetTextExtent(line);
                int center = width / 2 - lineSize.GetWidth() / 2;

                dc.DrawText(line, center, y);

                y += lineSize.y + margin;
            }
        }
    }

    void List::eventNcPaint(wxNcPaintEvent& event)
    {
        Theme& theme = Theme::getInstance();
        if (theme.isEnabled())
        {
            wxWindowDC dc(this);

            wxRect rect = this->GetClientRect();
            dc.SetBrush(*wxTRANSPARENT_BRUSH);
            if (auto fg = theme.getBackgroundColor(this->getSelector()))
                dc.SetPen(wxPen(*fg, 10));

            dc.DrawRectangle(rect);
        }
    }

    void List::eventThemeChanged(ThemeEvent& event)
    {
        this->processTheme();

        this->Refresh();
        this->Update();
    }

    void List::eventLanguageChanged(LanguageEvent& event)
    {
        this->processLanguage();
    }

    // List box

    ListBox::ListBox(wxWindow* parent, wxWindowID id,
        const wxPoint& pos,
        const wxSize& size,
        int n, const wxString choices[],
        long style,
        const wxValidator& validator,
        const wxString& name)
        : wxListBox(parent, id, pos, size, n, choices, style, validator, name)
    {
        this->setup();
    }

    ListBox::ListBox(wxWindow* parent, wxWindowID id,
        const wxPoint& pos,
        const wxSize& size,
        const wxArrayString& choices,
        long style,
        const wxValidator& validator,
        const wxString& name)
        : wxListBox(parent, id, pos, size, choices, style, validator, name)
    {
        this->setup();
    }

    void ListBox::setup()
    {
        this->selector.type = List::ListType;

        this->defaultBackgroundColor = this->GetBackgroundColour();
        this->defaultTextColor = this->GetForegroundColour();

        this->Bind(wxEVT_NC_PAINT, &ListBox::eventNcPaint, this);
        this->Bind(wxtEVT_THEME_CHANGED, &ListBox::eventThemeChanged, this);

        Theme& theme = Theme::getInstance();
        if (theme.isEnabled())
        {
            this->processTheme();
        }
    }

    void ListBox::processTheme()
    {
        Theme& theme = Theme::getInstance();

        auto bg = theme.getBackgroundColor(this->selector);
        this->SetBackgroundColour(bg ? *bg : this->defaultBackgroundColor);

        auto fg = theme.getTextColor(this->selector);
        this->SetForegroundColour(fg ? *fg : this->defaultTextColor);
    }

    void ListBox::eventNcPaint(wxNcPaintEvent& event)
    {
        Theme& theme = Theme::getInstance();
        if (theme.isEnabled())
        {
            wxWindowDC dc(this);

            wxRect rect = this->GetClientRect();
            dc.SetBrush(*wxTRANSPARENT_BRUSH);
            if (auto fg = theme.getBackgroundColor(this->selector))
                dc.SetPen(wxPen(*fg, 10));

            dc.DrawRectangle(rect);
        }
    }

    void ListBox::eventThemeChanged(ThemeEvent& event)
    {
        this->processTheme();

        this->Refresh();
        this->Update();
    }
}