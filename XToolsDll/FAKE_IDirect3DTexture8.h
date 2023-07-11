

#pragma once

#include <d3d8.h>

interface FAKE_IDirect3DTexture8 : public IDirect3DTexture8
{
public:
	IDirect3DTexture8 *pD3DTexture8;
	unsigned int Height;
	unsigned int Width;
	unsigned int Format;
	D3DLOCKED_RECT* pLastLockedRect;
	//CONST RECT *m_pLastRect;
	DWORD Crc32;
	bool bLocked;

	HRESULT __stdcall QueryInterface(REFIID iid, void ** ppvObject);
	ULONG __stdcall AddRef(void);
	ULONG __stdcall Release(void);

	/*** IDirect3DBaseTexture8 methods ***/
	HRESULT __stdcall AddDirtyRect(CONST RECT* pDirtyRect);
	HRESULT __stdcall GetLevelDesc(UINT Level, D3DSURFACE_DESC* pDesc);
	HRESULT __stdcall GetSurfaceLevel(UINT Level, IDirect3DSurface8** ppSurfaceLevel);
	HRESULT __stdcall LockRect(UINT Level, D3DLOCKED_RECT* pLockedRect, CONST RECT* pRect, DWORD Flags);
	HRESULT __stdcall UnlockRect(UINT Level);

	HRESULT __stdcall GetDevice(IDirect3DDevice8 **ppDevice);
	HRESULT __stdcall SetPrivateData(REFGUID refguid, CONST void* pData, DWORD SizeOfData, DWORD Flags);
	HRESULT __stdcall GetPrivateData(REFGUID refguid, void* pData, DWORD* pSizeOfData);
	HRESULT __stdcall FreePrivateData(REFGUID refguid);
	DWORD __stdcall SetPriority(DWORD PriorityNew);
	DWORD __stdcall GetPriority();
	void __stdcall PreLoad();
	D3DRESOURCETYPE __stdcall GetType();
	DWORD __stdcall SetLOD(DWORD LODNew);
	DWORD __stdcall GetLOD();
	DWORD __stdcall GetLevelCount();
};

