#ifndef IGAMEUIFUNCS_H
#define IGAMEUIFUNCS_H

#include <interface.h>
#include "VGUI2.h"

using namespace vgui2;

class IGameUIFuncs : public IBaseInterface {
public:
	virtual bool IsKeyDown(const char  *, bool &) = 0;
	virtual const char  * Key_NameForKey(int) = 0;
	virtual const char  * Key_BindingForKey(int) = 0;
	virtual enum KeyCode GetVGUI2KeyCodeForBind(const char  *) = 0;
	virtual void GetVideoModes(class vmode_s * *, int *) = 0;
	virtual void GetCurrentVideoMode(int *, int *, int *) = 0;
	virtual void GetCurrentRenderer(char *, int, int *, int *, int *, int *) = 0;
	virtual bool IsConnectedToVACSecureServer() = 0;
	virtual int Key_KeyStringToKeyNum(const char  *) = 0;
};

#define ENGINE_GAMEUIFUNCS_INTERFACE_VERSION "VENGINE_GAMEUIFUNCS_VERSION001"

#endif // IGAMEUIFUNCS_H
