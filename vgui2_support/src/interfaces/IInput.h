#ifndef IINPUT_H
#define IINPUT_H

#include <interface.h>
#include "VGUI2.h"

namespace vgui2 {
	class IInput : public IBaseInterface {
	public:
		virtual void SetMouseFocus(VPANEL) = 0;
		virtual void SetMouseCapture(VPANEL) = 0;
		virtual void GetKeyCodeText(enum KeyCode, char *, int) = 0;
		virtual VPANEL GetFocus() = 0;
		virtual VPANEL GetMouseOver() = 0;
		virtual void SetCursorPos(int, int) = 0;
		virtual void GetCursorPos(int &, int &) = 0;
		virtual bool WasMousePressed(enum MouseCode) = 0;
		virtual bool WasMouseDoublePressed(enum MouseCode) = 0;
		virtual bool IsMouseDown(enum MouseCode) = 0;
		virtual void SetCursorOveride(HCursor) = 0;
		virtual HCursor GetCursorOveride() = 0;
		virtual bool WasMouseReleased(enum MouseCode) = 0;
		virtual bool WasKeyPressed(enum KeyCode) = 0;
		virtual bool IsKeyDown(enum KeyCode) = 0;
		virtual bool WasKeyTyped(enum KeyCode) = 0;
		virtual bool WasKeyReleased(enum KeyCode) = 0;
		virtual VPANEL GetAppModalSurface() = 0;
		virtual void SetAppModalSurface(VPANEL) = 0;
		virtual void ReleaseAppModalSurface() = 0;
		virtual void GetCursorPosition(int &, int &) = 0;
	};
}

#define VGUI_INPUT_INTERFACE_VERSION "VGUI_Input004"

#endif // IINPUT_H
