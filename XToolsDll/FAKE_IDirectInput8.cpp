

#define INITGUID

#include "FAKE_IDirectInput8.h"

extern IDirectInput8 *pDInput8;						//Original Device pointer
extern FAKE_IDirectInput8 *pFAKE_DInput8;				//Wrapped Device pointer


HRESULT __stdcall FAKE_IDirectInput8::CreateDevice(REFGUID rguid, LPDIRECTINPUTDEVICE8 *lplpDirectInputDevice, LPUNKNOWN pUnkOuter)
{
	//Create DirectInput Device
	FAKE_IDirectInputDevice8 *pFAKE_DInputDevice8 = new FAKE_IDirectInputDevice8;
	if (rguid == GUID_SysMouse)
		pFAKE_DInputDevice8->m_bIsMouse = true;
	else
		pFAKE_DInputDevice8->m_bIsMouse = false;
	HRESULT Result = pDInput8->CreateDevice(rguid, (LPDIRECTINPUTDEVICE8*)&pFAKE_DInputDevice8->pDInputDevice8, pUnkOuter);
	*lplpDirectInputDevice = (LPDIRECTINPUTDEVICE8)pFAKE_DInputDevice8;

	return Result;
}

//****************************** FUNCTIONS BELOW ARE PASS-THROUGH ONLY ******************************

HRESULT __stdcall FAKE_IDirectInput8::QueryInterface(REFIID iid, void ** ppvObject)
{
	return pDInput8->QueryInterface(iid, ppvObject);
}

ULONG __stdcall FAKE_IDirectInput8::AddRef(void)
{
	return pDInput8->AddRef();
}

ULONG __stdcall FAKE_IDirectInput8::Release(void)
{
	return pDInput8->Release();
}

HRESULT __stdcall FAKE_IDirectInput8::ConfigureDevices(LPDICONFIGUREDEVICESCALLBACK lpdiCallback, 
													 LPDICONFIGUREDEVICESPARAMS lpdiCDParams, DWORD dwFlags, LPVOID pvRefData)
{
	return pDInput8->ConfigureDevices(lpdiCallback, lpdiCDParams, dwFlags, pvRefData);
}

HRESULT __stdcall FAKE_IDirectInput8::EnumDevices(DWORD dwDevType, LPDIENUMDEVICESCALLBACK lpCallback, LPVOID pvRef, DWORD dwFlags)
{
	return pDInput8->EnumDevices(dwDevType, lpCallback, pvRef, dwFlags);
}

HRESULT __stdcall FAKE_IDirectInput8::EnumDevicesBySemantics(LPCTSTR ptszUserName, LPDIACTIONFORMAT lpdiActionFormat, 
														   LPDIENUMDEVICESBYSEMANTICSCB lpCallback, LPVOID pvRef, DWORD dwFlags)
{
	return pDInput8->EnumDevicesBySemantics(ptszUserName, lpdiActionFormat, lpCallback, pvRef, dwFlags);
}

HRESULT __stdcall FAKE_IDirectInput8::FindDevice(REFGUID rguidClass, LPCTSTR ptszName, LPGUID pguidInstance)
{
	return pDInput8->FindDevice(rguidClass, ptszName, pguidInstance);
}

HRESULT __stdcall FAKE_IDirectInput8::GetDeviceStatus(REFGUID rguidInstance)
{
	return pDInput8->GetDeviceStatus(rguidInstance);
}

HRESULT __stdcall FAKE_IDirectInput8::Initialize(HINSTANCE hinst, DWORD dwVersion)
{
	return pDInput8->Initialize(hinst, dwVersion);
}

HRESULT __stdcall FAKE_IDirectInput8::RunControlPanel(HWND hwndOwner, DWORD dwFlags)
{
	return pDInput8->RunControlPanel(hwndOwner, dwFlags);
}
