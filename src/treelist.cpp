#include "wxt/treelist.h"
#include "wxt/utils.h"
#include "wxt/renderers.h"

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

    void TreeList::initTheme()
    {
        wxt::DataViewRenderer* renderer = new wxt::DataViewRenderer(wxt::DataViewRenderer::GetDefaultType(), wxDATAVIEW_CELL_INERT);

        struct Column
        {
            wxString title;
            int width;
            wxAlignment align;
        };

        wxVector<Column> columns;

        for (unsigned int i = 0; i < this->GetDataView()->GetColumnCount(); i++)
        {
            const auto col = this->GetDataView()->GetColumn(i);
            Column cache{ col->GetTitle(), col->GetWidth(), col->GetAlignment() };
            columns.push_back(cache);
        }

        this->ClearColumns();

        size_t i = 0;
        for (const auto& col : columns)
        {
            this->GetDataView()->AppendColumn(new wxDataViewColumn(col.title, renderer, i++, col.width, col.align));
        }
    }

    void TreeList::setup()
    {
        this->selector.type = TreeListType;
        this->selectorHeader.type = TreeListHeaderType;

        this->defaultBackgroundColor = this->GetBackgroundColour();
        this->defaultTextColor = this->GetForegroundColour();

#ifdef WXT_WINDOWS
        auto& children = this->m_view->GenericGetHeader()->GetChildren();
        if (!children.IsEmpty())
        {
            this->headerCtrl = this->m_view->GenericGetHeader()->GetChildren()[0];
            this->headerCtrl->Bind(wxEVT_PAINT, &TreeList::eventPaintHeader, this);
        }
#endif

        this->Bind(wxtEVT_THEME_CHANGED, &TreeList::eventThemeChanged, this);
        this->Bind(wxEVT_NC_PAINT, &TreeList::eventNcPaint, this);

        this->initTheme();

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

        // Doesn't work
        // ==============
        //wxSystemSettings setts;

        //auto headerBk = theme.getBackgroundColor(this->getSelectorHeader());

        //wxItemAttr headerAttr;
        ////headerAttr.SetBackgroundColour(headerBk ? *headerBk : setts.GetColour(wxSYS_COLOUR_LISTBOX));
        //headerAttr.SetBackgroundColour(wxColour(255, 0, 0));
        //
        //this->GetDataView()->SetHeaderAttr(headerAttr);
        //this->GetDataView()->Refresh();
        //this->GetDataView()->Update();

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

#ifdef WXT_WINDOWS
    void TreeList::eventPaintHeader(wxPaintEvent& event)
    {
        Theme& theme = Theme::getInstance();

        if (theme.isEnabled())
        {
            wxPaintDC dc(this->headerCtrl);

            wxRect rect = this->headerCtrl->GetClientRect();

            std::optional<wxColour> backgroundColor;

            if (this->headerCtrl->IsMouseInWindow())
            {
                backgroundColor = theme.getBackgroundColor(this->getSelectorHeader(), Theme::State::Hover);
            }
            else
            {
                backgroundColor = theme.getBackgroundColor(this->getSelectorHeader());
            }

            if (backgroundColor)
                dc.SetBrush(wxBrush(*backgroundColor));
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
#endif
}