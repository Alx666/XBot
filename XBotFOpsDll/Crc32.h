

#pragma once

#include <windows.h>

class CCrc32
{
public:
	CCrc32(void);
	~CCrc32(void);

	void Init(void);
	void Free(void);
	DWORD GetCrc32(BYTE *pData, unsigned int size);
	DWORD *m_pdwCrc32Table;

};
