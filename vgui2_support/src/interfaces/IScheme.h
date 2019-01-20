#ifndef ISCHEME_H
#define ISCHEME_H

#include <interface.h>
#include "VGUI2.h"

namespace vgui2 {
	class IScheme : public IBaseInterface {
	public:
		virtual const char  * GetResourceString(const char  *) = 0;
		virtual class IBorder * GetBorder(const char  *) = 0;
		virtual HFont GetFont(const char  *, bool) = 0;
		virtual class Color GetColor(const char  *, class Color) = 0;
	};
}

#endif // ISCHEME_H
