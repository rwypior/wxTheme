#include "wxt/staticline.h"
#include "wxt/utils.h"

#include <wx/settings.h>

namespace wxt
{
    StaticLine::StaticLine()
        : wxStaticLine()
    {
        this->setup();
    }

    StaticLine::StaticLine(wxWindow* parent,
        wxWindowID id,
        const wxPoint& pos,
        const wxSize& size,
        long style,
        const wxString& name)
        : wxStaticLine(parent, id, pos, size, style, name)
    {
        this->setup();
    }

    void StaticLine::setup()
    {
        this->defaultBackgroundColor = this->GetBackgroundColour();
        auto asd = this->GetForegroundColour();

        this->Bind(wxEVT_PAINT, &StaticLine::eventPaint, this);
        this->Bind(wxEVT_NC_PAINT, &StaticLine::eventNcPaint, this);

        this->selector.type = LineType;
    }

    Selector StaticLine::getSelector() const
    {
        return this->selector;
    }

    // NOTE - When using either paint or nc-paint alone it doesn't seem to work
    // however using them together seems to work fine, need to investigate

    void StaticLine::paint(wxDC& dc)
    {
        Theme& theme = Theme::getInstance();

        wxRect rect = this->GetClientRect(); // These manipulations shouldn't be necessary
        rect.height = this->GetSize().y + 1;
        rect.width = this->GetSize().x;

        dc.SetBrush(*theme.getBackgroundColor(this->getSelector()));
        dc.SetPen(wxNullPen);
        dc.DrawRectangle(rect);

    }

    void StaticLine::eventPaint(wxPaintEvent& event)
    {
        Theme& theme = Theme::getInstance();
        if (theme.isEnabled())
        {
            wxPaintDC dc(this);
            this->paint(dc);
            event.Skip();
        }
    }

    void StaticLine::eventNcPaint(wxNcPaintEvent& event)
    {
        Theme& theme = Theme::getInstance();
        if (theme.isEnabled())
        {
            wxWindowDC dc(this);
            this->paint(dc);
            event.Skip();
        }
    }
}