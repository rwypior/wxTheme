#pragma once

#include "theme.h"
#include "control.h"
#include "wxt/wxt.h"

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

        void initTheme();

    protected:
        void setup();
        void processTheme();

    private:
        void eventThemeChanged(ThemeEvent& event);

        void eventNcPaint(wxNcPaintEvent& event);

#ifdef WXT_WINDOWS
        void eventPaintHeader(wxPaintEvent& event);
#endif

    private:
        Selector selector;
        Selector selectorHeader;

        wxColour defaultBackgroundColor;
        wxColour defaultTextColor;

        wxString emptyMessage;
        wxWindow* headerCtrl;
    };
}