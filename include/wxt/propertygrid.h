#pragma once

#include "control.h"
#include "theme.h"

#include <wx/propgrid/propgrid.h>

namespace wxt
{
    class PropertyGrid : public Control, public wxPropertyGrid
    {
    public:
        static constexpr char PropertyGridType[] = "propertygrid";
        static constexpr char PropertyGridCategoryType[] = "propertygridcategory";

    public:
        PropertyGrid(wxWindow* parent,
            wxWindowID id = wxID_ANY,
            const wxPoint& pos = wxDefaultPosition,
            const wxSize& size = wxDefaultSize,
            long style = wxPG_DEFAULT_STYLE,
            const wxString& name = wxASCII_STR(wxPropertyGridNameStr));

        PropertyGrid(wxWindow* parent,
            const wxString& emptyMessage,
            wxWindowID id = wxID_ANY,
            const wxPoint& pos = wxDefaultPosition,
            const wxSize& size = wxDefaultSize,
            long style = wxPG_DEFAULT_STYLE,
            const wxString& name = wxASCII_STR(wxPropertyGridNameStr));

        virtual Selector getSelector() const override;
        virtual Selector getSelectorCategory() const;

        size_t count() const;

        void refreshCells();

    protected:
        void setup();
        void processTheme();
        void processLanguage();

    private:
        void eventPaint(wxPaintEvent& event);
        void eventNcPaint(wxNcPaintEvent& event);
        void eventThemeChanged(ThemeEvent& event);
        void eventLanguageChanged(LanguageEvent& event);

    private:
        wxString emptyMessage;

        Selector selector;
        Selector selectorCategory;

        // Defaults
        wxColour defaultColEmptySpace;
        wxColour defaultColLine;
        wxColour defaultColMargin;
        
        wxColour defaultColPropBack;
        wxColour defaultColPropFore;

        wxColour defaultColSelBack;
        wxColour defaultColSelFore;
        
        wxColour defaultPropertyDefaultCellBack;
        wxColour defaultPropertyDefaultCellFore;
        
        wxColour defaultCategoryDefaultCellBack;
        wxColour defaultCategoryDefaultCellFore;
        
        wxColour defaultBackgroundColor;
        wxColour defaultForegroundColor;
    };
}