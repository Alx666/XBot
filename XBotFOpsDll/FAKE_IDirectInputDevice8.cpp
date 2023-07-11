#ifdef TEST
	#include <stdio.h>
	extern FILE* logfile;
#endif

#include "FAKE_IDirectInput8.h"
#include "FAKE_IDirectInputDevice8.h"
#include "XBot.h"


extern IDirectInput8 *pDInput8;						//Original Device pointer
extern FAKE_IDirectInput8 *pFAKE_DInput8;				//Wrapped Device pointer


HRESULT __stdcall FAKE_IDirectInputDevice8::GetDeviceData(DWORD cbObjectData, LPDIDEVICEOBJECTDATA rgdod, LPDWORD pdwInOut, DWORD dwFlags)
{
	HRESULT Result = pDInputDevice8->GetDeviceData(cbObjectData, rgdod, pdwInOut, dwFlags);

	if(!m_bIsMouse)
		return Result;

	XBot* xbot = XBot::getXBot();

	if(*pdwInOut == 0)		//TODO: (DISCORSO DELLA SENSIBILITA' DEL MOUSE)
	{
			if(xbot->moveMouseX!=0)
			{	
				*pdwInOut = 1;
				rgdod->dwOfs = DIMOFS_X;
				rgdod->dwData = xbot->moveMouseX;//(xbot->moveMouseX - (1024/2))/3;
				xbot->moveMouseX = 0;
			}
			else if(xbot->moveMouseY!=0)
			{				
				*pdwInOut = 1;
				rgdod->dwOfs = DIMOFS_Y;
				rgdod->dwData = xbot->moveMouseY;//(xbot->moveMouseY - (768/2))/3;
				xbot->moveMouseY = 0;
			}
	}
	else
	{
		if(rgdod->dwOfs == xbot->keyPrimFire) 
		{
			if(rgdod->dwData != 0)
				xbot->inputHandler->onMousePrimDown(&rgdod->dwData, pdwInOut);
			else
				xbot->inputHandler->onMousePrimUp(&rgdod->dwData, pdwInOut);
		}
		else if(rgdod->dwOfs == xbot->keyAltFire)		//TODO IMPORTANTE gestione autofire fuoco secondario
		{
			xbot->inputHandler->mouseSecOps(&rgdod->dwData, pdwInOut);
		}


		switch (rgdod->dwOfs)
		{
			case DIMOFS_BUTTON0://VK_LBUTTON
				break;
			case DIMOFS_BUTTON1://VK_RBUTTON 
				break;
			case DIMOFS_BUTTON2://VK_MBUTTON
				break;
			case DIMOFS_BUTTON3:
				break;
			case DIMOFS_BUTTON4:
				break;
			case DIMOFS_BUTTON5:
				break;
			case DIMOFS_BUTTON6:
				break;
			case DIMOFS_BUTTON7:
				break;
			case DIMOFS_X:
				if (abs(rgdod->dwData)>xbot->unlockStr)
				{
					xbot->tPrimary->isValid = false;
					xbot->targetLocked=false;
					break;
				}
				
				if (xbot->moveMouseX!=0)
				{
					rgdod->dwData = xbot->moveMouseX;//(xbot->moveMouseX - (1024/2))/3;
					xbot->moveMouseX = 0;
				}
				else
				{
					//rgdod->dwData = (DWORD)(((int)rgdod->dwData * ((float)GameInfo.m_Settings.m_MouseSpeed / 100)) + 0.5f);
					//GameInfo.m_LastCameraMouseX = GameInfo.m_MousePositionX;
					//xbot->LAST_X += rgdod->dwData;
				}
				break;
			case DIMOFS_Y:
				if (abs(rgdod->dwData)>xbot->unlockStr)
				{
					xbot->tPrimary->isValid=false;
					xbot->targetLocked=false;
					break;
				}
				if (xbot->moveMouseY!=0)
				{
					rgdod->dwData = xbot->moveMouseY;//(xbot->moveMouseY - (768/2))/3;
					xbot->moveMouseY = 0;
				}
				else
				{
					//rgdod->dwData = (DWORD)(((int)rgdod->dwData * ((float)GameInfo.m_Settings.m_MouseSpeed / 100)) + 0.5f);
					//GameInfo.m_LastCameraMouseY = GameInfo.m_MousePositionY;
					//xbot->LAST_Y += rgdod->dwData;
				}
				break;
			case DIMOFS_Z:
				break;
		}
	}



	return Result;
}


