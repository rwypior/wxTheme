#pragma once

#include "control.h"
#include "theme.h"

#include "wxt/wxt.h"

#include <wx/wx.h>

namespace wxt
{
	class MenuBar : public Control, public wxMenuBar
	{
	public:
		static constexpr char MenuType[] = "menubar";
		static constexpr char MenuItemType[] = "menuitem";

	public:
		class MenuBarRenderer
		{
		public:
			MenuBarRenderer(MenuBar* menubar);
			~MenuBarRenderer();

			static MenuBar* getCurrentMenuBar();

		private:
			static MenuBar* currentMenuBar;
		};

	public:
		MenuBar();
		MenuBar(long style);
		MenuBar(size_t n, wxMenu* menus[], const wxString titles[], long style = 0);

		virtual Selector getSelector() const override;
		Selector getSelectorItem() const;

		virtual bool Append(wxMenu* menu, const wxString& title) wxOVERRIDE;

	protected:
		void setup();

		void createDictionary(wxMenu* menu);
		void createDictionary(wxMenuItem* menu);

		void translateMenu(wxMenu* menu);

	private:
		void processLanguage();

		virtual void eventLanguageChanged(LanguageEvent& event) override;

	private:
		Selector selector;
		Selector selectorItem;

		std::unordered_map<wxMenu*, wxString> menuDictionary;
		std::unordered_map<wxMenuItem*, wxString> menuItemDictionary;
	};

#ifdef WXT_WINDOWS

#	define WM_UAHDESTROYWINDOW		0x0090
#	define WM_UAHDRAWMENU			0x0091
#	define WM_UAHDRAWMENUITEM		0x0092
#	define WM_UAHINITMENU			0x0093
#	define WM_UAHMEASUREMENUITEM	0x0094
#	define WM_UAHNCPAINTMENUPOPUP	0x0095

	bool UAHWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam, LRESULT* lr);

	typedef union tagUAHMENUITEMMETRICS
	{
		struct
		{
			DWORD cx;
			DWORD cy;
		} rgsizeBar[2];

		struct
		{
			DWORD cx;
			DWORD cy;
		} rgsizePopup[4];
	} UAHMENUITEMMETRICS;

	typedef struct tagUAHMENUPOPUPMETRICS
	{
		DWORD rgcx[4];
		DWORD fUpdateMaxWidths : 2;
	} UAHMENUPOPUPMETRICS;

	typedef struct tagUAHMENU
	{
		HMENU hmenu;
		HDC hdc;
		DWORD dwFlags;
	} UAHMENU;

	typedef struct tagUAHMENUITEM
	{
		int iPosition;
		UAHMENUITEMMETRICS umim;
		UAHMENUPOPUPMETRICS umpm;
	} UAHMENUITEM;

	typedef struct UAHDRAWMENUITEM
	{
		DRAWITEMSTRUCT dis;
		UAHMENU um;
		UAHMENUITEM umi;
	} UAHDRAWMENUITEM;

	typedef struct tagUAHMEASUREMENUITEM
	{
		MEASUREITEMSTRUCT mis;
		UAHMENU um;
		UAHMENUITEM umi;
	} UAHMEASUREMENUITEM;
#endif
}