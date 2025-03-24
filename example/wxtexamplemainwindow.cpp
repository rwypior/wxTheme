#include "wxtexamplemainwindow.h"

#include "wxt/theme.h"
#include "wxt/renderers.h"

namespace
{
	static constexpr char DefaultTheme[] = "<Default>";
}

wxtexamplemainwindow::wxtexamplemainwindow( wxWindow* parent )
	: mainwindow( parent )
{
	this->m_refreshThemeCombo->Bind(wxEVT_BUTTON, &wxtexamplemainwindow::handlerRefreshThemes, this);
	this->m_refreshLanguageCombo->Bind(wxEVT_BUTTON, &wxtexamplemainwindow::handlerRefreshLanguages, this);
	this->m_theme_combo->Bind(wxEVT_COMBOBOX, &wxtexamplemainwindow::handlerThemeCombo, this);
	this->m_language_combo->Bind(wxEVT_COMBOBOX, &wxtexamplemainwindow::handlerLanguageCombo, this);

	this->m_button1->Bind(wxEVT_BUTTON, &wxtexamplemainwindow::handlerButton1, this);

	this->m_propertyGrid1->Append(new wxStringProperty("Example item"));
	this->m_propertyGrid1->Append(new wxStringProperty("Another item"));
	this->m_propertyGrid1->Append(new wxStringProperty("Something else"));

	this->m_listCtrl1->InsertItem(0, "Item 1");
	this->m_listCtrl1->InsertItem(1, "Item 2");
	this->m_listCtrl1->InsertItem(2, "Item 3");
	this->m_listCtrl1->InsertItem(3, "Item 4");

	this->m_treeListCtrl1->AppendColumn("Something");
	this->m_treeListCtrl1->initTheme();

	this->m_treeListCtrl1->AppendItem(this->m_treeListCtrl1->GetRootItem(), "Item A");
	this->m_treeListCtrl1->AppendItem(this->m_treeListCtrl1->GetRootItem(), "Item B");
	this->m_treeListCtrl1->AppendItem(this->m_treeListCtrl1->GetRootItem(), "Item C");
	this->m_treeListCtrl1->AppendItem(this->m_treeListCtrl1->GetRootItem(), "Item D");

	auto c1 = this->m_dataViewTreeCtrl1->AppendContainer(wxDataViewItem(0), "Container A");
	auto c2 = this->m_dataViewTreeCtrl1->AppendContainer(wxDataViewItem(0), "Container B");

	this->m_dataViewTreeCtrl1->AppendItem(c1, "Aaa");
	this->m_dataViewTreeCtrl1->AppendItem(c1, "Bbb");
	this->m_dataViewTreeCtrl1->AppendItem(c1, "Ccc");

	this->m_dataViewTreeCtrl1->AppendItem(c2, "Aaa");
	this->m_dataViewTreeCtrl1->AppendItem(c2, "Bbb");
	this->m_dataViewTreeCtrl1->AppendItem(c2, "Ccc");

	this->m_dataViewTreeCtrl1->ClearColumns();
	this->m_dataViewTreeCtrl1->AppendColumn(new wxDataViewColumn("Notes", wxt::DataViewTreeCtrl::createRenderer(), 0, wxCOL_WIDTH_DEFAULT));

	this->reloadThemeCombo();
	this->reloadLanguageCombo();

	this->enableAuiTheming(this->m_mgr);
	this->enableStatusBarTheming(this->m_statusBar);
	this->enableMenuBarTheming(this->m_menubar);
	this->enableMenuBarLanguage(this->m_menubar);
}

void wxtexamplemainwindow::reloadThemeCombo()
{
	wxt::Theme& theme = wxt::Theme::getInstance();
	auto themes = theme.getAvailableThemes();

	this->m_theme_combo->Clear();
	this->m_theme_combo->Insert(DefaultTheme, this->m_theme_combo->GetCount());
	for (auto& theme : themes)
	{
		this->m_theme_combo->Insert(theme, this->m_theme_combo->GetCount());
	}

	this->m_theme_combo->Select(0);
}

void wxtexamplemainwindow::reloadLanguageCombo()
{
	wxt::Language& lang = wxt::Language::getInstance();
	auto languages = lang.getAvailableLanguages();

	this->m_language_combo->Clear();
	for (auto& language : languages)
	{
		this->m_language_combo->Insert(language.second, this->m_language_combo->GetCount(), new wxStringClientData(language.first));
	}

	this->m_language_combo->Select(0);
}

void wxtexamplemainwindow::handlerRefreshThemes(wxCommandEvent& event)
{
	this->reloadThemeCombo();
}

void wxtexamplemainwindow::handlerRefreshLanguages(wxCommandEvent& event)
{
	this->reloadLanguageCombo();
}

void wxtexamplemainwindow::handlerThemeCombo(wxCommandEvent& event)
{
	wxString themeName = this->m_theme_combo->GetStringSelection();

	wxt::Theme& theme = wxt::Theme::getInstance();

	if (themeName == DefaultTheme)
	{
		theme.disable();
	}
	else
	{
		theme.enable();
		theme.loadStyle(themeName);
	}

	theme.refreshEverything();
}

void wxtexamplemainwindow::handlerLanguageCombo(wxCommandEvent& event)
{
	wxString languagePath = static_cast<wxStringClientData*>(event.GetClientObject())->GetData();

	wxt::Language& lang = wxt::Language::getInstance();
	lang.loadLanguage(languagePath, true);
}

void wxtexamplemainwindow::handlerButton1(wxCommandEvent& event)
{
	MyDialog1* dlg1 = new MyDialog1(this);
	dlg1->Show();
}