ULONG __stdcall FAKE_IDirectInputDevice8::Release(void)
{
	return pDInputDevice8->Release();
}

//****************************** FUNCTIONS BELOW ARE PASS-THROUGH ONLY ******************************

HRESULT __stdcall FAKE_IDirectInputDevice8::QueryInterface(REFIID iid, void ** ppvObject)
{
	return pDInputDevice8->QueryInterface(iid, ppvObject);
}

ULONG __stdcall FAKE_IDirectInputDevice8::AddRef(void)
{
	return pDInputDevice8->AddRef();
}

HRESULT __stdcall FAKE_IDirectInputDevice8::Acquire()
{
	return pDInputDevice8->Acquire();
}

HRESULT __stdcall FAKE_IDirectInputDevice8::BuildActionMap(LPDIACTIONFORMAT lpdiaf, LPCTSTR lpszUserName, DWORD dwFlags)
{
	return pDInputDevice8->BuildActionMap(lpdiaf, lpszUserName, dwFlags);
}

HRESULT __stdcall FAKE_IDirectInputDevice8::CreateEffect(REFGUID rguid, LPCDIEFFECT lpeff, LPDIRECTINPUTEFFECT *ppdeff, LPUNKNOWN punkOuter)
{
	return pDInputDevice8->CreateEffect(rguid, lpeff, ppdeff, punkOuter);
}

HRESULT __stdcall FAKE_IDirectInputDevice8::EnumCreatedEffectObjects(LPDIENUMCREATEDEFFECTOBJECTSCALLBACK lpCallback, LPVOID pvRef, DWORD fl)
{
	return pDInputDevice8->EnumCreatedEffectObjects(lpCallback, pvRef, fl);
}

HRESULT __stdcall FAKE_IDirectInputDevice8::EnumEffects(LPDIENUMEFFECTSCALLBACK lpCallback, LPVOID pvRef, DWORD dwEffType)
{
	return pDInputDevice8->EnumEffects(lpCallback, pvRef, dwEffType);
}

HRESULT __stdcall FAKE_IDirectInputDevice8::EnumEffectsInFile(LPCSTR lpszFileName, LPDIENUMEFFECTSINFILECALLBACK pec, LPVOID pvRef, DWORD dwFlags)
{
	return pDInputDevice8->EnumEffectsInFile(lpszFileName, pec, pvRef, dwFlags);
}

HRESULT __stdcall FAKE_IDirectInputDevice8::EnumObjects(LPDIENUMDEVICEOBJECTSCALLBACK lpCallback, LPVOID pvRef, DWORD dwFlags)
{
	return pDInputDevice8->EnumObjects(lpCallback, pvRef, dwFlags);
}

HRESULT __stdcall FAKE_IDirectInputDevice8::Escape(LPDIEFFESCAPE pesc)
{
	return pDInputDevice8->Escape(pesc);
}

HRESULT __stdcall FAKE_IDirectInputDevice8::GetCapabilities(LPDIDEVCAPS lpDIDevCaps)
{
	return pDInputDevice8->GetCapabilities(lpDIDevCaps);
}

HRESULT __stdcall FAKE_IDirectInputDevice8::GetDeviceInfo(LPDIDEVICEINSTANCE pdidi)
{
	return pDInputDevice8->GetDeviceInfo(pdidi);
}

HRESULT __stdcall FAKE_IDirectInputDevice8::GetDeviceState(DWORD cbData, LPVOID lpvData)
{
	return pDInputDevice8->GetDeviceState(cbData, lpvData);
}

