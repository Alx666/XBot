

#include "XBot.h"
#include "FAKE_IDirect3DTexture8.h"
#include "FAKE_IDirect3D8.h"

#ifdef TEST
	#include <stdio.h>
	extern FILE* logfile;
#endif

				

extern FAKE_IDirect3DDevice8 *pFAKE_D3DDevice8;		


HRESULT __stdcall FAKE_IDirect3DTexture8::LockRect(UINT Level, D3DLOCKED_RECT* pLockedRect, CONST RECT* pRect, DWORD Flags)
{
/*	#ifdef TEST
			char str[64];
			sprintf(str,"\n-> Texture LOCKED , Total Amount : %i",xbot.TexturesList.size());
			fwrite(str,sizeof(char),strlen(str),logfile);
	#endif*/
	
	if (Level == 0 && pRect == NULL)
	{
		//Save texture information
		pLastLockedRect = pLockedRect;
		//m_pLastRect = pRect;
		bLocked = true;

	}
	
	return pD3DTexture8->LockRect(Level, pLockedRect, pRect, Flags);
}

HRESULT __stdcall FAKE_IDirect3DTexture8::UnlockRect(UINT Level)
{

	XBot* xbot = XBot::getXBot();
	
	//Analyse texture
	if (bLocked)
	{
		bLocked = false;
		if (Format == 21)
		{
			BYTE *pData = (BYTE*)pLastLockedRect->pBits;
			Crc32 = xbot->Crc32Calculator->GetCrc32(pData, 4 * Width * Height);
	}
		else if (Format == 894720068)	//SVD HUD
		{
			BYTE *pData = (BYTE*)pLastLockedRect->pBits;
			Crc32 = xbot->Crc32Calculator->GetCrc32(pData, 1 * Width * Height);

		}
		else
		{
			BYTE *pData = (BYTE*)pLastLockedRect->pBits;
			Crc32 = xbot->Crc32Calculator->GetCrc32(pData, (int)(0.5 * Width * Height));

		}
	}
	
	return pD3DTexture8->UnlockRect(Level);
}

HRESULT __stdcall FAKE_IDirect3DTexture8::GetDevice(IDirect3DDevice8 **ppDevice)
{
	*ppDevice = (IDirect3DDevice8*)pFAKE_D3DDevice8;
	return D3D_OK;
}

ULONG __stdcall FAKE_IDirect3DTexture8::Release()
{
	ULONG Result = pD3DTexture8->Release();
	return Result;
}

//****************************** FUNCTIONS BELOW ARE PASS-THROUGH ONLY ******************************


HRESULT __stdcall FAKE_IDirect3DTexture8::QueryInterface(REFIID iid, void ** ppvObject)
{
	return pD3DTexture8->QueryInterface(iid, ppvObject);
}

ULONG __stdcall FAKE_IDirect3DTexture8::AddRef(void)
{
	return pD3DTexture8->AddRef();
}

HRESULT __stdcall FAKE_IDirect3DTexture8::AddDirtyRect(CONST RECT* pDirtyRect)
{
	return pD3DTexture8->AddDirtyRect(pDirtyRect);
}

HRESULT __stdcall FAKE_IDirect3DTexture8::GetLevelDesc(UINT Level, D3DSURFACE_DESC* pDesc)
{
	return pD3DTexture8->GetLevelDesc(Level, pDesc);
}

HRESULT __stdcall FAKE_IDirect3DTexture8::GetSurfaceLevel(UINT Level, IDirect3DSurface8** ppSurfaceLevel)
{
	return pD3DTexture8->GetSurfaceLevel(Level, ppSurfaceLevel);
}

HRESULT __stdcall FAKE_IDirect3DTexture8::SetPrivateData(REFGUID refguid, CONST void* pData, DWORD SizeOfData, DWORD Flags)
{
	return pD3DTexture8->SetPrivateData(refguid, pData, SizeOfData, Flags);
}

HRESULT __stdcall FAKE_IDirect3DTexture8::GetPrivateData(REFGUID refguid, void* pData, DWORD* pSizeOfData)
{
	return pD3DTexture8->GetPrivateData(refguid, pData, pSizeOfData);
}

HRESULT __stdcall FAKE_IDirect3DTexture8::FreePrivateData(REFGUID refguid)
{
	return pD3DTexture8->FreePrivateData(refguid);
}

DWORD __stdcall FAKE_IDirect3DTexture8::SetPriority(DWORD PriorityNew)
{
	return pD3DTexture8->SetPriority(PriorityNew);
}

DWORD __stdcall FAKE_IDirect3DTexture8::GetPriority()
{
	return pD3DTexture8->GetPriority();
}

void __stdcall FAKE_IDirect3DTexture8::PreLoad()
{
	pD3DTexture8->PreLoad();
}

D3DRESOURCETYPE __stdcall FAKE_IDirect3DTexture8::GetType()
{
	return pD3DTexture8->GetType();
}

DWORD __stdcall FAKE_IDirect3DTexture8::SetLOD(DWORD LODNew)
{
	return pD3DTexture8->SetLOD(LODNew);
}

DWORD __stdcall FAKE_IDirect3DTexture8::GetLOD()
{
	return pD3DTexture8->GetLOD();
}

DWORD __stdcall FAKE_IDirect3DTexture8::GetLevelCount()
{
	return pD3DTexture8->GetLevelCount();
}


