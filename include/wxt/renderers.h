#ifndef _h_wxtheme_renderers
#define _h_wxtheme_renderers

#include "control.h"

#include <wx/wx.h>
#include <wx/treelist.h>
#include <wx/dataview.h>

namespace wxt
{
    class DataViewRenderer : public wxDataViewIconTextRenderer
    {
    public:
        explicit DataViewRenderer(const wxString& varianttype = GetDefaultType(),
            wxDataViewCellMode mode = wxDATAVIEW_CELL_INERT,
            int align = wxDVR_DEFAULT_ALIGNMENT);

        Control* getWxtOwner();

        //virtual void RenderText(const wxString& text, int xOffset, wxRect cell, wxDC* dc, int state) override;
        virtual bool Render(wxRect rect, wxDC* dc, int state) override;

        virtual bool SetValue(const wxVariant& value) override;
        virtual bool GetValue(wxVariant& value) const override;

    private:
        wxDataViewIconText value;
    };
}

#endif