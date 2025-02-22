#include "wxt/propertygrid.h"
#include "wxt/utils.h"

namespace
{
    long getStyle(long style)
    {
        wxt::Theme& theme = wxt::Theme::getInstance();
        if (theme.isEnabled())
        {
            //style |= wxNO_BORDER;
        }

        return style;
    }
}

namespace wxt
{
    PropertyGrid::PropertyGrid(wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style, const wxString& name)
        : wxPropertyGrid(parent, id, pos, size, getStyle(style), name)
    {
        this->setup();
    }

    PropertyGrid::PropertyGrid(wxWindow* parent, const wxString& emptyMessage, wxWindowID id, const wxPoint& pos, const wxSize& size, long style, const wxString& name)
        : wxPropertyGrid(parent, id, pos, size, getStyle(style), name)
        , emptyMessage(emptyMessage)
    {
        this->setup();
    }

    Selector PropertyGrid::getSelector() const
    {
        return this->selector;
    }

    Selector PropertyGrid::getSelectorCategory() const
    {
        return this->selectorCategory;
    }

    void PropertyGrid::setup()
    {
        this->selector.type = PropertyGridType;
        this->selectorCategory.type = PropertyGridCategoryType;

        this->defaultColEmptySpace = m_colEmptySpace;
        this->defaultColLine = m_colLine;
        this->defaultColMargin = m_colMargin;

        this->defaultColPropBack = m_colPropBack;
        this->defaultColPropFore = m_colPropFore;

        this->defaultColSelBack = m_colSelBack;
        this->defaultColSelFore = m_colSelFore;

        this->defaultPropertyDefaultCellBack = m_propertyDefaultCell.GetBgCol();
        this->defaultPropertyDefaultCellFore = m_propertyDefaultCell.GetFgCol();

        this->defaultCategoryDefaultCellBack = m_categoryDefaultCell.GetBgCol();
        this->defaultCategoryDefaultCellFore = m_categoryDefaultCell.GetFgCol();

        this->defaultBackgroundColor = this->GetBackgroundColour();
        this->defaultForegroundColor = this->GetForegroundColour();

        Theme& theme = Theme::getInstance();
        if (theme.isEnabled())
        {
            this->processTheme();
        }

        this->Bind(wxEVT_PAINT, &PropertyGrid::eventPaint, this);
        this->Bind(wxEVT_NC_PAINT, &PropertyGrid::eventNcPaint, this);
        this->Bind(wxtEVT_THEME_CHANGED, &PropertyGrid::eventThemeChanged, this);
        this->Bind(wxtEVT_LANGUAGE_CHANGED, &PropertyGrid::eventLanguageChanged, this);
    }

    void PropertyGrid::processTheme()
    {
        Theme& theme = Theme::getInstance();

        m_colEmptySpace = theme.isEnabled() ? *theme.getBackgroundColor(this->getSelector()) : this->defaultColEmptySpace;
        m_colLine = theme.isEnabled() ? *theme.getBorderColor(this->getSelector()) : this->defaultColLine;
        m_colMargin = theme.isEnabled() ? *theme.getMarginColor(this->getSelector()) : this->defaultColMargin;

        m_colPropBack = theme.isEnabled() ? *theme.getBackgroundColor(this->getSelector()) : this->defaultColPropBack;
        m_colPropFore = theme.isEnabled() ? *theme.getTextColor(this->getSelector()) : this->defaultColPropFore;

        m_colSelBack = theme.isEnabled() ? *theme.getBackgroundColor(this->getSelector(), Theme::State::Selected) : this->defaultColSelBack;
        m_colSelFore = theme.isEnabled() ? *theme.getTextColor(this->getSelector(), Theme::State::Selected) : this->defaultColSelFore;

        m_propertyDefaultCell.SetBgCol(theme.isEnabled() ? *theme.getBackgroundColor(this->getSelector()) : this->defaultPropertyDefaultCellBack);
        m_propertyDefaultCell.SetFgCol(theme.isEnabled() ? *theme.getTextColor(this->getSelector()) : this->defaultPropertyDefaultCellFore);

        m_categoryDefaultCell.SetBgCol(theme.isEnabled() ? *theme.getBackgroundColor(this->getSelectorCategory()) : this->defaultCategoryDefaultCellBack);
        m_categoryDefaultCell.SetFgCol(theme.isEnabled() ? *theme.getTextColor(this->getSelectorCategory()) : this->defaultCategoryDefaultCellFore);

        this->SetBackgroundColour(theme.isEnabled() ? *theme.getBackgroundColor(this->getSelector()) : this->defaultBackgroundColor);
        this->SetForegroundColour(theme.isEnabled() ? *theme.getTextColor(this->getSelector()) : this->defaultForegroundColor);

        Refresh();
        Update();

        this->refreshCells();
    }

    void PropertyGrid::processLanguage()
    {
        this->Refresh();
    }

    void PropertyGrid::refreshCells()
    {
        Theme& theme = Theme::getInstance();

        auto it = this->GetIterator(wxPG_ITERATE_ALL);

        do
        {
            auto prop = it.GetProperty();
            if (!prop)
                continue;

            if (prop->IsCategory())
            {
                auto& cell = prop->GetCell(0);
                cell.SetBgCol(theme.isEnabled() ? *theme.getBackgroundColor(this->getSelectorCategory()) : this->defaultCategoryDefaultCellBack);
                cell.SetFgCol(theme.isEnabled() ? *theme.getTextColor(this->getSelectorCategory()) : this->defaultCategoryDefaultCellFore);
            }
            else
            {
                for (unsigned int i = 0; i < this->GetColumnCount(); i++)
                {
                    auto& cell = prop->GetCell(i);
                    cell.SetBgCol(theme.isEnabled() ? *theme.getBackgroundColor(this->getSelector()) : this->defaultPropertyDefaultCellBack);
                    cell.SetFgCol(theme.isEnabled() ? *theme.getTextColor(this->getSelector()) : this->defaultPropertyDefaultCellFore);
                }
            }
        } while (!it++.AtEnd());
    }

    void PropertyGrid::eventThemeChanged(ThemeEvent& event)
    {
        this->processTheme();
    }

    void PropertyGrid::eventLanguageChanged(LanguageEvent& event)
    {
        this->processLanguage();
    }

    size_t PropertyGrid::count() const
    {
        size_t count = 0;
        auto it = this->GetIterator();
        while (!it++.AtEnd())
        {
            count++;
        }
        return count;
    }

    void PropertyGrid::eventPaint(wxPaintEvent& event)
    {
        wxPropertyGrid::OnPaint(event);

        if (this->count() == 0)
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

    void PropertyGrid::eventNcPaint(wxNcPaintEvent& event)
    {
        Theme& theme = Theme::getInstance();
        if (theme.isEnabled())
        {
            wxWindowDC dc(this);

            wxRect rect = this->GetRect();
            dc.SetBrush(*wxTRANSPARENT_BRUSH);
            dc.SetPen(wxPen(*theme.getBackgroundColor(this->getSelector()), 3));
            dc.DrawRectangle(rect);
        }
    }
}