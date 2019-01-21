#ifndef KEYVALUES_H
#define KEYVALUES_H

#include <archtypes.h>

class KeyValues {
	enum types_t {
		TYPE_NONE = 0,
		TYPE_STRING = 1,
		TYPE_INT = 2,
		TYPE_FLOAT = 3,
		TYPE_PTR = 4,
		TYPE_WSTRING = 5,
		TYPE_COLOR = 6,
		TYPE_UINT64 = 7,
	};

public:
	KeyValues(const char *);
	KeyValues(const char *, const char *, const char *);
	KeyValues(const char *, const char *, const wchar_t *);
	KeyValues(const char *, const char *, int);
	KeyValues(const char *, const char *, const char *, const char *, const char *);
	KeyValues(const char *, const char *, int, const char *, int);
	virtual const char * GetName() const;
	virtual int GetNameSymbol() const;
	virtual bool LoadFromFile(class IFileSystem *, const char *, const char *);
	virtual bool SaveToFile(class IFileSystem *, const char *, const char *);
	virtual class KeyValues * FindKey(const char *, bool);
	virtual class KeyValues * FindKey(int) const;
	virtual class KeyValues * CreateNewKey();
	void AddSubKey(KeyValues *pSubkey);
	virtual void RemoveSubKey(KeyValues *subKey);
	virtual class KeyValues * GetFirstSubKey();
	virtual class KeyValues * GetNextKey();
	void SetNextKey(KeyValues *pSubkey);
	virtual int GetInt(const char *, int);
	uint64 GetUint64(const char *, uint64);
	virtual float GetFloat(const char *, float);
	virtual const char * GetString(const char *, const char *);
	virtual const wchar_t * GetWString(const char *, const wchar_t *);
	virtual void * GetPtr(const char *, void *);
	class Color GetColor(const char *);
	virtual bool IsEmpty(const char *);
	virtual void SetWString(const char *, const wchar_t *);
	virtual void SetString(const char *, const char *);
	virtual void SetInt(const char *, int);
	void SetUint64(const char *, uint64);
	virtual void SetFloat(const char *, float);
	virtual void SetPtr(const char *, void *);
	void SetColor(const char *, class Color);
	void * operator new(size_t);
	void * operator new(size_t, int, const char *, int);
	void operator delete(void *);
	void operator delete(void *, int, const char *, int);
	virtual class KeyValues * MakeCopy() const;
	virtual void Clear();
	virtual enum types_t GetDataType(const char *);
	virtual void deleteThis();
	void LoadFromBuffer(const char *);
	KeyValues(class KeyValues &);
	~KeyValues();
	void RecursiveSaveToFile(class IFileSystem *, class CUtlBuffer &, int);
	void WriteConvertedString(class CUtlBuffer &, const char *);
	void RecursiveLoadFromBuffer(char * *);
	void Init(const char *);
	void FreeAllocatedValue();
	void AllocateValueBlock(int);

private:
	int m_iKeyName;

	union {
		int m_iValue;
		float m_flValue;
		void * m_pValue;
		char * m_sValue;
		wchar_t *m_wsValue;
		unsigned char m_Color[4];
	};

	unsigned short m_iDataType;
	short m_iAllocationSize;
	KeyValues * m_pPeer;
	KeyValues * m_pSub;
};

#endif // KEYVALUES_H
