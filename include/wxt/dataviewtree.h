#pragma once

#include "control.h"
#include "theme.h"

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

        virtual void RenderText(const wxString& text, int xOffset, wxRect cell, wxDC* dc, int state) override;

    private:
        wxString value;
    };

    class DataViewTreeCtrl : public Control, public wxDataViewTreeCtrl
    {
    public:
        static constexpr char DataViewTreeType[] = "treectrl";
        static constexpr char DataViewTreeHeaderType[] = "treectrlheader";

    public:
        DataViewTreeCtrl();
        DataViewTreeCtrl(wxWindow* parent,
            wxWindowID id,
            const wxPoint& pos = wxDefaultPosition,
            const wxSize& size = wxDefaultSize,
            long style = wxTL_DEFAULT_STYLE,
            const wxValidator& validator = wxDefaultValidator);

        virtual Selector getSelector() const override;

    protected:
        void setup();
        void processTheme();

    private:
        virtual void eventThemeChanged(ThemeEvent& event) override;

        void eventNcPaint(wxNcPaintEvent& event);

        void eventPaintHeader(wxPaintEvent& event);

    private:
        Selector selector;
        Selector headerselector;

        wxString emptyMessage;
        wxWindow* headerCtrl;

        wxColour defaultBackgroundColor;
        wxColour defaultTextColor;
        wxColour defaultAlternateRowColor;
    };
}