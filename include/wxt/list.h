#pragma once

#include "control.h"
#include "theme.h"

#include <wx/listctrl.h>

namespace wxt
{
    class List : public Control, public wxListCtrl
    {
    public:
        static constexpr char ListType[] = "list";

    public:
        List(wxWindow* parent,
            const wxString& emptyMessage,
            wxWindowID id = wxID_ANY,
            const wxPoint& pos = wxDefaultPosition,
            const wxSize& size = wxDefaultSize,
            long style = wxLC_ICON,
            const wxValidator& validator = wxDefaultValidator,
            const wxString& name = wxASCII_STR(wxListCtrlNameStr));

        List(wxWindow* parent,
            wxWindowID id = wxID_ANY,
            const wxPoint& pos = wxDefaultPosition,
            const wxSize& size = wxDefaultSize,
            long style = wxLC_ICON,
            const wxValidator& validator = wxDefaultValidator,
            const wxString& name = wxASCII_STR(wxListCtrlNameStr));

    protected:
        void setup();
        void processTheme();
        void processLanguage();

    private:
        void eventPaint(wxPaintEvent& event);
        void eventNcPaint(wxNcPaintEvent& event);

        virtual void eventThemeChanged(ThemeEvent& event) override;
        virtual void eventLanguageChanged(LanguageEvent& event) override;

    private:
        Selector selector;

        wxColour defaultBackgroundColor;
        wxColour defaultTextColor;

        wxString emptyMessage;
    };

    class ListBox : public Control, public wxListBox
    {
    public:
        ListBox(wxWindow* parent, wxWindowID id,
            const wxPoint& pos = wxDefaultPosition,
            const wxSize& size = wxDefaultSize,
            int n = 0, const wxString choices[] = NULL,
            long style = 0,
            const wxValidator& validator = wxDefaultValidator,
            const wxString& name = wxASCII_STR(wxListBoxNameStr));

        ListBox(wxWindow* parent, wxWindowID id,
            const wxPoint& pos,
            const wxSize& size,
            const wxArrayString& choices,
            long style = 0,
            const wxValidator& validator = wxDefaultValidator,
            const wxString& name = wxASCII_STR(wxListBoxNameStr));

    protected:
        void setup();
        void processTheme();

    private:
        void eventNcPaint(wxNcPaintEvent& event);

        virtual void eventThemeChanged(ThemeEvent& event) override;

    private:
        Selector selector;

        wxColour defaultBackgroundColor;
        wxColour defaultTextColor;

        wxString emptyMessage;
    };
}