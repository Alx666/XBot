

#pragma once

#define DIRECTINPUT_VERSION 0x0800

#include "FAKE_IDirectInputDevice8.h"

interface FAKE_IDirectInput8 : public IDirectInput8
{
public:
	FAKE_IDirectInputDevice8 FAKE_DInputDevice8;
	HRESULT __stdcall QueryInterface(REFIID iid, void ** ppvObject);
	ULONG __stdcall AddRef(void);
	ULONG __stdcall Release(void);
	HRESULT __stdcall ConfigureDevices(LPDICONFIGUREDEVICESCALLBACK lpdiCallback, LPDICONFIGUREDEVICESPARAMS lpdiCDParams, DWORD dwFlags, LPVOID pvRefData);
	HRESULT __stdcall CreateDevice(REFGUID rguid, LPDIRECTINPUTDEVICE8 *lpDirectInputDevice, LPUNKNOWN pUnkOuter);
	HRESULT __stdcall EnumDevices(DWORD dwDevType, LPDIENUMDEVICESCALLBACK lpCallback, LPVOID pvRef, DWORD dwFlags);
	HRESULT __stdcall EnumDevicesBySemantics(LPCTSTR ptszUserName, LPDIACTIONFORMAT lpdiActionFormat, LPDIENUMDEVICESBYSEMANTICSCB lpCallback, LPVOID pvRef, DWORD dwFlags);
	HRESULT __stdcall FindDevice(REFGUID rguidClass, LPCTSTR ptszName, LPGUID pguidInstance);
	HRESULT __stdcall GetDeviceStatus(REFGUID rguidInstance);
	HRESULT __stdcall Initialize(HINSTANCE hinst, DWORD dwVersion);
	HRESULT __stdcall RunControlPanel(HWND hwndOwner, DWORD dwFlags);
};

