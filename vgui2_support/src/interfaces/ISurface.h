#ifndef ISURFACE_H
#define ISURFACE_H

#include <interface.h>
#include "VGUI2.h"

class IHTMLChromeController;
class IHTMLResponses;

namespace vgui2 {
	class ISurface : public IBaseInterface {
	public:
		enum SurfaceFeature_e {
			ANTIALIASED_FONTS = 0x1,
			DROPSHADOW_FONTS = 0x2,
			ESCAPE_KEY = 0x3,
			OPENING_NEW_HTML_WINDOWS = 0x4,
			FRAME_MINIMIZE_MAXIMIZE = 0x5,
			DIRECT_HWND_RENDER = 0x6,
		};

		virtual void Shutdown() = 0;
		virtual void RunFrame() = 0;
		virtual VPANEL GetEmbeddedPanel() = 0;
		virtual void SetEmbeddedPanel(VPANEL) = 0;
		virtual void PushMakeCurrent(VPANEL, bool) = 0;
		virtual void PopMakeCurrent(VPANEL) = 0;
		virtual void DrawSetColor(int, int, int, int) = 0;
		virtual void DrawSetColor(class Color) = 0;
		virtual void DrawFilledRect(int, int, int, int) = 0;
		virtual void DrawOutlinedRect(int, int, int, int) = 0;
		virtual void DrawLine(int, int, int, int) = 0;
		virtual void DrawPolyLine(int *, int *, int) = 0;
		virtual void DrawSetTextFont(HFont) = 0;
		virtual void DrawSetTextColor(int, int, int, int) = 0;
		virtual void DrawSetTextColor(class Color) = 0;
		virtual void DrawSetTextPos(int, int) = 0;
		virtual void DrawGetTextPos(int &, int &) = 0;
		virtual void DrawPrintText(const wchar_t  *, int) = 0;
		virtual void DrawUnicodeChar(wchar_t) = 0;
		virtual void DrawUnicodeCharAdd(wchar_t) = 0;
		virtual void DrawFlushText() = 0;
		virtual class IHTML * CreateHTMLWindow(class IHTMLEvents *, VPANEL) = 0;
		virtual void PaintHTMLWindow(class IHTML *) = 0;
		virtual void DeleteHTMLWindow(class IHTML *) = 0;
		virtual void DrawSetTextureFile(int, const char  *, int, bool) = 0;
		virtual void DrawSetTextureRGBA(int, const unsigned char  *, int, int, int, bool) = 0;
		virtual void DrawSetTexture(int) = 0;
		virtual void DrawGetTextureSize(int, int &, int &) = 0;
		virtual void DrawTexturedRect(int, int, int, int) = 0;
		virtual bool IsTextureIDValid(int) = 0;
		virtual int CreateNewTextureID(bool) = 0;
		virtual void GetScreenSize(int &wide, int &tall) = 0;
		virtual void SetAsTopMost(VPANEL, bool) = 0;
		virtual void BringToFront(VPANEL) = 0;
		virtual void SetForegroundWindow(VPANEL) = 0;
		virtual void SetPanelVisible(VPANEL, bool) = 0;
		virtual void SetMinimized(VPANEL, bool) = 0;
		virtual bool IsMinimized(VPANEL) = 0;
		virtual void FlashWindow(VPANEL, bool) = 0;
		virtual void SetTitle(VPANEL, const wchar_t  *) = 0;
		virtual void SetAsToolBar(VPANEL, bool) = 0;
		virtual void CreatePopup(VPANEL panel, bool minimised, bool showTaskbarIcon, bool disabled, bool mouseInput, bool kbInput) = 0;
		virtual void SwapBuffers(VPANEL) = 0;
		virtual void Invalidate(VPANEL) = 0;
		virtual void SetCursor(HCursor) = 0;
		virtual bool IsCursorVisible() = 0;
		virtual void ApplyChanges() = 0;
		virtual bool IsWithin(int, int) = 0;
		virtual bool HasFocus() = 0;
		virtual bool SupportsFeature(SurfaceFeature_e feature) = 0;
		virtual void RestrictPaintToSinglePanel(VPANEL) = 0;
		virtual void SetModalPanel(VPANEL) = 0;
		virtual VPANEL GetModalPanel() = 0;
		virtual void UnlockCursor() = 0;
		virtual void LockCursor() = 0;
		virtual void SetTranslateExtendedKeys(bool) = 0;
		virtual VPANEL GetTopmostPopup() = 0;
		virtual void SetTopLevelFocus(VPANEL) = 0;
		virtual HFont CreateFont() = 0;
		virtual bool AddGlyphSetToFont(HFont, const char  *, int, int, int, int, int, int, int) = 0;
		virtual bool AddCustomFontFile(const char  *) = 0;
		virtual int GetFontTall(HFont font) = 0;
		virtual void GetCharABCwide(HFont font, int ch, int &a, int &b, int &c) = 0;
		virtual int GetCharacterWidth(HFont, int) = 0;
		virtual void GetTextSize(HFont, const wchar_t  *, int &, int &) = 0;
		virtual VPANEL GetNotifyPanel() = 0;
		virtual void SetNotifyIcon(VPANEL, HTexture, VPANEL, const char  *) = 0;
		virtual void PlaySound(const char  *) = 0;
		virtual int GetPopupCount() = 0;
		virtual VPANEL GetPopup(int) = 0;
		virtual bool ShouldPaintChildPanel(VPANEL) = 0;
		virtual bool RecreateContext(VPANEL) = 0;
		virtual void AddPanel(VPANEL) = 0;
		virtual void ReleasePanel(VPANEL) = 0;
		virtual void MovePopupToFront(VPANEL) = 0;
		virtual void MovePopupToBack(VPANEL) = 0;
		virtual void SolveTraverse(VPANEL, bool) = 0;
		virtual void PaintTraverse(VPANEL) = 0;
		virtual void EnableMouseCapture(VPANEL, bool) = 0;
		virtual void GetWorkspaceBounds(int &, int &, int &, int &) = 0;
		virtual void GetAbsoluteWindowBounds(int &, int &, int &, int &) = 0;
		virtual void GetProportionalBase(int &, int &) = 0;
		virtual void CalculateMouseVisible() = 0;
		virtual bool NeedKBInput() = 0;
		virtual bool HasCursorPosFunctions() = 0;
		virtual void SurfaceGetCursorPos(int &, int &) = 0;
		virtual void SurfaceSetCursorPos(int, int) = 0;
		virtual void DrawTexturedPolygon(class VGuiVertex *, int) = 0;
		virtual int GetFontAscent(HFont, wchar_t) = 0;
		virtual void SetAllowHTMLJavaScript(bool) = 0;
		virtual void SetLanguage(const char  *) = 0;
		virtual const char  * GetLanguage() = 0;
		virtual bool DeleteTextureByID(int) = 0;
		virtual void DrawUpdateRegionTextureBGRA(int, int, int, const unsigned char  *, int, int) = 0;
		virtual void DrawSetTextureBGRA(int, const unsigned char  *, int, int) = 0;
		virtual void CreateBrowser(VPANEL, ::IHTMLResponses *, bool, const char  *) = 0;
		virtual void RemoveBrowser(VPANEL, ::IHTMLResponses *) = 0;
		virtual class IHTMLChromeController * AccessChromeHTMLController() = 0;
	};
}

#define VGUI_SURFACE_INTERFACE_VERSION "VGUI_Surface026"

#endif // #ISURFACE_H
