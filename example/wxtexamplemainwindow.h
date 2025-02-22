#ifndef __wxtexamplemainwindow__
#define __wxtexamplemainwindow__

/**
@file
Subclass of mainwindow, which is generated by wxFormBuilder.
*/

#include "wxtexample.h"

/** Implementing mainwindow */
class wxtexamplemainwindow : public mainwindow
{
public:
	wxtexamplemainwindow( wxWindow* parent );

private:
	void reloadThemeCombo();
	void reloadLanguageCombo();

private:
	void handlerRefreshThemes(wxCommandEvent& event);
	void handlerRefreshLanguages(wxCommandEvent& event);
	void handlerThemeCombo(wxCommandEvent& event);
	void handlerLanguageCombo(wxCommandEvent& event);
};

#endif // __wxtexamplemainwindow__
