#ifndef _h_wxtheme_theme
#define _h_wxtheme_theme

#include <wx/wx.h>
#include <wx/xml/xml.h>
#include <wx/dir.h>
#include <wx/string.h>

#include <optional>

namespace wxt
{
	// Events

	class ThemeEvent : public wxCommandEvent
	{
	public:
		ThemeEvent(wxEventType eventType);
		ThemeEvent* Clone() const;
	};

	// Selector

	struct Selector
	{
		Selector(const wxString& type = "")
			: type(type)
		{
		}

		wxString type;
	};

	// Style

	// TODO
	// This style class utilizes XML format to read the
	// properties, turn this to CSS format instead

	class Theme
	{
	public:
		/*enum class Element
		{
			Window,
			Titlebar,
			Panel,
			DockPanelHeader,
			DockPanelButton,
			InfoPanel,
			Label,
			Hyperlink,
			TextCtrl,
			List,
			Checkbox,
			PropertyGrid,
			PropertyGridCategory,
			StatusBar,
			Groupbox,
			TreeCtrl,
			TreeCtrlHeader,
			Button,
			SmallButton,
			MenuBar,
			MenuItem
		};*/

		enum class Property
		{
			Background,
			Text,
			Border,
			Margin,
			IconColor
		};

		enum class State
		{
			Default,
			Hover,
			Pressed,
			Selected,
			Active,
			Disabled,
			Warning,
			Error
		};

	public:
		static Theme& getInstance();

		static wxDir getThemeDirectory();

		void enable();
		void disable();
		bool isEnabled();

		std::optional<wxColour> getBackgroundColor(Selector selector, State state = State::Default);
		std::optional<wxColour> getTextColor(Selector selector, State state = State::Default);
		std::optional<wxColour> getBorderColor(Selector selector, State state = State::Default);
		std::optional<wxColour> getMarginColor(Selector selector, State state = State::Default);
		std::optional<wxColour> getIconColor();
		std::optional<wxString> getMode(Selector selector, State state = State::Default);

		std::optional<wxColour> getColor(Selector selector, Property property, State state);

		Selector getDefaultSelector() const;

		void refreshRecursively(wxWindow* pWindow);
		void refreshEverything();

		void reloadStyle();
		void loadStyle(const wxString& themename, bool refresh = false);

		wxVector<wxString> getAvailableThemes();
		wxString getThemePath(const wxString& themename);

		static wxString translateState(State state);

	protected:
		wxString getValue(const wxString& element, const wxString& property, const wxString& attribute, const wxString& state = "");

	private:
		Selector defaultSelector;

		wxString currentThemePath;
		wxXmlDocument theme;
		bool enabled = false;

		Theme();
	};
}

wxDECLARE_EVENT(wxtEVT_THEME_CHANGED, wxt::ThemeEvent);

#endif