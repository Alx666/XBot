#pragma once

#include <windows.h>
#include "ApiHijack.h"





//Function prototypes
DWORD WINAPI FAKE_Direct3DCreate8(UINT SDKVersion);
DWORD WINAPI FAKE_LoadLibraryExW(wchar_t *lpFileName, DWORD hFile, DWORD dwFlags);
DWORD WINAPI FAKE_LoadLibraryW(wchar_t *lpFileName);
DWORD WINAPI FAKE_LoadLibraryExA(char *lpFileName, DWORD hFile, DWORD dwFlags);
DWORD WINAPI FAKE_LoadLibraryA(char *lpFileName);
HRESULT WINAPI FAKE_DirectInput8Create(HINSTANCE hinst, DWORD dwVersion, REFIID riidltf, LPVOID* ppvOut, LPUNKNOWN punkOuter);

SHORT WINAPI FAKE_GetKeyState(int nVirtKey);


//Function pointer types
typedef DWORD (WINAPI *FP_Direct3DCreate8)(UINT SDKVersion);
typedef DWORD (WINAPI *FP_LoadLibraryExW)(wchar_t *lpFileName, DWORD hFile, DWORD dwFlags);
typedef DWORD (WINAPI *FP_LoadLibraryW)(wchar_t *lpFileName);
typedef DWORD (WINAPI *FP_LoadLibraryExA)(char *lpFileName, DWORD hFile, DWORD dwFlags);
typedef DWORD (WINAPI *FP_LoadLibraryA)(char *lpFileName);
typedef HRESULT (WINAPI *FP_DirectInput8Create)(HINSTANCE hinst, DWORD dwVersion, REFIID riidltf, LPVOID* ppvOut, LPUNKNOWN punkOuter);

typedef SHORT (WINAPI *FP_GetKeyState)(int nVirtKey);



//Hook lists

SDLLHook D3DHook = 
{
    "D3D8.DLL",
    false, NULL,
    {
        {"Direct3DCreate8", FAKE_Direct3DCreate8},
        {NULL, NULL},
    },
};


SDLLHook DirectInput8Hook = 
{
    "DINPUT8.DLL",
    false, NULL,
    {
        {"DirectInput8Create", FAKE_DirectInput8Create},
        {NULL, NULL},
    },
};


SDLLHook User32Hook = 
{
    "USER32.DLL",
    false, NULL,
    {
        {"GetKeyState", FAKE_GetKeyState},
        {NULL, NULL},
    },
};

SDLLHook LoadLibraryHook = 
{
    "KERNEL32.DLL",
    false, NULL,
    {
        {"LoadLibraryExW", FAKE_LoadLibraryExW},
		{"LoadLibraryW", FAKE_LoadLibraryW},
		{"LoadLibraryExA", FAKE_LoadLibraryExA},
		{"LoadLibraryA", FAKE_LoadLibraryA},
        {NULL, NULL},
    },
};