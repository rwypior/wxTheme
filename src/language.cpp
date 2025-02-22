#include "wxt/language.h"

#include <wx/filename.h>
#include <wx/stdpaths.h>
#include <wx/dir.h>

#include <cassert>

namespace wxt
{
	wxString translate(const wxString& str)
	{
		return wxGetTranslation(wxTRANS_INPUT_STR(str));
	}

	// Event

	LanguageEvent::LanguageEvent(wxEventType eventType)
		: wxCommandEvent(eventType, wxID_ANY)
	{
	}

	LanguageEvent* LanguageEvent::Clone() const
	{
		return new LanguageEvent(*this);
	}

	// Language

	Language::Language()
	{
		this->addLookupPath(this->defaultlangdir());
	}

	Language& Language::getInstance()
	{
		static Language instance;
		return instance;
	}

	wxString Language::defaultlangdir()
	{
		wxFileName f(wxFileName(wxStandardPaths::Get().GetExecutablePath()).GetPath(), "lang");
		return f.GetFullPath();
	}

	void Language::refreshRecursively(wxWindow* pWindow)
	{
		LanguageEvent event(wxtEVT_LANGUAGE_CHANGED);
		pWindow->ProcessWindowEvent(event);

		pWindow->Layout();
		pWindow->Refresh();
		pWindow->Update();

		for (wxWindow* child : pWindow->GetChildren())
		{
			refreshRecursively(child);
		}
	}

	void Language::refreshEverything()
	{
		for (wxWindow* wnd : wxTopLevelWindows)
		{
			refreshRecursively(wnd);
		}
	}

	bool Language::loadLanguage(const wxString & path, bool refresh)
	{
		wxString name;

		if (path.empty())
			name = this->defaultLanguage;
		else
		{
			wxFileName filename(path);
			name = filename.GetName();
		}

		const wxLanguageInfo* info = wxLocale::FindLanguageInfo(name);
		
		return this->loadLanguage(info->Language, name, refresh);
	}

	bool Language::loadLanguage(long language, const wxString& catalog, bool refresh)
	{
		bool result = true;

		if (!wxLocale::IsAvailable(language))
		{
			result = false;
			language = wxLANGUAGE_ENGLISH;
		}

		this->locale = std::make_unique<wxLocale>(language);
		
		for (const wxString& path : this->lookupPaths)
		{
			this->locale->AddCatalogLookupPathPrefix(path);
		}
		
		if (!this->locale->IsLoaded(catalog))
		{
			// TODO - this seems to crash randomly, need to find the fix
			if (!this->locale->AddCatalog(catalog))
				result = false;
		}

		if (!this->locale->IsOk())
			result = false;

		if (result && refresh)
			this->refreshEverything();

		return result;
	}

	void Language::addLookupPath(const wxString& path)
	{
		this->lookupPaths.push_back(path);
	}

	void Language::setLookupPaths(const wxVector<wxString>& paths)
	{
		this->lookupPaths = paths;
	}

	const wxVector<wxString>& Language::getLookupPaths() const
	{
		return this->lookupPaths;
	}

	void Language::setDefaultLanguage(const wxString& lang)
	{
		this->defaultLanguage = lang;
	}

	wxVector<std::pair<wxString, wxString>> Language::getAvailableLanguages(bool useNativeNames)
	{
		wxVector<std::pair<wxString, wxString>> result;

		for (const wxString& path : this->getLookupPaths())
		{
			wxDir dir(path);
			wxArrayString files;

			wxString filename;
			bool cont = dir.GetFirst(&filename, wxEmptyString, wxDIR_DIRS);
			while (cont)
			{
				wxFileName fn(path, filename);
				wxString name = fn.GetName();

				const wxLanguageInfo* info = wxLocale::FindLanguageInfo(name);
				wxString languageName = useNativeNames ? info->DescriptionNative : info->Description;

				result.push_back({ fn.GetFullPath(), languageName});

				cont = dir.GetNext(&filename);
			}
		}

		return result;
	}
}

wxDEFINE_EVENT(wxtEVT_LANGUAGE_CHANGED, wxt::LanguageEvent);