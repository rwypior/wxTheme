///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version 4.2.1-0-g80c4cb6)
// http://www.wxformbuilder.org/
//
// PLEASE DO *NOT* EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "wxtexample.h"

///////////////////////////////////////////////////////////////////////////

mainwindow::mainwindow( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxt::Frame( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	m_mgr.SetManagedWindow(this);
	m_mgr.SetFlags(wxAUI_MGR_DEFAULT);

	m_panel1 = new wxt::Panel( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	m_mgr.AddPane( m_panel1, wxAuiPaneInfo() .Left() .Caption( _("Theme") ).PinButton( true ).Dock().Resizable().FloatingSize( wxDefaultSize ).BestSize( wxSize( 250,-1 ) ) );

	wxBoxSizer* bSizer1;
	bSizer1 = new wxBoxSizer( wxVERTICAL );

	m_theme = new wxt::Label( m_panel1, wxID_ANY, _("Theme"), wxDefaultPosition, wxDefaultSize, 0 );
	m_theme->Wrap( -1 );
	bSizer1->Add( m_theme, 0, wxALL, 5 );

	m_theme_combo = new wxt::ComboBox( m_panel1, wxID_ANY, _("Combo!"), wxDefaultPosition, wxDefaultSize, 0, NULL, 0 );
	bSizer1->Add( m_theme_combo, 0, wxALL|wxEXPAND, 5 );

	m_refreshThemeCombo = new wxt::Button( m_panel1, wxID_ANY, _("Refresh list"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer1->Add( m_refreshThemeCombo, 0, wxALL, 5 );

	m_staticline2 = new wxStaticLine( m_panel1, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL );
	bSizer1->Add( m_staticline2, 0, wxEXPAND | wxALL, 5 );

	m_language = new wxt::Label( m_panel1, wxID_ANY, _("Language"), wxDefaultPosition, wxDefaultSize, 0 );
	m_language->Wrap( -1 );
	bSizer1->Add( m_language, 0, wxALL, 5 );

	m_language_combo = new wxt::ComboBox( m_panel1, wxID_ANY, _("Combo!"), wxDefaultPosition, wxDefaultSize, 0, NULL, 0 );
	bSizer1->Add( m_language_combo, 0, wxALL|wxEXPAND, 5 );

	m_refreshLanguageCombo = new wxt::Button( m_panel1, wxID_ANY, _("Refresh list"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer1->Add( m_refreshLanguageCombo, 0, wxALL, 5 );


	m_panel1->SetSizer( bSizer1 );
	m_panel1->Layout();
	bSizer1->Fit( m_panel1 );
	m_panel2 = new wxt::Panel( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	m_mgr.AddPane( m_panel2, wxAuiPaneInfo() .Center() .PinButton( true ).Dock().Resizable().FloatingSize( wxDefaultSize ) );

	wxBoxSizer* bSizer2;
	bSizer2 = new wxBoxSizer( wxHORIZONTAL );

	m_panel3 = new wxt::Panel( m_panel2, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer3;
	bSizer3 = new wxBoxSizer( wxVERTICAL );

	m_staticText3 = new wxt::Label( m_panel3, wxID_ANY, _("Example controls"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText3->Wrap( -1 );
	bSizer3->Add( m_staticText3, 0, wxALL, 5 );

	m_button1 = new wxt::Button( m_panel3, wxID_ANY, _("MyButton"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer3->Add( m_button1, 0, wxALL, 5 );

	m_checkBox1 = new wxt::Checkbox( m_panel3, wxID_ANY, _("Check Me!"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer3->Add( m_checkBox1, 0, wxALL, 5 );


	m_panel3->SetSizer( bSizer3 );
	m_panel3->Layout();
	bSizer3->Fit( m_panel3 );
	bSizer2->Add( m_panel3, 1, wxEXPAND | wxALL, 5 );

	m_panel4 = new wxt::Panel( m_panel2, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer4;
	bSizer4 = new wxBoxSizer( wxVERTICAL );

	m_panel5 = new wxPanel( m_panel4, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxStaticBoxSizer* sbSizer1;
	sbSizer1 = new wxStaticBoxSizer( new wxt::StaticBox( m_panel5, wxID_ANY, _("label") ), wxVERTICAL );


	m_panel5->SetSizer( sbSizer1 );
	m_panel5->Layout();
	sbSizer1->Fit( m_panel5 );
	bSizer4->Add( m_panel5, 1, wxEXPAND | wxALL, 5 );


	m_panel4->SetSizer( bSizer4 );
	m_panel4->Layout();
	bSizer4->Fit( m_panel4 );
	bSizer2->Add( m_panel4, 1, wxEXPAND | wxALL, 5 );


	m_panel2->SetSizer( bSizer2 );
	m_panel2->Layout();
	bSizer2->Fit( m_panel2 );
	m_menubar = new wxt::MenuBar( 0 );
	file = new wxMenu();
	wxMenuItem* newitem;
	newitem = new wxMenuItem( file, ID_NEW, wxString( _("New") ) , wxEmptyString, wxITEM_NORMAL );
	file->Append( newitem );

	wxMenuItem* open;
	open = new wxMenuItem( file, ID_OPEN, wxString( _("Open") ) , wxEmptyString, wxITEM_NORMAL );
	file->Append( open );

	wxMenuItem* save;
	save = new wxMenuItem( file, ID_SAVE, wxString( _("Save") ) , wxEmptyString, wxITEM_NORMAL );
	file->Append( save );

	m_menubar->Append( file, _("File") );

	edit = new wxMenu();
	wxMenuItem* undo;
	undo = new wxMenuItem( edit, ID_UNDO, wxString( _("Undo") ) , wxEmptyString, wxITEM_NORMAL );
	edit->Append( undo );

	wxMenuItem* redo;
	redo = new wxMenuItem( edit, ID_REDO, wxString( _("Redo") ) , wxEmptyString, wxITEM_NORMAL );
	edit->Append( redo );

	m_menubar->Append( edit, _("Edit") );

	tools = new wxMenu();
	wxMenuItem* settings;
	settings = new wxMenuItem( tools, ID_SETTINGS, wxString( _("Settings") ) , wxEmptyString, wxITEM_NORMAL );
	tools->Append( settings );

	m_menubar->Append( tools, _("Tools") );

	help = new wxMenu();
	wxMenuItem* about;
	about = new wxMenuItem( help, ID_ABOUT, wxString( _("About") ) , wxEmptyString, wxITEM_NORMAL );
	help->Append( about );

	m_menubar->Append( help, _("Help") );

	this->SetMenuBar( m_menubar );

	m_statusBar = this->CreateStatusBar( 1, wxSTB_SIZEGRIP, wxID_ANY );

	m_mgr.Update();
	this->Centre( wxBOTH );
}

mainwindow::~mainwindow()
{
	m_mgr.UnInit();

}