HRESULT __stdcall FAKE_IDirectInputDevice8::GetEffectInfo(LPDIEFFECTINFO pdei, REFGUID rguid)
{
	return pDInputDevice8->GetEffectInfo(pdei, rguid);
}

HRESULT __stdcall FAKE_IDirectInputDevice8::GetForceFeedbackState(LPDWORD pdwOut)
{
	return pDInputDevice8->GetForceFeedbackState(pdwOut);
}

HRESULT __stdcall FAKE_IDirectInputDevice8::GetImageInfo(LPDIDEVICEIMAGEINFOHEADER lpdiDevImageInfoHeader)
{
	return pDInputDevice8->GetImageInfo(lpdiDevImageInfoHeader);
}

HRESULT __stdcall FAKE_IDirectInputDevice8::GetObjectInfo(LPDIDEVICEOBJECTINSTANCE pdidoi, DWORD dwObj, DWORD dwHow)
{
	return pDInputDevice8->GetObjectInfo(pdidoi, dwObj, dwHow);
}

HRESULT __stdcall FAKE_IDirectInputDevice8::GetProperty(REFGUID rguidProp, LPDIPROPHEADER pdiph)
{
	return pDInputDevice8->GetProperty(rguidProp, pdiph);
}

HRESULT __stdcall FAKE_IDirectInputDevice8::Initialize(HINSTANCE hinst, DWORD dwVersion, REFGUID rguid)
{
	return pDInputDevice8->Initialize(hinst, dwVersion, rguid);
}

HRESULT __stdcall FAKE_IDirectInputDevice8::Poll()
{
	return pDInputDevice8->Poll();
}

HRESULT __stdcall FAKE_IDirectInputDevice8::RunControlPanel(HWND hwndOwner, DWORD dwFlags)
{
	return pDInputDevice8->RunControlPanel(hwndOwner, dwFlags);
}

HRESULT __stdcall FAKE_IDirectInputDevice8::SendDeviceData(DWORD cbObjectData, LPCDIDEVICEOBJECTDATA rgdod, LPDWORD pdwInOut, DWORD fl)
{
	return pDInputDevice8->SendDeviceData(cbObjectData, rgdod, pdwInOut, fl);
}

HRESULT __stdcall FAKE_IDirectInputDevice8::SendForceFeedbackCommand(DWORD dwFlags)
{
	return pDInputDevice8->SendForceFeedbackCommand(dwFlags);
}

HRESULT __stdcall FAKE_IDirectInputDevice8::SetActionMap(LPDIACTIONFORMAT lpdiActionFormat, LPCTSTR lptszUserName, DWORD dwFlags)
{
	return pDInputDevice8->SetActionMap(lpdiActionFormat, lptszUserName, dwFlags);
}

HRESULT __stdcall FAKE_IDirectInputDevice8::SetCooperativeLevel(HWND hwnd, DWORD dwFlags)
{
	return pDInputDevice8->SetCooperativeLevel(hwnd, dwFlags);
}

HRESULT __stdcall FAKE_IDirectInputDevice8::SetDataFormat(LPCDIDATAFORMAT lpdf)
{
	return pDInputDevice8->SetDataFormat(lpdf);
}

HRESULT __stdcall FAKE_IDirectInputDevice8::SetEventNotification(HANDLE hEvent)
{
	return pDInputDevice8->SetEventNotification(hEvent);
}

HRESULT __stdcall FAKE_IDirectInputDevice8::SetProperty(REFGUID rguidProp, LPCDIPROPHEADER pdiph)
{
	return pDInputDevice8->SetProperty(rguidProp, pdiph);
}

HRESULT __stdcall FAKE_IDirectInputDevice8::Unacquire()
{
	return pDInputDevice8->Unacquire();
}

HRESULT __stdcall FAKE_IDirectInputDevice8::WriteEffectToFile(LPCSTR lpszFileName, DWORD dwEntries, LPDIFILEEFFECT rgDiFileEft, DWORD dwFlags)
{
	return pDInputDevice8->WriteEffectToFile(lpszFileName, dwEntries, rgDiFileEft, dwFlags);
}
