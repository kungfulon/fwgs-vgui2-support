#ifndef CGAMEUIFUNCS_H
#define CGAMEUIFUNCS_H

#include "interfaces/IGameUIFuncs.h"

class CGameUIFuncs : public IGameUIFuncs {
public:
	virtual bool IsKeyDown(const char  *, bool &);
	virtual const char  * Key_NameForKey(int);
	virtual const char  * Key_BindingForKey(int);
	virtual enum KeyCode GetVGUI2KeyCodeForBind(const char  *);
	virtual void GetVideoModes(class vmode_s * *, int *);
	virtual void GetCurrentVideoMode(int *, int *, int *);
	virtual void GetCurrentRenderer(char *, int, int *, int *, int *, int *);
	virtual bool IsConnectedToVACSecureServer();
	virtual int Key_KeyStringToKeyNum(const char  *);
};

#endif // CGAMEUIFUNCS_H
