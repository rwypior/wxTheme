#include "wxtexamplemainwindow.h"

#include "wxt/theme.h"

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
	this->m_language_combo->Insert("English", this->m_language_combo->GetCount(), new wxStringClientData(""));
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