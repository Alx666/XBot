
#include "XBot.h"
#include "Hooks.h"
#include "FAKE_IDirect3D8.h"
#include "FAKE_IDirectInput8.h"



#ifdef TEST
	#include <stdio.h>
	extern FILE* logfile;
#endif

extern FAKE_IDirect3D8 FAKE_D3D8;
extern FAKE_IDirect3D8 *pFAKE_D3D8;						
extern IDirect3D8 *pD3D8;						

extern IDirectInput8 *pDInput8;						//Original Device pointer
extern FAKE_IDirectInput8 *pFAKE_DInput8;				//Wrapped Device pointer
extern FAKE_IDirectInput8 FAKE_DInput8;							//Wrapped Device


//*************************** D3D8.dll HOOKS
DWORD WINAPI FAKE_Direct3DCreate8(UINT SDKVersion)
{

	FP_Direct3DCreate8 OldFn = (FP_Direct3DCreate8)D3DHook.Functions[0].OrigFn;
	//Set pointer to original device
	pD3D8 =  (IDirect3D8*)OldFn(SDKVersion);
	pFAKE_D3D8 = &FAKE_D3D8;
	
	return (DWORD)pFAKE_D3D8;

}

//*************************** DINPUT.dll HOOKS

HRESULT WINAPI FAKE_DirectInput8Create(HINSTANCE hinst, DWORD dwVersion, REFIID riidltf, LPVOID* ppvOut, LPUNKNOWN punkOuter)
{
    FP_DirectInput8Create OldFn = (FP_DirectInput8Create)DirectInput8Hook.Functions[0].OrigFn;
    HRESULT Result = OldFn(hinst, dwVersion, riidltf, (LPVOID*)&pDInput8, punkOuter);
	pFAKE_DInput8 = &FAKE_DInput8;
	*ppvOut = pFAKE_DInput8;
	return Result;
}


//*************************** USER32.DLL
SHORT WINAPI FAKE_GetKeyState(int nVirtKey)
{
	FP_GetKeyState OldFn = (FP_GetKeyState)User32Hook.Functions[0].OrigFn;
	SHORT Result = OldFn(nVirtKey);

	XBot* xbot = XBot::getXBot();
	
	if(!xbot->masterSwitch || !xbot->lastGameStarted)
		return Result;

	if(xbot->dodger->hideKeyPress && nVirtKey == xbot->dodger->getReleaseKey())
		return 0;
		
	
	if(nVirtKey == xbot->keyAltFire && xbot->inputHandler->HideAltFirePress )
		return 0xFFFF;

	if(nVirtKey == xbot->keyAltFire && xbot->tSecondary->isValid && xbot->lastWeaponCrc == CRC_SHOCKRIFLE)
		return 0;
	
		
	return Result;

}

//*************************** KERNEL32.DLL
DWORD WINAPI FAKE_LoadLibraryExW(wchar_t *lpFileName, DWORD hFile, DWORD dwFlags)
{
    FP_LoadLibraryExW OldFn = (FP_LoadLibraryExW)LoadLibraryHook.Functions[0].OrigFn;

	DWORD Result = OldFn(lpFileName, hFile, dwFlags);

	/*HookAPICalls(&D3DHook, (HMODULE)Result);
	HookAPICalls(&DirectInput8Hook, (HMODULE)Result);
	HookAPICalls(&User32Hook, (HMODULE)Result);*/

	return Result;
}

DWORD WINAPI FAKE_LoadLibraryW(wchar_t *lpFileName)
{
    FP_LoadLibraryW OldFn = (FP_LoadLibraryW)LoadLibraryHook.Functions[1].OrigFn;

	DWORD Result = OldFn(lpFileName);
	
	char s[256],dllName[256];
	wsprintf(s,"%ls",lpFileName);
	
	for(int i = strlen(s); i>0; i--)
		if(s[i] == '\\')
		{
			memcpy(dllName,&s[i+1],strlen(s) -i );
			break;
		}

	if(stricmp(dllName,"D3DDrv")==0)
		HookAPICalls(&D3DHook, (HMODULE)Result);
	else if(stricmp(dllName,"WinDrv")==0)	
		HookAPICalls(&DirectInput8Hook, (HMODULE)Result);
	
	HookAPICalls(&User32Hook, (HMODULE)Result);


	return Result;
}

DWORD WINAPI FAKE_LoadLibraryExA(char *lpFileName, DWORD hFile, DWORD dwFlags)
{
    FP_LoadLibraryExA OldFn = (FP_LoadLibraryExA)LoadLibraryHook.Functions[2].OrigFn;

	DWORD Result = OldFn(lpFileName, hFile, dwFlags);

	/*HookAPICalls(&D3DHook, (HMODULE)Result);
	HookAPICalls(&DirectInput8Hook, (HMODULE)Result);
	HookAPICalls(&User32Hook, (HMODULE)Result);*/


	return Result;
}

DWORD WINAPI FAKE_LoadLibraryA(char *lpFileName)
{
    FP_LoadLibraryA OldFn = (FP_LoadLibraryA)LoadLibraryHook.Functions[3].OrigFn;

	DWORD Result = OldFn(lpFileName);

	/*HookAPICalls(&D3DHook, (HMODULE)Result);
	HookAPICalls(&DirectInput8Hook, (HMODULE)Result);
	HookAPICalls(&User32Hook, (HMODULE)Result);*/


	return Result;
}