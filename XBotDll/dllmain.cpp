
#include "XBot.h"
#include <windows.h>
#include <stdio.h>
#include "ApiHijack.h"
#include "globals.h"

extern SDLLHook D3DHook;
extern SDLLHook LoadLibraryHook;
extern SDLLHook User32Hook;

#ifdef TEST
	FILE* logfile = NULL;
#endif

HHOOK hMessageHook;
LRESULT CALLBACK MessageProc(int code, WPARAM wParam, LPARAM lParam);


BOOL APIENTRY DllMain(HANDLE hModule, DWORD ul_reason_for_call, LPVOID lpReserved)
{
	switch(ul_reason_for_call)
	{
		MessageBox(NULL, "Hook Attach Fail CORE.DLL", "error", MB_OK);

		case DLL_PROCESS_ATTACH:
		{
			#ifdef TEST
				logfile = fopen("Aimbot_Log.txt","w");
			#endif
			

			if(! (HookAPICalls(&User32Hook, GetModuleHandle("core.dll")) &&  HookAPICalls(&LoadLibraryHook, GetModuleHandle("core.dll"))))
				MessageBox(NULL, "Hook Attach Fail CORE.DLL", "error", MB_OK);
			
		
			#ifdef TEXTURE_LOGGER
				texturelogger = new XTextureLogger();
			#endif
			
		}
		break;
		
		case DLL_THREAD_ATTACH:
			if(XBot::getXBot()->xconfig->threadID)
			{
				hMessageHook = SetWindowsHookEx(WH_GETMESSAGE, MessageProc, (HMODULE)hModule, XBot::getXBot()->xconfig->threadID);
				XBot::getXBot()->xconfig->threadID = 0;
				//HideModule((HINSTANCE)hModule);
			}
			break;
		
		case DLL_THREAD_DETACH:
		break;
		
		case DLL_PROCESS_DETACH:
		{			
			XBot* xbot = XBot::getXBot();
			
			xbot->xconfig->saveStatus(xbot->autoAimSwitch, xbot->radarSwitch, xbot->imodeType, xbot->headshotSwitch,
									  xbot->pingCorrection, xbot->easyDodgeSwitch);
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


				if(xbot->console->getIsOut() && xbot->console->acceptKeyInput())
				{
					xbot->console->getKeyPress(&msg->wParam);
				}
				if(msg->wParam == xbot->keyAltFire)
				{
					if(xbot->gameStarted)
					{
						if(GetMessageExtraInfo() == FAKE_INPUT)
							xbot->InputUp.ki.dwExtraInfo = 0;

						else			
							xbot->inputHandler->onSecFireKeyDown(&msg->wParam);
						
					}
				}
				else if(msg->wParam == xbot->keyJump)
				{
					 if(xbot->gameStarted)
						xbot->inputHandler->onJumpDown(&msg->wParam);
				}

				else if(msg->wParam == xbot->keyEnableAim)
				{
					if(xbot->gameStarted)
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
					case 2:	xbot->onModifyImodeType();
							break;
					case 4: xbot->onModifyCrosshairRadius();
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
							xbot->onModifyImodeType();
							break;
					case 4: xbot->onModifyCrosshairRadius();
							break;
					default:break;
					}
					

				}
				else if(msg->wParam == xbot->keyResetCounterRedeem)	//Timer Reedeemer
				{
					if(xbot->gameStarted)
						xbot->resetRedeemTimer(true);
				}
				else if(msg->wParam == xbot->keyResetCounterDDamage) //Timer DDamage
				{
					if(xbot->gameStarted)
						xbot->resetDDamageTimer(true);

					//TEST CODE
					/*
					xbot->aimAssistant->rayOffset--;
					xbot->console->addSprintfLine("offset = %i", xbot->aimAssistant->rayOffset);
					xbot->console->popUp();
					*/

					
				}
				else if(msg->wParam == xbot->keyResetCounterShield)	//Timer Shield
				{	
					if(xbot->gameStarted)
						xbot->resetShield100Timer(true);

					//TEST CODE
					/*
					xbot->aimAssistant->rayOffset++;
					xbot->console->addSprintfLine("offset = %i", xbot->aimAssistant->rayOffset);
					xbot->console->popUp();
					*/
					
				}
				else if(msg->wParam == xbot->keyMasterSwitch)		//MasterSwitch
				{
					xbot->masterSwitch =! xbot->masterSwitch;
				}
				else if(msg->wParam == xbot->keyDodge)		
				{
					if(xbot->masterSwitch && xbot->gameStarted)
					{
						if(xbot->easyDodgeSwitch == XBot::DODGEMODE_AUTO)
							xbot->easyDodgeSwitch = XBot::DODGEMODE_NONE;
						else if(xbot->easyDodgeSwitch == XBot::DODGEMODE_NONE)
							xbot->easyDodgeSwitch = XBot::DODGEMODE_AUTO;
						else if(xbot->easyDodgeSwitch == XBot::DODGEMODE_MANUAL)
							xbot->dodger->startDodge();

					}
				}
				else if(msg->wParam == xbot->keyHeadShot)		
				{
					if(xbot->masterSwitch && xbot->gameStarted)
						xbot->headshotSwitch =! xbot->headshotSwitch;
				}
				else if(msg->wParam == xbot->keyEnableCounterShock)
				{
					if(xbot->masterSwitch && xbot->gameStarted)
						xbot->counterShockEnabled =! xbot->counterShockEnabled;
				}
				else if(msg->wParam == VK_MULTIPLY )
				{
					
						if(xbot->console->getIsPopUpping() && xbot->console->getIsOut())
							xbot->console->popUp(false);
						else if(xbot->console->getIsOut())
						{
							if(xbot->console->getBkgrnMode())
								xbot->console->switchBkgrndMode();
							else
								xbot->console->slideIn();
						}
						else
							xbot->console->slideOut();
				}
			
			}
			break;

		case WM_KEYUP:
			{
				XBot* xbot = XBot::getXBot();

				if(msg->wParam ==VK_LBUTTON)	/*&& xbot->isFakeInput*/ //)
				{	
					if(GetMessageExtraInfo() == FAKE_INPUT && xbot->imodeType!=XBot::IMODE_AUTO)
					{
						xbot->InputUp.ki.dwExtraInfo = 0;
						xbot->setAutoAim(false);
					}
				}
				else if(msg->wParam == xbot->keyAltFire)
				{
					if(GetMessageExtraInfo() == FAKE_INPUT)
						xbot->InputUp.ki.dwExtraInfo = 0;
					else
						xbot->inputHandler->onSecFireUp(&msg->wParam);
				}

			}
			break;

			default:break;
		}
	}
		

	return CallNextHookEx(hMessageHook, code, wParam, lParam);
}