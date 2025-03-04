#include "wxt/theme.h"
#include "wxt/control.h"

#include <wx/filename.h>
#include <wx/stdpaths.h>

namespace wxt
{
	// Event

	ThemeEvent::ThemeEvent(wxEventType eventType)
		: wxCommandEvent(eventType, wxID_ANY)
	{
	}

	ThemeEvent* ThemeEvent::Clone() const
	{
		return new ThemeEvent(*this);
	}

	// Theme

	Theme& Theme::getInstance()
	{
		static Theme theme;
		return theme;
	}

	Theme::Theme()
	{
		this->defaultSelector.type = DefaultType;
		this->reloadStyle();
	}

	void Theme::enable()
	{
		this->enabled = true;
	}

	void Theme::disable()
	{
		this->enabled = false;
	}

	bool Theme::isEnabled()
	{
		return this->enabled;
	}

	std::optional<wxColour> Theme::getBackgroundColor(Selector selector, State state, bool useDefault)
	{
		if (!this->isEnabled())
			return {};

		auto s = translateState(state);
		wxString val = this->getValue(selector.type, "background", "color", s);

		if (val.empty())
			return useDefault ? this->getValue(DefaultType, "background", "color", s) : std::optional<wxColour>{};

		return wxColour(val);
	}

	std::optional<wxColour> Theme::getTextColor(Selector selector, State state, bool useDefault)
	{
		if (!this->isEnabled())
			return {};

		auto s = translateState(state);
		wxString val = this->getValue(selector.type, "text", "color", s);

		if (val.empty())
			return useDefault ? this->getValue(DefaultType, "text", "color", s) : std::optional<wxColour>{};

		return wxColour(val);
	}

	std::optional<wxColour> Theme::getBorderColor(Selector selector, State state, bool useDefault)
	{
		if (!this->isEnabled())
			return {};

		auto s = translateState(state);
		wxString val = this->getValue(selector.type, "border", "color", s);

		if (val.empty())
			return useDefault ? this->getValue(DefaultType, "border", "color", s) : std::optional<wxColour>{};

		return wxColour(val);
	}

	std::optional<wxColour> Theme::getMarginColor(Selector selector, State state, bool useDefault)
	{
		if (!this->isEnabled())
			return {};

		auto s = translateState(state);
		wxString val = this->getValue(selector.type, "margin", "color", s);

		if (val.empty())
			return useDefault ? this->getValue(DefaultType, "margin", "color", s) : std::optional<wxColour>{};

		return wxColour(val);
	}

	std::optional<wxColour> Theme::getIconColor()
	{
		if (!this->isEnabled())
			return {};

		wxString val = this->getValue("svg", "shape", "color");
		if (val.empty())
			return {};

		return wxColour(val);
	}

	std::optional<wxString> Theme::getMode(Selector selector, State state, bool useDefault)
	{
		if (!this->isEnabled())
			return {};

		auto s = translateState(state);
		wxString val = this->getValue(selector.type, "background", "mode", s);

		if (val.empty())
			return useDefault ? this->getValue(DefaultType, "background", "mode", s) : std::optional<wxString>{};

		return val;
	}

	std::optional<wxColour> Theme::getColor(Selector selector, Property property, State state)
	{
		switch (property)
		{
		case Property::Background: return getBackgroundColor(selector, state);
		case Property::Text: return getTextColor(selector, state);
		case Property::Border: return getBorderColor(selector, state);
		case Property::Margin: return getMarginColor(selector, state);
		case Property::IconColor: return getIconColor();
		}

		assert(!"Invalid color property specified");
		return {};
	}

	Selector Theme::getDefaultSelector() const
	{
		return this->defaultSelector;
	}

	void Theme::refreshRecursively(wxWindow* pWindow)
	{
		ThemeEvent event(wxtEVT_THEME_CHANGED);
		pWindow->ProcessWindowEvent(event);

		pWindow->Layout();
		pWindow->Refresh();
		pWindow->Update();

		for (wxWindow* child : pWindow->GetChildren())
		{
			refreshRecursively(child);
		}
	}

