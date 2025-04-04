///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version 4.2.1-0-g80c4cb6)
// http://www.wxformbuilder.org/
//
// PLEASE DO *NOT* EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#pragma once

#include <wx/artprov.h>
#include <wx/xrc/xmlres.h>
#include <wx/intl.h>
namespace wxt{ class InfoPanel; }
namespace wxt{ class Label; }

#include "wxt/label.h"
#include "wxt/combobox.h"
#include "wxt/button.h"
#include "wxt/staticline.h"
#include "wxt/panel.h"
#include "wxt/checkbox.h"
#include "wxt/list.h"
#include "wxt/treelist.h"
#include "wxt/propertygrid.h"
#include "wxt/dataviewtree.h"
#include "wxt/menu.h"
#include "wxt/dialog.h"
#include <wx/string.h>
#include <wx/stattext.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/combobox.h>
#include <wx/button.h>
#include <wx/bitmap.h>
#include <wx/image.h>
#include <wx/icon.h>
#include <wx/statline.h>
#include <wx/sizer.h>
#include <wx/panel.h>
#include <wx/checkbox.h>
#include <wx/listctrl.h>
#include <wx/treelist.h>
#include <wx/statbox.h>
#include <wx/propgrid/propgrid.h>
#include <wx/propgrid/advprops.h>
#include <wx/dataview.h>
#include <wx/menu.h>
#include <wx/statusbr.h>
#include <wx/frame.h>
#include <wx/aui/aui.h>
#include <wx/dialog.h>

///////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// Class mainwindow
///////////////////////////////////////////////////////////////////////////////
class mainwindow : public wxt::Frame
{
	private:

	protected:
		enum
		{
			ID_NEW = 6000,
			ID_OPEN,
			ID_SAVE,
			ID_UNDO,
			ID_REDO,
			ID_SETTINGS,
			ID_ABOUT,
		};

		wxt::Panel* m_panel1;
		wxt::Label* m_theme;
		wxt::ComboBox* m_theme_combo;
		wxt::Button* m_refreshThemeCombo;
		wxt::StaticLine* m_staticline2;
		wxt::Label* m_language;
		wxt::ComboBox* m_language_combo;
		wxt::Button* m_refreshLanguageCombo;
		wxt::StaticLine* m_staticline21;
		wxt::ComboBox* m_example_combo;
		wxt::Panel* m_panel2;
		wxt::Panel* m_panel3;
		wxt::Label* m_staticText3;
		wxt::Button* m_button1;
		wxt::Checkbox* m_checkBox1;
		wxt::Panel* m_panel4;
		wxt::Panel* m_panel5;
		wxt::Panel* m_panel11;
		wxt::List* m_listCtrl1;
		wxt::Panel* m_panel12;
		wxt::TreeList* m_treeListCtrl1;
		wxt::Panel* m_panel14;
		wxt::Panel* m_panel6;
		wxt::PropertyGrid* m_propertyGrid1;
		wxPanel* m_panel13;
		wxt::DataViewTreeCtrl* m_dataViewTreeCtrl1;
		wxt::MenuBar* m_menubar;
		wxMenu* file;
		wxMenu* edit;
		wxMenu* tools;
		wxMenu* help;
		wxStatusBar* m_statusBar;

	public:

		mainwindow( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = _("wxTheme example"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 1137,524 ), long style = wxDEFAULT_FRAME_STYLE|wxTAB_TRAVERSAL );
		wxAuiManager m_mgr;

		~mainwindow();

};

///////////////////////////////////////////////////////////////////////////////
/// Class MyDialog1
///////////////////////////////////////////////////////////////////////////////
class MyDialog1 : public wxt::Dialog
{
	private:

	protected:
		wxt::Panel* m_panel7;
		wxt::Label* m_staticText4;
		wxt::Panel* m_panel8;
		wxt::Panel* m_panel9;
		wxt::Button* m_button4;
		wxt::InfoPanel* m_panel10;
		wxt::Label* m_staticText5;
		wxt::Label* m_staticText6;

	public:

		MyDialog1( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxEmptyString, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 584,378 ), long style = wxDEFAULT_DIALOG_STYLE );

		~MyDialog1();

};

