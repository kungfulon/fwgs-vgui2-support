#ifndef IINPUTINTERNAL_H
#define IINPUTINTERNAL_H

#include "IInput.h"

namespace vgui2 {
	class IInputInternal : public IInput {
	public:
		virtual void RunFrame() = 0;
		virtual void UpdateMouseFocus(int, int) = 0;
		virtual void PanelDeleted(VPANEL) = 0;
		virtual void InternalCursorMoved(int, int) = 0;
		virtual void InternalMousePressed(enum MouseCode) = 0;
		virtual void InternalMouseDoublePressed(enum MouseCode) = 0;
		virtual void InternalMouseReleased(enum MouseCode) = 0;
		virtual void InternalMouseWheeled(int) = 0;
		virtual void InternalKeyCodePressed(enum KeyCode) = 0;
		virtual void InternalKeyCodeTyped(enum KeyCode) = 0;
		virtual void InternalKeyTyped(wchar_t) = 0;
		virtual void InternalKeyCodeReleased(enum KeyCode) = 0;
		virtual HInputContext CreateInputContext() = 0;
		virtual void DestroyInputContext(HInputContext) = 0;
		virtual void AssociatePanelWithInputContext(HInputContext, VPANEL) = 0;
		virtual void ActivateInputContext(HInputContext) = 0;
	};
}

#define VGUI_INPUTINTERNAL_INTERFACE_VERSION "VGUI_InputInternal001"

#endif