	void Theme::refreshEverything()
	{
		this->reloadStyle();

		for (wxWindow* wnd : wxTopLevelWindows)
		{
			refreshRecursively(wnd);
		}
	}

	wxDir Theme::getThemeDirectory()
	{
		wxFileName f(wxFileName(wxStandardPaths::Get().GetExecutablePath()).GetPath(), "themes");
		return wxDir(f.GetFullPath());
	}

	wxVector<wxString> Theme::getAvailableThemes()
	{
		wxDir dir = getThemeDirectory();
		wxArrayString files;
		dir.GetAllFiles(dir.GetName(), &files, "*.xml", wxDIR_FILES);

		wxVector<wxString> result;
		for (const wxString& str : files)
		{
			wxXmlDocument doc(str);
			wxXmlNode* root = doc.GetRoot();
			wxString name;
			if (root->HasAttribute("name"))
				name = root->GetAttribute("name");
			else
				name = wxFileName(str).GetName();
			result.push_back(name.ToStdString());
		}

		return result;
	}

	wxString Theme::getThemePath(const wxString& themename)
	{
		wxDir dir = getThemeDirectory();
		wxArrayString files;
		dir.GetAllFiles(dir.GetName(), &files, "*.xml", wxDIR_FILES);

		for (const wxString& str : files)
		{
			wxXmlDocument doc(str);
			wxXmlNode* root = doc.GetRoot();
			wxString name;
			if (root->HasAttribute("name"))
				name = root->GetAttribute("name");
			else
				name = wxFileName(str).GetName();

			if (name == themename)
				return str.ToStdString();
		}

		return "";
	}

	wxString Theme::getValue(const wxString& element, const wxString& property, const wxString& attribute, const wxString& state, bool strict)
	{
		wxXmlNode* node = this->theme.GetRoot()->GetChildren();

		while (node)
		{
			if (node->GetName() == element)
			{
				node = node->GetChildren();

				if (!state.empty())
				{
					bool found = false;
					while (node)
					{
						auto x = node->GetName().ToStdString();
						if (node->GetName() == "state" && node->HasAttribute("name") && node->GetAttribute("name") == state)
						{
							found = true;
							break;
						}

						node = node->GetNext();
					}

					if (!found)
					{
						if (strict)
							return "";
						else
							return this->getValue(element, property, attribute, "", true);
					}

					node = node->GetChildren();
				}

				while (node)
				{
					if (node->GetName() == property)
					{
						wxXmlAttribute* attrib = node->GetAttributes();
						while (attrib)
						{
							if (attrib->GetName() == attribute)
							{
								auto x = attrib->GetValue().ToStdString();
								return attrib->GetValue();
							}

							attrib = attrib->GetNext();
						}
					}
					else
						node = node->GetNext();
				}
			}
			else
				node = node->GetNext();
		}

		return "";
	}

	void Theme::reloadStyle()
	{
		this->loadStyle(this->currentThemePath);
	}

	void Theme::loadStyle(const wxString& themename, bool refresh)
	{
		this->currentThemePath = themename;
		wxString path;
		wxString usedthemename;

		if (themename.empty())
		{
			wxVector<wxString> themes = this->getAvailableThemes();

			if (themes.empty())
				return;

			usedthemename = themes.front();
		}
		else
			usedthemename = themename;

		path = this->getThemePath(usedthemename);

		if (path.empty())
			return;

		this->theme.Load(path);

		if (refresh)
			this->refreshEverything();
	}

	wxString Theme::translateState(State state)
	{
		switch (state)
		{
		case State::Hover: return "hover";
		case State::Pressed: return "pressed";
		case State::Selected: return "selected";
		case State::Active: return "active";
		case State::Disabled: return "disabled";
		case State::Warning: return "warning";
		case State::Error: return "error";
		}

		return "";
	}
}

wxDEFINE_EVENT(wxtEVT_THEME_CHANGED, wxt::ThemeEvent);