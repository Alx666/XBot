
#include "XBot.h"
#include "FAKE_IDirect3D8.h"
#include "FAKE_IDirect3DDevice8.h"

#ifdef TEXTURE_LOGGER
	#include "XTextureLogger.h"
#endif

#ifdef TEST
	#include <stdio.h>
	extern FILE* logfile;
#endif

extern FAKE_IDirect3D8 FAKE_D3D8;
extern FAKE_IDirect3D8 *pFAKE_D3D8;						
extern IDirect3D8 *pD3D8;
extern FAKE_IDirect3DDevice8 FAKE_D3DDevice8;
extern FAKE_IDirect3DDevice8 *pFAKE_D3DDevice8;		
extern IDirect3DDevice8 *pD3DDevice8;

#ifdef TEXTURE_LOGGER
	extern XTextureLogger *texturelogger;
#endif

HRESULT __stdcall FAKE_IDirect3D8::CreateDevice(UINT Adapter, D3DDEVTYPE DeviceType, HWND hFocusWindow, DWORD BehaviorFlags,
											  D3DPRESENT_PARAMETERS* pPresentationParameters, IDirect3DDevice8** ppReturnedDeviceInterface)
{
	HRESULT Result = 0;
	Result = pD3D8->CreateDevice(Adapter, DeviceType, hFocusWindow, BehaviorFlags, pPresentationParameters, ppReturnedDeviceInterface);

	//Set pointer to original device
	pD3DDevice8 = *ppReturnedDeviceInterface;

	//Return pointer to wrapper
	*ppReturnedDeviceInterface = (IDirect3DDevice8*)&FAKE_D3DDevice8;
	pFAKE_D3DDevice8 = &FAKE_D3DDevice8;

	XBot::getXBot()->setDevice(pD3DDevice8);
	
	
#ifdef TEXTURE_LOGGER
	texturelogger->setDevice(pD3DDevice8);
#endif

	
	
	return Result;
}

ULONG __stdcall FAKE_IDirect3D8::Release(void)
{
	return pD3D8->Release();
}

//****************************** FUNCTIONS BELOW ARE PASS-THROUGH ONLY ******************************

HRESULT __stdcall FAKE_IDirect3D8::QueryInterface(REFIID iid, void ** ppvObject)
{
	return pD3D8->QueryInterface(iid, ppvObject);
}

ULONG __stdcall FAKE_IDirect3D8::AddRef(void)
{
	return pD3D8->AddRef();
}

HRESULT __stdcall FAKE_IDirect3D8::RegisterSoftwareDevice(void *pInitializeFunction)
{
	return pD3D8->RegisterSoftwareDevice(pInitializeFunction);
}

UINT __stdcall FAKE_IDirect3D8::GetAdapterCount(void)
{
	return pD3D8->GetAdapterCount();
}

HRESULT __stdcall FAKE_IDirect3D8::GetAdapterIdentifier(UINT Adapter, DWORD Flags, D3DADAPTER_IDENTIFIER8* pIdentifier)
{
	return pD3D8->GetAdapterIdentifier(Adapter, Flags , pIdentifier);;
}

UINT __stdcall FAKE_IDirect3D8::GetAdapterModeCount(UINT Adapter)
{
	return pD3D8->GetAdapterModeCount(Adapter);
}

HRESULT __stdcall FAKE_IDirect3D8::EnumAdapterModes(UINT Adapter, UINT Mode, D3DDISPLAYMODE* pMode)
{
	return pD3D8->EnumAdapterModes(Adapter, Mode, pMode);
}

HRESULT __stdcall FAKE_IDirect3D8::GetAdapterDisplayMode(UINT Adapter,D3DDISPLAYMODE *pMode)
{
	return pD3D8->GetAdapterDisplayMode(Adapter, pMode);
}

HRESULT __stdcall FAKE_IDirect3D8::CheckDeviceType(UINT Adapter, D3DDEVTYPE CheckType,
												 D3DFORMAT DisplayFormat, D3DFORMAT BackBufferFormat, BOOL Windowed)
{
	return pD3D8->CheckDeviceType(Adapter, CheckType, DisplayFormat, BackBufferFormat, Windowed);
}

HRESULT __stdcall FAKE_IDirect3D8::CheckDeviceFormat(UINT Adapter, D3DDEVTYPE DeviceType,
									D3DFORMAT AdapterFormat, DWORD Usage, D3DRESOURCETYPE RType, D3DFORMAT CheckFormat)
{
	return pD3D8->CheckDeviceFormat(Adapter, DeviceType, AdapterFormat, Usage, RType, CheckFormat);
}

HRESULT __stdcall FAKE_IDirect3D8::CheckDeviceMultiSampleType(UINT Adapter, D3DDEVTYPE DeviceType,
															D3DFORMAT SurfaceFormat, BOOL Windowed, D3DMULTISAMPLE_TYPE MultiSampleType)
{
	return pD3D8->CheckDeviceMultiSampleType(Adapter, DeviceType, SurfaceFormat, Windowed, MultiSampleType);
}

HRESULT __stdcall FAKE_IDirect3D8::CheckDepthStencilMatch(UINT Adapter, D3DDEVTYPE DeviceType,
														D3DFORMAT AdapterFormat, D3DFORMAT RenderTargetFormat, D3DFORMAT DepthStencilFormat)
{
	return pD3D8->CheckDepthStencilMatch(Adapter, DeviceType, AdapterFormat, RenderTargetFormat, DepthStencilFormat);
}

HRESULT __stdcall FAKE_IDirect3D8::GetDeviceCaps(UINT Adapter, D3DDEVTYPE DeviceType, D3DCAPS8* pCaps)
{
	return pD3D8->GetDeviceCaps(Adapter, DeviceType, pCaps);
}

HMONITOR __stdcall FAKE_IDirect3D8::GetAdapterMonitor(UINT Adapter)
{
	return pD3D8->GetAdapterMonitor(Adapter);
}
