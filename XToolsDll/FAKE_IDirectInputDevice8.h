
#pragma once

#include <dinput.h>

interface FAKE_IDirectInputDevice8 : public IDirectInputDevice8
{
public:
	IDirectInputDevice8 *pDInputDevice8;
	bool m_bIsMouse;
	HRESULT __stdcall QueryInterface(REFIID iid, void ** ppvObject);
	ULONG __stdcall AddRef(void);
	ULONG __stdcall Release(void);
	HRESULT __stdcall Acquire();
	HRESULT __stdcall BuildActionMap(LPDIACTIONFORMAT lpdiaf, LPCTSTR lpszUserName, DWORD dwFlags);
	HRESULT __stdcall CreateEffect(REFGUID rguid, LPCDIEFFECT lpeff, LPDIRECTINPUTEFFECT *ppdeff, LPUNKNOWN punkOuter);
	HRESULT __stdcall EnumCreatedEffectObjects(LPDIENUMCREATEDEFFECTOBJECTSCALLBACK lpCallback, LPVOID pvRef, DWORD fl);
	HRESULT __stdcall EnumEffects(LPDIENUMEFFECTSCALLBACK lpCallback, LPVOID pvRef, DWORD dwEffType);
	HRESULT __stdcall EnumEffectsInFile(LPCSTR lpszFileName, LPDIENUMEFFECTSINFILECALLBACK pec, LPVOID pvRef, DWORD dwFlags);
	HRESULT __stdcall EnumObjects(LPDIENUMDEVICEOBJECTSCALLBACK lpCallback, LPVOID pvRef, DWORD dwFlags);
	HRESULT __stdcall Escape(LPDIEFFESCAPE pesc);
	HRESULT __stdcall GetCapabilities(LPDIDEVCAPS lpDIDevCaps);
	HRESULT __stdcall GetDeviceData(DWORD cbObjectData, LPDIDEVICEOBJECTDATA rgdod, LPDWORD pdwInOut, DWORD dwFlags);
	HRESULT __stdcall GetDeviceInfo(LPDIDEVICEINSTANCE pdidi);
	HRESULT __stdcall GetDeviceState(DWORD cbData, LPVOID lpvData);
	HRESULT __stdcall GetEffectInfo(LPDIEFFECTINFO pdei, REFGUID rguid);
	HRESULT __stdcall GetForceFeedbackState(LPDWORD pdwOut);
	HRESULT __stdcall GetImageInfo(LPDIDEVICEIMAGEINFOHEADER lpdiDevImageInfoHeader);
	HRESULT __stdcall GetObjectInfo(LPDIDEVICEOBJECTINSTANCE pdidoi, DWORD dwObj, DWORD dwHow);
	HRESULT __stdcall GetProperty(REFGUID rguidProp, LPDIPROPHEADER pdiph);
	HRESULT __stdcall Initialize(HINSTANCE hinst, DWORD dwVersion, REFGUID rguid);
	HRESULT __stdcall Poll();
	HRESULT __stdcall RunControlPanel(HWND hwndOwner, DWORD dwFlags);
	HRESULT __stdcall SendDeviceData(DWORD cbObjectData, LPCDIDEVICEOBJECTDATA rgdod, LPDWORD pdwInOut, DWORD fl);
	HRESULT __stdcall SendForceFeedbackCommand(DWORD dwFlags);
	HRESULT __stdcall SetActionMap(LPDIACTIONFORMAT lpdiActionFormat, LPCTSTR lptszUserName, DWORD dwFlags);
	HRESULT __stdcall SetCooperativeLevel(HWND hwnd, DWORD dwFlags);
	HRESULT __stdcall SetDataFormat(LPCDIDATAFORMAT lpdf);
	HRESULT __stdcall SetEventNotification(HANDLE hEvent);
	HRESULT __stdcall SetProperty(REFGUID rguidProp, LPCDIPROPHEADER pdiph);
	HRESULT __stdcall Unacquire();
	HRESULT __stdcall WriteEffectToFile(LPCSTR lpszFileName, DWORD dwEntries, LPDIFILEEFFECT rgDiFileEft, DWORD dwFlags);
};

