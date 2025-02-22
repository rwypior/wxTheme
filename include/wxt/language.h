#ifndef _h_wxtheme_language
#define _h_wxtheme_language

#include <wx/wx.h>

#include <memory>

namespace wxt
{
	wxString translate(const wxString& str);

	class LanguageEvent : public wxCommandEvent
	{
	public:
		LanguageEvent(wxEventType eventType);
		LanguageEvent* Clone() const;
	};

	class Language
	{
	public:
		virtual ~Language() = default;

		static Language& getInstance();
		static Language& initialize();

		static wxString defaultlangdir();
		static wxString defaultCatalog();

		void refreshRecursively(wxWindow* pWindow);
		void refreshEverything();

		virtual bool loadLanguage(const wxString& path, bool refresh = false);
		virtual bool loadLanguage(long language, const wxString& catalog, bool refresh = false);

		void addLookupPath(const wxString& path);
		void setLookupPaths(const wxVector<wxString>& paths);
		const wxVector<wxString>& getLookupPaths() const;

		void setDefaultLanguage(const wxString& lang);

		wxVector<std::pair<wxString, wxString>> getAvailableLanguages(bool useNativeNames = false);

	private:
		Language();

		wxVector<wxString> lookupPaths;
		wxString defaultLanguage = "en";
		
		std::unique_ptr<wxLocale> locale = nullptr;
	};
}

wxDECLARE_EVENT(wxtEVT_LANGUAGE_CHANGED, wxt::LanguageEvent);

#endif