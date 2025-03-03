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
#include "wxt/label.h"
#include "wxt/combobox.h"
#include "wxt/button.h"
#include "wxt/panel.h"
#include "wxt/checkbox.h"
#include "wxt/menu.h"
#include "wxt/dialog.h"
#include "wxt/staticbox.h"
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
#include <wx/statbox.h>
#include <wx/menu.h>
#include <wx/statusbr.h>
#include <wx/frame.h>
#include <wx/aui/aui.h>

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
		wxStaticLine* m_staticline2;
		wxt::Label* m_language;
		wxt::ComboBox* m_language_combo;
		wxt::Button* m_refreshLanguageCombo;
		wxt::Panel* m_panel2;
		wxt::Panel* m_panel3;
		wxt::Label* m_staticText3;
		wxt::Button* m_button1;
		wxt::Checkbox* m_checkBox1;
		wxt::Panel* m_panel4;
		wxPanel* m_panel5;
		wxt::MenuBar* m_menubar;
		wxMenu* file;
		wxMenu* edit;
		wxMenu* tools;
		wxMenu* help;
		wxStatusBar* m_statusBar;

	public:

		mainwindow( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = _("wxTheme example"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 858,524 ), long style = wxDEFAULT_FRAME_STYLE|wxTAB_TRAVERSAL );
		wxAuiManager m_mgr;

		~mainwindow();

};

