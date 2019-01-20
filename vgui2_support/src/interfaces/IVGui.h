#ifndef IVGUI_H
#define IVGUI_H

#include <interface.h>
#include "VGUI2.h"

namespace vgui2 {
	class IVGui : public IBaseInterface {
	public:
		virtual bool Init(CreateInterfaceFn *, int) = 0;
		virtual void Shutdown() = 0;
		virtual void Start() = 0;
		virtual void Stop() = 0;
		virtual bool IsRunning() = 0;
		virtual void RunFrame() = 0;
		virtual void ShutdownMessage(unsigned int) = 0;
		virtual VPANEL AllocPanel() = 0;
		virtual void FreePanel(VPANEL) = 0;
		virtual void DPrintf(const char  *, ...) = 0;
		virtual void DPrintf2(const char  *, ...) = 0;
		virtual void SpewAllActivePanelNames() = 0;
		virtual HPanel PanelToHandle(VPANEL) = 0;
		virtual VPANEL HandleToPanel(HPanel) = 0;
		virtual void MarkPanelForDeletion(VPANEL) = 0;
		virtual void AddTickSignal(VPANEL, int) = 0;
		virtual void RemoveTickSignal(VPANEL) = 0;
		virtual void PostMessage(VPANEL, class KeyValues *, VPANEL, float) = 0;
		virtual HContext CreateContext() = 0;
		virtual void DestroyContext(HContext) = 0;
		virtual void AssociatePanelWithContext(HContext, VPANEL) = 0;
		virtual void ActivateContext(HContext) = 0;
		virtual void SetSleep(bool) = 0;
		virtual bool GetShouldVGuiControlSleep() = 0;
	};
}

#define VGUI_IVGUI_INTERFACE_VERSION "VGUI_ivgui006"

#endif // IVGUI_H
