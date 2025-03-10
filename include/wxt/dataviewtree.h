#pragma once

#include "control.h"
#include "theme.h"
#include "renderers.h"

#include <wx/treelist.h>
#include <wx/dataview.h>

namespace wxt
{
    class DataViewTreeCtrl : public Control, public wxDataViewTreeCtrl
    {
    public:
        static constexpr char DataViewTreeType[] = "dataviewtree";
        static constexpr char DataViewTreeHeaderType[] = "dataviewtreeheader";

    public:
        DataViewTreeCtrl();
        DataViewTreeCtrl(wxWindow* parent,
            wxWindowID id,
            const wxPoint& pos = wxDefaultPosition,
            const wxSize& size = wxDefaultSize,
            long style = wxTL_DEFAULT_STYLE,
            const wxValidator& validator = wxDefaultValidator);

        virtual Selector getSelector() const override;

        static DataViewRenderer* createRenderer();

    protected:
        void setup();
        void processTheme();

    private:
        void eventThemeChanged(ThemeEvent& event);

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