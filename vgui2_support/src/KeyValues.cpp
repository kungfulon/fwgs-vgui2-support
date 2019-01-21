#include <Windows.h>
#include <direct.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <FileSystem.h>
#include "interfaces/IKeyValues.h"
#include "vgui_controls/controls.h"
#include "KeyValues.h"

#define KEYVALUES_TOKEN_SIZE 1024

KeyValues::KeyValues(const char *SetName) {
	Init(SetName);
}

KeyValues::KeyValues(const char *SetName, const char *firstKey, const char *firstValue) {
	Init(SetName);
	SetString(firstKey, firstValue);
}

KeyValues::KeyValues(const char *SetName, const char *firstKey, const wchar_t *firstValue) {
	Init(SetName);
	SetWString(firstKey, firstValue);
}

KeyValues::KeyValues(const char *SetName, const char *firstKey, int firstValue) {
	Init(SetName);
	SetInt(firstKey, firstValue);
}

KeyValues::KeyValues(const char *SetName, const char *firstKey, const char *firstValue, const char *secondKey, const char *secondValue) {
	Init(SetName);
	SetString(firstKey, firstValue);
	SetString(secondKey, secondValue);
}

KeyValues::KeyValues(const char *SetName, const char *firstKey, int firstValue, const char *secondKey, int secondValue) {
	Init(SetName);
	SetInt(firstKey, firstValue);
	SetInt(secondKey, secondValue);
}

const char *KeyValues::GetName() const {
	return vgui2::keyvalues()->GetStringForSymbol(m_iKeyName);
}

int KeyValues::GetNameSymbol() const {
	return m_iKeyName;
}

bool KeyValues::LoadFromFile(IFileSystem *filesystem, const char *resourceName, const char *pathID) {
	FileHandle_t f = filesystem->Open(resourceName, "rb", pathID);

	if (f == FILESYSTEM_INVALID_HANDLE) {
		return false;
	}

	int fileSize = filesystem->Size(f);
	char *buffer = (char *)malloc(fileSize + 1);
	filesystem->Read(buffer, fileSize, f);
	buffer[fileSize] = 0;
	filesystem->Close(f);
	LoadFromBuffer(buffer);
	free(buffer);

	return true;
}

bool KeyValues::SaveToFile(IFileSystem *filesystem, const char *resourceName, const char *pathID) {
	//
	return false;
}

KeyValues *KeyValues::FindKey(const char *keyName, bool bCreate) {
	if (!keyName || !keyName[0]) {
		return this;
	}

	char szBuf[256];
	const char *subStr = strchr(keyName, '/');
	const char *searchStr = keyName;

	if (subStr) {
		int size = subStr - keyName;
		memcpy(szBuf, keyName, size);
		szBuf[size] = 0;
		searchStr = szBuf;
	}

	vgui2::HKeySymbol iSearchStr = vgui2::keyvalues()->GetSymbolForString(searchStr);

	KeyValues *lastItem = NULL;
	KeyValues *dat;
	
	for (dat = m_pSub; dat != NULL; dat = dat->m_pPeer) {
		lastItem = dat;

		if (dat->m_iKeyName == iSearchStr) {
			break;
		}
	}

	if (!dat) {
		if (bCreate) {
			dat = new KeyValues(searchStr);
			
			if (lastItem) {
				lastItem->m_pPeer = dat;
			} else {
				m_pSub = dat;
			}
			
			dat->m_pPeer = NULL;
			m_iDataType = TYPE_NONE;
		}
		else {
			return NULL;
		}
	}

	if (subStr) {
		return dat->FindKey(subStr + 1, bCreate);
	}

	return dat;
}

KeyValues *KeyValues::FindKey(int keySymbol) const {
	for (KeyValues *dat = m_pSub; dat != NULL; dat = dat->m_pPeer) {
		if (dat->m_iKeyName == keySymbol) {
			return dat;
		}
	}

	return NULL;
}

KeyValues *KeyValues::CreateNewKey() {
	int newID = 1;

	for (KeyValues *dat = m_pSub; dat != NULL; dat = dat->m_pPeer) {
		int val = strtol(dat->GetName(), NULL, 10);

		if (newID <= val) {
			newID = val + 1;
		}
	}

	char buf[12];
	snprintf(buf, sizeof(buf), "%d", newID);

	return FindKey(buf, true);
}

void KeyValues::AddSubKey(KeyValues *pSubkey) {
	if (m_pSub == NULL) {
		m_pSub = pSubkey;
	} else {
		KeyValues *pTempDat = m_pSub;

		while (pTempDat->GetNextKey() != NULL) {
			pTempDat = pTempDat->GetNextKey();
		}

		pTempDat->SetNextKey(pSubkey);
	}
}

