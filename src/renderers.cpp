#include "wxt/renderers.h"
#include "wxt/dataviewtree.h"

namespace wxt
{
    DataViewRenderer::DataViewRenderer(const wxString& varianttype, wxDataViewCellMode mode, int align)
        : wxDataViewIconTextRenderer(varianttype, mode, align)
    {
    }

    Control* DataViewRenderer::getWxtOwner()
    {
        auto owner = GetOwner();
        auto owner2 = owner->GetOwner();
        if (Control* control = dynamic_cast<Control*>(owner2))
            return control;
        else if (!owner2)
            return nullptr;

        auto parent = owner2->GetParent();
        if (Control* control = dynamic_cast<Control*>(parent))
            return control;

        return nullptr;
    }

    bool DataViewRenderer::Render(wxRect rect, wxDC* dc, int state)
    {
        Theme& theme = Theme::getInstance();
        if (theme.isEnabled())
        {
            auto owner = GetOwner();
            auto owner2 = owner->GetOwner();
            auto parent = owner2->GetParent();

            if (Control* control = getWxtOwner())
            {
                dc->SetPen(*wxTRANSPARENT_PEN);

                auto text = this->value.GetText();
                auto extent = dc->GetTextExtent(text);

                if (auto color = theme.getTextColor(control->getSelector()))
                    dc->SetTextForeground(*color);

                RenderText(
                    text,
                    0,
                    wxRect(extent).CentreIn(rect),
                    dc,
                    0);
                return true;
            }
        }

        return wxDataViewIconTextRenderer::Render(rect, dc, state);
    }

    bool DataViewRenderer::SetValue(const wxVariant& value)
    {
        // Seems hacky, but passing value directly to parent function
        // causes crash
        this->value << value;
        return wxDataViewIconTextRenderer::SetValue(wxVariant(wxDataViewIconText{ this->value }));
    }

    bool DataViewRenderer::GetValue(wxVariant& value) const
    {
        return wxDataViewIconTextRenderer::GetValue(value);
    }
}