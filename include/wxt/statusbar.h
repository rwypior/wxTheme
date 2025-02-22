#pragma once
#pragma once

#include <wx/wx.h>
#include <wx/aui/aui.h>

#include <unordered_set>

namespace wxt
{
	class StatusBarManager
	{
	public:
		static constexpr char StatusBarType[] = "statusbar";

	public:
		StatusBarManager();

		Selector getSelector() const;

		void registerStatusBar(wxStatusBar* statusBar);
		void setup();

		void applyTheme();

	private:
		Selector selector;

		std::unordered_set<wxStatusBar*> statusBars;

		bool hasDefault = false;
		wxColour defaultBackgroundColor;
	};
}