void KeyValues::RemoveSubKey(KeyValues *subKey) {
	if (!subKey) {
		return;
	}

	if (m_pSub == subKey) {
		m_pSub = subKey->m_pPeer;
	} else {
		KeyValues *kv = m_pSub;

		while (kv->m_pPeer) {
			if (kv->m_pPeer == subKey) {
				kv->m_pPeer = subKey->m_pPeer;
				break;
			}

			kv = kv->m_pPeer;
		}
	}

	subKey->m_pPeer = NULL;
}

KeyValues *KeyValues::GetFirstSubKey() {
	return m_pSub;
}

KeyValues *KeyValues::GetNextKey() {
	return m_pPeer;
}

void KeyValues::SetNextKey(KeyValues *pDat) {
	m_pPeer = pDat;
}

int KeyValues::GetInt(const char *keyName, int defaultValue) {
	KeyValues *dat = FindKey(keyName, false);

	if (dat) {
		switch (dat->m_iDataType) {
		case TYPE_STRING:
			return strtol(dat->m_sValue, NULL, 10);
		case TYPE_WSTRING:
			return wcstol(dat->m_wsValue, NULL, 10);
		case TYPE_FLOAT:
			return (int)dat->m_flValue;
		case TYPE_UINT64:
			return 0;
		case TYPE_INT:
		case TYPE_PTR:
		default:
			return dat->m_iValue;
		};
	}

	return defaultValue;
}

uint64 KeyValues::GetUint64(const char *keyName, uint64 defaultValue) {
	KeyValues *dat = FindKey(keyName, false);
	
	if (dat) {
		switch (dat->m_iDataType) {
		case TYPE_STRING:
			return strtol(dat->m_sValue, NULL, 10);
		case TYPE_WSTRING:
			return wcstol(dat->m_wsValue, NULL, 10);
		case TYPE_FLOAT:
			return (int)dat->m_flValue;
		case TYPE_UINT64:
			return *((uint64 *)dat->m_sValue);
		case TYPE_INT:
		case TYPE_PTR:
		default:
			return dat->m_iValue;
		};
	}

	return defaultValue;
}

float KeyValues::GetFloat(const char *keyName, float defaultValue) {
	KeyValues *dat = FindKey(keyName, false);
	
	if (dat) {
		switch (dat->m_iDataType) {
		case TYPE_STRING:
			return (float)strtod(dat->m_sValue, NULL);
		case TYPE_WSTRING:
			return 0.0f;
		case TYPE_FLOAT:
			return dat->m_flValue;
		case TYPE_INT:
			return (float)dat->m_iValue;
		case TYPE_UINT64:
			return (float)(*((uint64 *)dat->m_sValue));
		case TYPE_PTR:
		default:
			return 0.0f;
		};
	}

	return defaultValue;
}

const char *KeyValues::GetString(const char *keyName, const char *defaultValue) {
	KeyValues *dat = FindKey(keyName, false);
	
	if (dat) {
		char buf[64];

		switch (dat->m_iDataType) {
		case TYPE_FLOAT:
			snprintf(buf, sizeof(buf), "%f", dat->m_flValue);
			SetString(keyName, buf);
			break;
		case TYPE_INT:
		case TYPE_PTR:
			snprintf(buf, sizeof(buf), "%d", dat->m_iValue);
			SetString(keyName, buf);
			break;
		case TYPE_UINT64:
			snprintf(buf, sizeof(buf), "%I64i", *((uint64 *)(dat->m_sValue)));
			SetString(keyName, buf);
			break;
		case TYPE_WSTRING: {
			static char buf[512];
			int result = ::WideCharToMultiByte(CP_UTF8, 0, dat->m_wsValue, -1, buf, 512, NULL, NULL);
			
			if (result) {
				SetString(keyName, buf);
			} else {
				return defaultValue;
			}

			break;
		}
		case TYPE_STRING:
			break;
		default:
			return defaultValue;
		};

		return dat->m_sValue;
	}

	return defaultValue;
}

const wchar_t *KeyValues::GetWString(const char *keyName, const wchar_t *defaultValue) {
	KeyValues *dat = FindKey(keyName, false);

	if (dat) {
		wchar_t wbuf[64];

		switch (dat->m_iDataType) {
		case TYPE_FLOAT:
			swprintf(wbuf, 64, L"%f", dat->m_flValue);
			SetWString(keyName, wbuf);
			break;
		case TYPE_INT:
		case TYPE_PTR:
			swprintf(wbuf, 64, L"%d", dat->m_iValue);
			SetWString(keyName, wbuf);
			break;
		case TYPE_UINT64:
			swprintf(wbuf, 64, L"%I64i", *((uint64 *)(dat->m_sValue)));
			SetWString(keyName, wbuf);
			break;
		case TYPE_WSTRING:
			break;
		case TYPE_STRING: {
			static wchar_t wbuftemp[512];
			int result = ::MultiByteToWideChar(CP_UTF8, 0, dat->m_sValue, -1, wbuftemp, 512);
			
			if (result) {
				SetWString(keyName, wbuftemp);
			} else {
				return defaultValue;
			}

			break;
		}
		default:
			return defaultValue;
		};

		return dat->m_wsValue;
	}

	return defaultValue;
}

