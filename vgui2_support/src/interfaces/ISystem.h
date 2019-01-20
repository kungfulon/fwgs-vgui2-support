#ifndef ISYSTEM_H
#define ISYSTEM_H

#include <interface.h>

namespace vgui2 {
	class ISystem : public IBaseInterface {
	public:
		virtual void Shutdown() = 0;
		virtual void RunFrame() = 0;
		virtual void ShellExecute(const char  *, const char  *) = 0;
		virtual double GetFrameTime() = 0;
		virtual double GetCurrentTime() = 0;
		virtual long int GetTimeMillis() = 0;
		virtual int GetClipboardTextCount() = 0;
		virtual void SetClipboardText(const char  *, int) = 0;
		virtual void SetClipboardText(const wchar_t  *, int) = 0;
		virtual int GetClipboardText(int, char *, int) = 0;
		virtual int GetClipboardText(int, wchar_t *, int) = 0;
		virtual bool SetRegistryString(const char  *, const char  *) = 0;
		virtual bool GetRegistryString(const char  *, char *, int) = 0;
		virtual bool SetRegistryInteger(const char  *, int) = 0;
		virtual bool GetRegistryInteger(const char  *, int &) = 0;
		virtual class KeyValues * GetUserConfigFileData(const char  *, int) = 0;
		virtual void SetUserConfigFile(const char  *, const char  *) = 0;
		virtual void SaveUserConfigFile() = 0;
		virtual bool SetWatchForComputerUse(bool) = 0;
		virtual double GetTimeSinceLastUse() = 0;
		virtual int GetAvailableDrives(char *, int) = 0;
		virtual bool CommandLineParamExists(const char  *) = 0;
		virtual const char  * GetFullCommandLine() = 0;
		virtual bool GetCurrentTimeAndDate(int *, int *, int *, int *, int *, int *, int *) = 0;
		virtual double GetFreeDiskSpace(const char  *) = 0;
		virtual bool CreateShortcut(const char  *, const char  *, const char  *, const char  *, const char  *) = 0;
		virtual bool GetShortcutTarget(const char  *, char *, char *, int) = 0;
		virtual bool ModifyShortcutTarget(const char  *, const char  *, const char  *, const char  *) = 0;
		virtual bool GetCommandLineParamValue(const char  *, char *, int) = 0;
		virtual bool DeleteRegistryKey(const char  *) = 0;
		virtual const char  * GetDesktopFolderPath() = 0;
		virtual enum KeyCode KeyCode_VirtualKeyToVGUI(int) = 0;
		virtual int KeyCode_VGUIToVirtualKey(enum KeyCode) = 0;
	};
}

#define VGUI_SYSTEM_INTERFACE_VERSION "VGUI_System009"

#endif // ISYSTEM_H
