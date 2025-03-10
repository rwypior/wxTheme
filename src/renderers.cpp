#include "wxt/renderers.h"
#include "wxt/dataviewtree.h"

namespace wxt
{
    DataViewRenderer::DataViewRenderer(const wxString& varianttype, wxDataViewCellMode mode, int align)
        : wxDataViewCustomRenderer(varianttype, mode, align)
    {
        SetMode(mode);
        SetAlignment(align);
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
        auto text = this->value.GetText();
        auto extent = dc->GetTextExtent(text);

        Theme& theme = Theme::getInstance();
        if (theme.isEnabled())
        {
            if (Control* control = getWxtOwner())
            {
                state = 0;
                if (auto color = theme.getTextColor(control->getSelector()))
                    dc->SetTextForeground(*color);
            }
        }

        RenderText(
            text,
            0,
            wxRect(extent).CentreIn(rect),
            dc,
            state);

        return true;
    }

    wxSize DataViewRenderer::GetSize() const
    {
        wxWindow* const dvc = GetView();

        wxSize size = GetTextExtent(this->value.GetText());

        const wxBitmapBundle& bb = this->value.GetBitmapBundle();
        if (bb.IsOk())
            size.x += bb.GetPreferredLogicalSizeFor(dvc).x + dvc->FromDIP(4);
        return size;
    }

    bool DataViewRenderer::SetValue(const wxVariant& value)
    {
        this->value << value;
        return true;
    }

    bool DataViewRenderer::GetValue(wxVariant& value) const
    {
        return false;
    }
}