#pragma once

#include "theme.h"
#include "control.h"

#include "wx/treelist.h"

namespace wxt
{
    class TreeList : public Control, public wxTreeListCtrl
    {
    public:
        static constexpr char TreeListType[] = "treelist";
        static constexpr char TreeListHeaderType[] = "treelistheader";

    public:
        TreeList();
        TreeList(wxWindow* parent,
            wxWindowID id,
            const wxPoint& pos = wxDefaultPosition,
            const wxSize& size = wxDefaultSize,
            long style = wxTL_DEFAULT_STYLE,
            const wxString& name = wxASCII_STR(wxTreeListCtrlNameStr));

        virtual Selector getSelector() const override;
        Selector getSelectorHeader() const;

    protected:
        void setup();
        void processTheme();

    private:
        void eventThemeChanged(ThemeEvent& event) override;

        void eventNcPaint(wxNcPaintEvent& event);

        void eventPaintHeader(wxPaintEvent& event);

    private:
        Selector selector;
        Selector selectorHeader;

        wxColour defaultBackgroundColor;
        wxColour defaultTextColor;

        wxString emptyMessage;
        wxWindow* headerCtrl;
    };
}