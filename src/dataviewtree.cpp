#include "wxt/dataviewtree.h"
#include "wxt/renderers.h"

#include "wx/wx.h"
#include "wx/dataview.h"
#include "wx/itemattr.h"
#include "wx/headerctrl.h"

#include <vector>

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
    DataViewTreeCtrl::DataViewTreeCtrl()
        : wxDataViewTreeCtrl()
    {
        this->setup();
    }

    DataViewTreeCtrl::DataViewTreeCtrl(wxWindow* parent,
        wxWindowID id,
        const wxPoint& pos,
        const wxSize& size,
        long style,
        const wxValidator& validator)
        : wxDataViewTreeCtrl(parent, id, pos, size, getStyle(style), validator)
    {
        this->setup();
    }

    void DataViewTreeCtrl::setup()
    {
        this->Bind(wxtEVT_THEME_CHANGED, &DataViewTreeCtrl::eventThemeChanged, this);
        this->Bind(wxEVT_NC_PAINT, &DataViewTreeCtrl::eventNcPaint, this);

        this->selector.type = DataViewTreeType;
        this->headerselector.type = DataViewTreeHeaderType;

        this->defaultBackgroundColor = this->GetBackgroundColour();
        this->defaultTextColor = this->GetForegroundColour();
        //this->defaultAlternateRowColor = this->GetAlternateRowColour();
        this->defaultAlternateRowColor = this->GetBackgroundColour();

        Theme& theme = Theme::getInstance();
        if (theme.isEnabled())
        {
            this->processTheme();
        }
    }

    Selector DataViewTreeCtrl::getSelector() const
    {
        return this->selector;
    }

    DataViewRenderer* DataViewTreeCtrl::createRenderer()
    {
        return new wxt::DataViewRenderer(wxt::DataViewRenderer::GetDefaultType(), wxDATAVIEW_CELL_INERT);
    }

    void DataViewTreeCtrl::processTheme()
    {
        Theme& theme = Theme::getInstance();

        auto bg = theme.getBackgroundColor(this->getSelector());
        this->SetBackgroundColour(bg ? *bg : this->defaultBackgroundColor);

        auto fg = theme.getTextColor(this->getSelector());
        this->SetForegroundColour(fg ? *fg : this->defaultTextColor);

        // TODO - add this to style
        this->SetAlternateRowColour(this->GetBackgroundColour());
    }

    void DataViewTreeCtrl::eventThemeChanged(ThemeEvent& event)
    {
        this->processTheme();
    }

    void DataViewTreeCtrl::eventNcPaint(wxNcPaintEvent& event)
    {
        Theme& theme = Theme::getInstance();
        if (theme.isEnabled())
        {
            wxWindowDC dc(this);

            int border = getWidgetBorder(*this);

            wxRect rect = this->GetClientRect();
            rect.height += border;
            rect.width += border;

            dc.SetBrush(*wxTRANSPARENT_BRUSH);
            dc.SetPen(wxPen(this->GetBackgroundColour(), 3));
            dc.DrawRectangle(rect);
        }
    }

    void DataViewTreeCtrl::eventPaintHeader(wxPaintEvent& event)
    {
        Theme& theme = Theme::getInstance();

        if (!theme.isEnabled())
        {
            event.Skip();
            return;
        }

        wxPaintDC dc(this->headerCtrl);

        wxRect rect = this->headerCtrl->GetClientRect();

        Theme::State state = Theme::State::Default;

        if (auto bg = theme.getBackgroundColor(this->headerselector, state))
            dc.SetBrush(wxBrush(*bg));

        dc.SetPen(*wxTRANSPARENT_PEN);

        dc.DrawRectangle(rect);
    }
}