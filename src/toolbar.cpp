#include "wxt/toolbar.h"
#include "wxt/utils.h"

#include <wx/wx.h>
#include <wx/dataview.h>
#include <wx/itemattr.h>
#include <wx/headerctrl.h>

#include <vector>

namespace wxt
{
    Toolbar::Toolbar()
        : wxToolBar()
    {
        this->setup();
    }

    Toolbar::Toolbar(wxWindow* parent,
        wxWindowID id,
        const wxPoint& pos,
        const wxSize& size,
        long style,
        const wxString& name)
        : wxToolBar(parent, id, pos, size, style, name)
    {
        this->setup();
    }

    Selector Toolbar::getSelector() const
    {
        return this->selector;
    }

    void Toolbar::setup()
    {
        this->selector.type = ToolbarType;

        this->defaultBackgroundColor = this->GetBackgroundColour();
        this->defaultTextColor = this->GetForegroundColour();

        this->Bind(wxtEVT_THEME_CHANGED, &Toolbar::eventThemeChanged, this);
        this->Bind(wxEVT_NC_PAINT, &Toolbar::eventNcPaint, this);
        this->Bind(wxEVT_PAINT, &Toolbar::eventPaint, this);

        Theme& theme = Theme::getInstance();
        if (theme.isEnabled())
        {
            this->processTheme();
        }
    }

    void Toolbar::processTheme()
    {
        Theme& theme = Theme::getInstance();
        this->SetBackgroundColour(either(theme.getBackgroundColor(this->selector), this->defaultBackgroundColor));
        this->SetForegroundColour(either(theme.getTextColor(this->selector), this->defaultTextColor));
    }

    void Toolbar::eventThemeChanged(ThemeEvent& event)
    {
        this->processTheme();
    }

    void Toolbar::eventNcPaint(wxNcPaintEvent& event)
    {
        Theme& theme = Theme::getInstance();
        if (theme.isEnabled())
        {
            wxWindowDC dc(this);

            wxRect rect = this->GetClientRect();
            dc.SetBrush(*wxTRANSPARENT_BRUSH);
            //dc.SetPen(wxPen(gs.getBackgroundColor(GuiStyle::Element::TreeCtrl), 3));
            dc.SetPen(wxPen(wxColour(255, 0, 0), 3));
            //dc.DrawLine()
            dc.DrawRectangle(rect);
        }
    }

    void Toolbar::eventPaint(wxPaintEvent& event)
    {
        Theme& theme = Theme::getInstance();
        if (theme.isEnabled())
        {
            wxPaintDC dc(this);

            wxRect rect = this->GetClientRect();
            dc.SetBrush(*wxTRANSPARENT_BRUSH);
            //dc.SetPen(wxPen(gs.getBackgroundColor(GuiStyle::Element::TreeCtrl), 3));
            dc.SetPen(wxPen(wxColour(255, 0, 0), 3));
            //dc.DrawLine()
            dc.DrawRectangle(rect);
        }
    }
}