void *KeyValues::GetPtr(const char *keyName, void *defaultValue) {
	KeyValues *dat = FindKey(keyName, false);
	
	if (dat) {
		switch (dat->m_iDataType) {
		case TYPE_PTR:
			return dat->m_pValue;
		case TYPE_WSTRING:
		case TYPE_STRING:
		case TYPE_FLOAT:
		case TYPE_INT:
		case TYPE_UINT64:
		default:
			return NULL;
		};
	}

	return defaultValue;
}

Color KeyValues::GetColor(const char *keyName) {
	Color color(0, 0, 0, 0);
	KeyValues *dat = FindKey(keyName, false);

	if (dat) {
		if (dat->m_iDataType == TYPE_COLOR) {
			color[0] = dat->m_Color[0];
			color[1] = dat->m_Color[1];
			color[2] = dat->m_Color[2];
			color[3] = dat->m_Color[3];
		} else if (dat->m_iDataType == TYPE_FLOAT) {
			color[0] = dat->m_flValue;
		} else if (dat->m_iDataType == TYPE_INT) {
			color[0] = dat->m_iValue;
		} else if (dat->m_iDataType == TYPE_STRING) {
			float a, b, c, d;
			sscanf_s(dat->m_sValue, "%f %f %f %f", &a, &b, &c, &d);
			color[0] = (unsigned char)a;
			color[1] = (unsigned char)b;
			color[2] = (unsigned char)c;
			color[3] = (unsigned char)d;
		}
	}

	return color;
}

bool KeyValues::IsEmpty(const char *keyName) {
	KeyValues *dat = FindKey(keyName, false);
	
	if (!dat) {
		return true;
	}

	if (dat->m_iDataType == TYPE_NONE && dat->m_pSub == NULL) {
		return true;
	}

	return false;
}

void KeyValues::SetWString(const char *keyName, const wchar_t *value) {
	KeyValues *dat = FindKey(keyName, true);
	
	if (dat) {
		delete[] dat->m_wsValue;
		dat->m_wsValue = NULL;

		if (!value) {
			value = L"";
		}

		int len = wcslen(value);
		dat->m_wsValue = new wchar_t[len + 1];
		memcpy(dat->m_wsValue, value, (len + 1) * sizeof(wchar_t));

		dat->m_iDataType = TYPE_WSTRING;
	}
}

void KeyValues::SetString(const char *keyName, const char *value) {
	KeyValues *dat = FindKey(keyName, true);

	if (dat) {
		delete[] dat->m_sValue;
		dat->m_wsValue = NULL;

		if (!value) {
			value = "";
		}

		int len = strlen(value);
		dat->m_sValue = new char[len + 1];
		memcpy(dat->m_sValue, value, len + 1);

		dat->m_iDataType = TYPE_STRING;
	}
}

void KeyValues::SetInt(const char *keyName, int value) {
	KeyValues *dat = FindKey(keyName, true);

	if (dat) {
		dat->m_iValue = value;
		dat->m_iDataType = TYPE_INT;
	}
}

void KeyValues::SetUint64(const char *keyName, uint64 value) {
	KeyValues *dat = FindKey(keyName, true);

	if (dat) {
		delete[] dat->m_sValue;
		m_sValue = NULL;

		dat->m_sValue = new char[sizeof(uint64)];
		*((uint64 *)dat->m_sValue) = value;
		dat->m_iDataType = TYPE_UINT64;
	}
}

void KeyValues::SetFloat(const char *keyName, float value) {
	KeyValues *dat = FindKey(keyName, true);

	if (dat) {
		dat->m_flValue = value;
		dat->m_iDataType = TYPE_FLOAT;
	}
}

void KeyValues::SetPtr(const char *keyName, void *value) {
	KeyValues *dat = FindKey(keyName, true);

	if (dat) {
		dat->m_pValue = value;
		dat->m_iDataType = TYPE_PTR;
	}
}

void KeyValues::SetColor(const char *keyName, Color value) {
	KeyValues *dat = FindKey(keyName, true);

	if (dat) {
		dat->m_iDataType = TYPE_COLOR;
		dat->m_Color[0] = value[0];
		dat->m_Color[1] = value[1];
		dat->m_Color[2] = value[2];
		dat->m_Color[3] = value[3];
	}
}

void *KeyValues::operator new(size_t iAllocSize) {
	return vgui2::keyvalues()->AllocKeyValuesMemory(iAllocSize);
}

