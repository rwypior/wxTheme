#include "wxt/theme.h"
#include "wxt/statusbar.h"

namespace wxt
{
	StatusBarManager::StatusBarManager()
	{
		this->selector.type = StatusBarType;
	}

	Selector StatusBarManager::getSelector() const
	{
		return this->selector;
	}

	void StatusBarManager::registerStatusBar(wxStatusBar* statusBar)
	{
		this->statusBars.insert(statusBar);
	}

	void StatusBarManager::setup()
	{
		Theme& theme = Theme::getInstance();

		if (!this->hasDefault && !this->statusBars.empty())
		{
			this->hasDefault = true;
			this->defaultBackgroundColor = (*this->statusBars.begin())->GetBackgroundColour();
		}
	}

	void StatusBarManager::applyTheme()
	{
		Theme& theme = Theme::getInstance();

		for (wxStatusBar* statusBar : this->statusBars)
		{
			statusBar->SetBackgroundColour(theme.isEnabled() ? *theme.getBackgroundColor(this->getSelector()) : this->defaultBackgroundColor);
		}
	}
}