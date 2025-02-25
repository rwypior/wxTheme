#include "wxt/treelist.h"
#include "wxt/utils.h"

#include <wx/wx.h>
#include <wx/dataview.h>
#include <wx/itemattr.h>
#include <wx/headerctrl.h>

#include <vector>

namespace wxt
{
    TreeList::TreeList()
        : wxTreeListCtrl()
    {
        this->setup();
    }

    TreeList::TreeList(wxWindow* parent,
        wxWindowID id,
        const wxPoint& pos,
        const wxSize& size,
        long style,
        const wxString& name)
        : wxTreeListCtrl(parent, id, pos, size, style, name)
    {
        this->setup();
    }

    Selector TreeList::getSelector() const
    {
        return this->selector;
    }

    Selector TreeList::getSelectorHeader() const
    {
        return this->selectorHeader;
    }

    void TreeList::setup()
    {
        this->selector.type = TreeListType;
        this->selectorHeader.type = TreeListHeaderType;

        this->defaultBackgroundColor = this->GetBackgroundColour();
        this->defaultTextColor = this->GetForegroundColour();

        auto& children = this->m_view->GenericGetHeader()->GetChildren();
        if (!children.IsEmpty())
        {
            this->headerCtrl = this->m_view->GenericGetHeader()->GetChildren()[0];
            this->headerCtrl->Bind(wxEVT_PAINT, &TreeList::eventPaintHeader, this);
        }

        this->Bind(wxtEVT_THEME_CHANGED, &TreeList::eventThemeChanged, this);
        this->Bind(wxEVT_NC_PAINT, &TreeList::eventNcPaint, this);

        Theme& theme = Theme::getInstance();
        if (theme.isEnabled())
        {
            this->processTheme();
        }
    }

    void TreeList::processTheme()
    {
        Theme& theme = Theme::getInstance();
        this->SetBackgroundColour(either(theme.getBackgroundColor(this->getSelector()), this->defaultBackgroundColor));
        this->SetForegroundColour(either(theme.getTextColor(this->getSelector()), this->defaultTextColor));
    }

    void TreeList::eventThemeChanged(ThemeEvent& event)
    {
        this->processTheme();
    }

    void TreeList::eventNcPaint(wxNcPaintEvent& event)
    {
        Theme& theme = Theme::getInstance();
        if (theme.isEnabled())
        {
            wxWindowDC dc(this);

            wxRect rect = this->GetClientRect();
            dc.SetBrush(*wxTRANSPARENT_BRUSH);
            if (auto color = theme.getBackgroundColor(this->getSelector()))
                dc.SetPen(wxPen(*color, 3));
            dc.DrawRectangle(rect);
        }
    }

    void TreeList::eventPaintHeader(wxPaintEvent& event)
    {
        Theme& theme = Theme::getInstance();

        if (theme.isEnabled())
        {
            wxPaintDC dc(this->headerCtrl);

            wxRect rect = this->headerCtrl->GetClientRect();

            wxColour backgroundColor;

            if (this->headerCtrl->IsMouseInWindow())
            {
                backgroundColor = *theme.getBackgroundColor(this->getSelectorHeader(), Theme::State::Hover);
            }
            else
            {
                backgroundColor = *theme.getBackgroundColor(this->getSelectorHeader());
            }

            dc.SetBrush(wxBrush(backgroundColor));
            dc.SetPen(*wxTRANSPARENT_PEN);

            dc.DrawRectangle(rect);

            if (this->m_view->GetColumnCount() > 0)
            {
                wxString label = this->m_view->GetColumn(0)->GetTitle();
                wxSize extent = dc.GetTextExtent(label);

                if (auto color = theme.getTextColor(this->getSelectorHeader()))
                    dc.SetTextForeground(*color);
                dc.DrawText(label, 8, rect.height / 2 - extent.GetHeight() / 2);
            }
        }
    }
}