void *KeyValues::operator new(size_t iAllocSize, int nBlockUse, const char *pFileName, int nLine) {
	return vgui2::keyvalues()->AllocKeyValuesMemory(iAllocSize);;
}

void KeyValues::operator delete(void *pMem) {
	vgui2::keyvalues()->FreeKeyValuesMemory(pMem);
}

void KeyValues::operator delete(void *pMem, int nBlockUse, const char *pFileName, int nLine) {
	vgui2::keyvalues()->FreeKeyValuesMemory(pMem);
}

KeyValues *KeyValues::MakeCopy() const {
	KeyValues *newKeyValue = new KeyValues(GetName());
	newKeyValue->m_iDataType = m_iDataType;

	switch (m_iDataType) {
	case TYPE_STRING: {
		if (m_sValue) {
			int len = strlen(m_sValue);
			newKeyValue->m_sValue = new char[len + 1];
			memcpy(newKeyValue->m_sValue, m_sValue, len + 1);
		}
	}
	break;
	case TYPE_WSTRING: {
		if (m_wsValue) {
			int len = wcslen(m_wsValue);
			newKeyValue->m_wsValue = new wchar_t[len + 1];
			memcpy(newKeyValue->m_wsValue, m_wsValue, (len + 1) * sizeof(wchar_t));
		}
	}
	break;
	case TYPE_INT:
		newKeyValue->m_iValue = m_iValue;
		break;
	case TYPE_FLOAT:
		newKeyValue->m_flValue = m_flValue;
		break;
	case TYPE_PTR:
		newKeyValue->m_pValue = m_pValue;
		break;
	case TYPE_COLOR:
		newKeyValue->m_Color[0] = m_Color[0];
		newKeyValue->m_Color[1] = m_Color[1];
		newKeyValue->m_Color[2] = m_Color[2];
		newKeyValue->m_Color[3] = m_Color[3];
		break;
	case TYPE_UINT64:
		newKeyValue->m_sValue = new char[sizeof(uint64)];
		memcpy(newKeyValue->m_sValue, m_sValue, sizeof(uint64));
		break;
	};

	KeyValues *pPrev = NULL;

	for (KeyValues *sub = m_pSub; sub != NULL; sub = sub->m_pPeer) {
		KeyValues *dat = sub->MakeCopy();

		if (pPrev) {
			pPrev->m_pPeer = dat;
		} else {
			newKeyValue->m_pSub = dat;
		}

		dat->m_pPeer = NULL;
		pPrev = dat;
	}

	return newKeyValue;
}

void KeyValues::Clear() {
	delete m_pSub;
	m_pSub = NULL;
	m_iDataType = TYPE_NONE;
}

KeyValues::types_t KeyValues::GetDataType(const char *keyName) {
	KeyValues *dat = FindKey(keyName, false);
	
	if (dat) {
		return (types_t)dat->m_iDataType;
	}

	return TYPE_NONE;
}

void KeyValues::deleteThis() {
	delete this;
}

char *ReadToken(char **buffer) {
	//
	return *buffer;
}

void KeyValues::LoadFromBuffer(const char *buffer) {
	//
	//char *pfile = const_cast<char *>(buffer);
	//const char *s = ReadToken(&pfile);
	//
	//if (s) {
	//	m_iKeyName = vgui2::keyvalues()->GetSymbolForString(s);
	//}

	//s = ReadToken(&pfile);

	//if (s && m_iKeyName >= 0 && *s == '{') {
	//	KeyValues::RecursiveLoadFromBuffer(&pfile);
	//}
}

KeyValues::~KeyValues() {
	KeyValues *dat;
	KeyValues *datNext = NULL;
	
	for (dat = m_pSub; dat != NULL; dat = datNext) {
		datNext = dat->m_pPeer;
		dat->m_pPeer = NULL;
		delete dat;
	}

	for (dat = m_pPeer; dat && dat != this; dat = datNext) {
		datNext = dat->m_pPeer;
		dat->m_pPeer = NULL;
		delete dat;
	}

	if (m_iDataType == TYPE_STRING) {
		delete[] m_sValue;
		m_sValue = NULL;
	} else if (m_iDataType == TYPE_WSTRING) {
		delete[] m_wsValue;
		m_wsValue = NULL;
	}
}

void KeyValues::RecursiveSaveToFile(IFileSystem *, CUtlBuffer &, int) {
	//
}

void KeyValues::WriteConvertedString(CUtlBuffer &, const char *) {
	//
}

void KeyValues::RecursiveLoadFromBuffer(char **buffer) {
	//
}

void KeyValues::Init(const char *setName) {
	m_iKeyName = vgui2::keyvalues()->GetSymbolForString(setName);
	m_iDataType = NULL;
	m_pSub = NULL;
	m_pPeer = NULL;
	m_iValue = NULL;
	m_iAllocationSize = 0;
}
