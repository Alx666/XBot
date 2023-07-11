
#include <windows.h>
#include <stdio.h>
#include "ApiHijack.h"
#include "XBot.h"
#include "globals.h"

//#define TEST

#ifdef TEXTURE_LOGGER
	#include "XTextureLogger.h"
#endif

extern SDLLHook D3DHook;
extern SDLLHook LoadLibraryHook;
extern SDLLHook User32Hook;

#ifdef TEXTURE_LOGGER
	extern XTextureLogger *texturelogger;
#endif

#ifdef TEST
	FILE* logfile = NULL;
#endif

HHOOK hMessageHook;
LRESULT CALLBACK MessageProc(int code, WPARAM wParam, LPARAM lParam);


BOOL APIENTRY DllMain(HANDLE hModule, DWORD ul_reason_for_call, LPVOID lpReserved)
{
	switch(ul_reason_for_call)
	{
		case DLL_PROCESS_ATTACH:
		{
			if(! (HookAPICalls(&User32Hook, GetModuleHandle("core.dll")) &&  HookAPICalls(&LoadLibraryHook, GetModuleHandle("core.dll"))))
				MessageBox(NULL, "Hook Attach Fail CORE.DLL", "error", MB_OK);
			hMessageHook = SetWindowsHookEx(WH_GETMESSAGE, MessageProc, (HMODULE)hModule, GetCurrentThreadId());
			
			#ifdef TEST
				logfile = fopen("Aimbot_Log.txt","w");
			#endif

			#ifdef TEXTURE_LOGGER
				texturelogger = new XTextureLogger();
			#endif

		}
		break;
		
		case DLL_THREAD_ATTACH:
		break;
		
		case DLL_THREAD_DETACH:
		break;
		
		case DLL_PROCESS_DETACH:
		{			
			XBot* xbot = XBot::getXBot();
			
			xbot->xconfig->saveStatus(xbot->autoAimSwitch, xbot->radarSwitch, xbot->imodeType, xbot->headshotSwitch,
									  xbot->pingCorrection, 3);
			#ifdef TEST
				fclose(logfile);
			#endif

			#ifdef TEXTURE_LOGGER
				delete texturelogger;
			#endif

		}
		break;
	}
	
	return true;
}


LRESULT CALLBACK MessageProc(int code, WPARAM wParam, LPARAM lParam)
{
	MSG* msg = (MSG*)lParam;
	
	if(code==HC_ACTION)
	{
		switch(msg->message)
		{
		case WM_KEYDOWN:
			{
				
#ifdef TEXTURE_LOGGER
				switch(msg->wParam)
				{
				case 0x5A: texturelogger->ZPression(); return CallNextHookEx(hMessageHook, code, wParam, lParam);
				case 0x58: texturelogger->XPression(); return CallNextHookEx(hMessageHook, code, wParam, lParam);
				case 0x43: texturelogger->CPression(); return CallNextHookEx(hMessageHook, code, wParam, lParam);
				}
#endif
				
				XBot* xbot = XBot::getXBot();


				if(msg->wParam == xbot->keyAltFire)
				{
					xbot->inputHandler->onSecFireKeyDown();
				}
				else if(msg->wParam == xbot->keyEnableAim)
				{
					xbot->swapAutoAimOnOff();
				}
				else if(msg->wParam == xbot->keyMenuUp)
				{
					xbot->menu->moveUp();
				}
				else if(msg->wParam == xbot->keyMenuDown)
				{
					xbot->menu->moveDown();
				}
				else if(msg->wParam == xbot->keyMenuMinus)
				{
					switch(xbot->menu->subtract())
					{
					case 0:	if(xbot->imodeSwitch) 
								xbot->menu->switchBool(0);		
							break;
					case 2:	xbot->setAutoFireMode(xbot->menu->getIntValue(2));	
							break;
					default:break;
					}
						
				}
				else if(msg->wParam == xbot->keyMenuPlus)
				{
					switch(xbot->menu->add())
					{
					case 0:	if(xbot->imodeSwitch) 
								xbot->menu->switchBool(0);		
							break;
					case 2:	xbot->setAutoAim(false);
							xbot->setAutoFireMode(xbot->menu->getIntValue(2));
							break;
					
					default:break;
					}
				}
				else if(msg->wParam == xbot->keyWallHack)
				{
					if(xbot->masterSwitch && xbot->gameStarted)
						xbot->wallHack =! xbot->wallHack;
				}
				else if(msg->wParam == xbot->keyMasterSwitch)		//MasterSwitch
				{
					xbot->masterSwitch =! xbot->masterSwitch;
				}
				else if(msg->wParam == xbot->keyHeadShot)		
				{
					if(xbot->masterSwitch && xbot->gameStarted)
						xbot->headshotSwitch =! xbot->headshotSwitch;
				}
			
			}
			break;

		case WM_KEYUP:
			{
				XBot* xbot = XBot::getXBot();

				if(msg->wParam == xbot->keyPrimFire)
				{
					if(xbot->gameStarted && xbot->imodeSwitch && xbot->autoAimSwitch && !xbot->secFireDown)
					{
						xbot->setAutoAim(false);
						xbot->primFireDown = false;
					}
				}
				else if(msg->wParam == xbot->keyAltFire)
				{
					xbot->inputHandler->onSecFireKeyUp();
				}

			}
			break;

			default:break;
		}
	}
		

	return CallNextHookEx(hMessageHook, code, wParam, lParam);
}