#ifndef _h_wxtheme_control
#define _h_wxtheme_control

#include "theme.h"
#include "language.h"

namespace wxt
{
	// Base control

	class Control
	{
	public:
		virtual Selector getSelector() const = 0;
	};
}

#endif