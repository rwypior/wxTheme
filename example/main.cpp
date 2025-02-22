#include "wxtexamplemainwindow.h"

#include <wx/wx.h>
#include <wx/cmdline.h>
#include <wx/stdpaths.h>

class WxThemeExample : public wxApp
{
public:
	WxThemeExample();

	virtual bool OnInit() override;
};

wxIMPLEMENT_APP(WxThemeExample);

WxThemeExample::WxThemeExample()
{
	SetVendorName("ScribbleMd");
	SetAppName("ScribbleMd");

	wxStandardPaths& sp = wxStandardPaths::Get();
	sp.UseAppInfo(wxStandardPaths::AppInfo_AppName);
}

bool WxThemeExample::OnInit()
{
	if (!wxApp::OnInit())
		return false;

	wxInitAllImageHandlers();

	wxtexamplemainwindow* window = new wxtexamplemainwindow(nullptr);
	window->Show();

	return true;
}