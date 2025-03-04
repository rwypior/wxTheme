#include "wxt/control.h"

namespace wxt
{
	int Control::getWidgetBorder(wxWindow& window)
	{
		if (auto* sizer = window.GetContainingSizer())
		{
			if (auto* item = sizer->GetItem(&window))
				return item->GetBorder();
		}
		return 0;
	}
}