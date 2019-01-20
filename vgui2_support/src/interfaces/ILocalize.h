#ifndef ILOCALIZE_H
#define ILOCALIZE_H

#include <FileSystem.h>
#include "VGUI2.h"

namespace vgui2 {
	class ILocalize : public IBaseInterface {
	public:
		virtual bool AddFile(class IFileSystem *, const char  *) = 0;
		virtual void RemoveAll() = 0;
		virtual wchar_t * Find(const char  *) = 0;
		virtual int ConvertANSIToUnicode(const char  *, wchar_t *, int) = 0;
		virtual int ConvertUnicodeToANSI(const wchar_t  *, char *, int) = 0;
		virtual StringIndex_t FindIndex(const char  *) = 0;
		virtual void ConstructString(wchar_t *, int, wchar_t *, int, ...) = 0;
		virtual const char  * GetNameByIndex(StringIndex_t) = 0;
		virtual wchar_t * GetValueByIndex(StringIndex_t) = 0;
		virtual StringIndex_t GetFirstStringIndex() = 0;
		virtual StringIndex_t GetNextStringIndex(StringIndex_t) = 0;
		virtual void AddString(const char  *, wchar_t *, const char  *) = 0;
		virtual void SetValueByIndex(StringIndex_t, wchar_t *) = 0;
		virtual bool SaveToFile(class IFileSystem *, const char  *) = 0;
		virtual int GetLocalizationFileCount() = 0;
		virtual const char  * GetLocalizationFileName(int) = 0;
		virtual const char  * GetFileNameByIndex(StringIndex_t) = 0;
		virtual void ReloadLocalizationFiles(class IFileSystem *) = 0;
		virtual void ConstructString(wchar_t *, int, const char  *, class KeyValues *) = 0;
		virtual void ConstructString(wchar_t *, int, StringIndex_t, class KeyValues *) = 0;
	};
}

#define VGUI_LOCALIZE_INTERFACE_VERSION "VGUI_Localize003"

#endif // ILOCALIZE_H
