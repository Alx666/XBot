#include "XBot.h"
#include "XInputHandler.h"

#ifdef TEST
	#include <stdio.h>
	extern FILE* logfile;
#endif

void XInputHandler::onSecFireKeyDown(WPARAM* wParam)
{
	XBot* xbot = XBot::getXBot();

	if(!xbot->gameStarted || !xbot->masterSwitch)
		return;
	
	xbot->primFireModeSwitch = false;

	
	if(!xbot->imodeSwitch)									// Autofire OFF
	{
	}
	else
	{
		switch(xbot->lastWeaponCrc)
		{
		case CRC_SHOCKRIFLE: 
			xbot->secFireDown = true;
			break;	  
		case CRC_ROCKET_LAUNCHER: 
			if(xbot->secFireDown)
			{
				*wParam = 0;	
				return;
			}
			if(!HideAltFirePress)
			{
				xbot->InputDown.ki.wVk = xbot->keyAltFire;
				rocket2ndFireRelease = true;
				release2ndRocketFireDelay = GetTickCount();
				HideAltFirePress  = true;
				xbot->secFireDown = true;
			}
			break;
		case CRC_GES:
			if(!xbot->secFireDown)
			{
				HideAltFirePress  = true;
				xbot->InputDown.ki.wVk = xbot->keyAltFire;
				xbot->secFireDown = true;
			}
			break;
		case CRC_ASSAULT_RIFLE:   
		case CRC_SHIELD_GUN:	  
		case CRC_LIGHT_GUN:		  
		//case CRC_FLAK_CANNON:	  
		case CRC_SNIPER	: 
			break;
		default:
			onSecDown((UINT*)wParam);
			break;
		}
	}
}


void XInputHandler::onMouseSecDown(LPDWORD pdwInOut)
{	

	XBot* xbot = XBot::getXBot();

	if(!xbot->gameStarted || !xbot->masterSwitch)
		return;

	xbot->primFireModeSwitch = false;


	if(!xbot->imodeSwitch)									// Autofire OFF
	{
		if(xbot->lastWeaponCrc == CRC_SHOCKRIFLE)
		{
			releaseAltFireShock			= true; 
			releaseAltFireShockDelay	= GetTickCount();
			xbot->secFireDown = true;

		}
	}
	else												// Autofire ON
	{
		switch(xbot->lastWeaponCrc)
		{			  
		case CRC_SHOCKRIFLE:	
			releaseAltFireShock			= true; 
			releaseAltFireShockDelay	= GetTickCount();
			xbot->secFireDown = true;
			break;
		case CRC_ROCKET_LAUNCHER: 
			rocket2ndFireRelease = true;
			release2ndRocketFireDelay = GetTickCount();
			xbot->InputDown.ki.wVk = xbot->keyAltFire;
			xbot->secFireDown = true;
			break;
		case CRC_GES:
			xbot->InputDown.ki.wVk = xbot->keyAltFire;
			xbot->secFireDown = true;
			break;
		case CRC_LIGHT_GUN:		  
		//case CRC_FLAK_CANNON:	  
		case CRC_ASSAULT_RIFLE:	  
		case CRC_SHIELD_GUN:	  
		case CRC_SNIPER:		
			break;
		default: 
			onSecDown((UINT*)pdwInOut);
			break;
		}	
			

	}
	
}


void XInputHandler::onSecDown(UINT* out)
{	
	XBot* xbot = XBot::getXBot();


	if(!xbot->primFireDown && !xbot->isAutoFiring )
	{
		xbot->secFireDown = true;
		xbot->InputDown.ki.wVk = xbot->keyAltFire;

		if(xbot->tPrimary->isInRange || xbot->imodeType == XBot::IMODE_AUTO)
		{
			*out = 0;
			xbot->setAutoAim(true);	
		}
	}
	
	
}

void XInputHandler::onSecFireUp(UINT* out)
{
	XBot* xbot = XBot::getXBot();
	
	if(!xbot->gameStarted || !xbot->masterSwitch)
		return;

	if(xbot->imodeSwitch)				//Autofire ON
	{
	
		switch(xbot->lastWeaponCrc)
		{
		case CRC_ROCKET_LAUNCHER:
			if(rocket2ndFireRelease)
			{
				if(xbot->tPrimary->isInRange)
				{
					xbot->setAutoAim(true);
					*out = 0;
				}
				rocket2ndFireRelease = false;
			}
			else
				HideAltFirePress = false;
			break;
		case CRC_GES:
			if(xbot->tPrimary->isInRange && xbot->secFireDown)
			{
				xbot->setAutoAim(true);
				*out = 0;
			}
			else
			{


			}
			break;
		default:
			{
				if(!xbot->tPrimary->isValid || xbot->imodeType == XBot::IMODE_AUTO)								
				{
					xbot->stopFire();
					xbot->setAutoAim(false);
				}
			}
			break;
		}
	}
	else							//Autofire OFF
	{


	}

	xbot->secFireDown = false;

}

void XInputHandler::onMousePrimDown(LPDWORD pdwInOut)
{
	XBot* xbot = XBot::getXBot();
	
	if(!xbot->gameStarted || !xbot->masterSwitch)
		return;

	switch(xbot->lastWeaponCrc)
	{
	case CRC_SHIELD_GUN: 
		return;
	}

	HideAltFirePress  = false;

	if(xbot->lastWeaponCrc == CRC_SHOCKRIFLE && xbot->tSecondary->isValid)
	{
		if(xbot->imodeType == XBot::IMODE_NONE)
			xbot->setAutoFireMode(XBot::IMODE_AUTOCOMBO);
		
		xbot->InputDown.ki.wVk = VK_LBUTTON;//xbot->keyPrimFire2;
		xbot->blastCombo = true;
		*pdwInOut = 0;
	}
	else if(!xbot->imodeSwitch)									// Autofire OFF
	{
		
	}
	else												// Autofire ON
	{
		if(!xbot->secFireDown && !xbot->isAutoFiring)				// Quando il pulsante viene premuto
		{
			xbot->primFireDown = true;
			xbot->primFireModeSwitch = true;
			xbot->InputDown.ki.wVk = VK_LBUTTON;//xbot->keyPrimFire2;

			if(xbot->tPrimary->isInRange || xbot->imodeType == XBot::IMODE_AUTO)
			{
				*pdwInOut = 0;
				xbot->setAutoAim(true);
			}
		}
	}
}


void XInputHandler::onMousePrimUp(LPDWORD pdwInOut)
{
	XBot* xbot = XBot::getXBot();

	if(!xbot->gameStarted || !xbot->masterSwitch)
		return;


	xbot->primFireDown = false;

	if(!xbot->imodeSwitch)			//Rilascio del pulsante
	{



	}
	else
	{
		if(!xbot->tPrimary->isValid || xbot->imodeType == XBot::IMODE_AUTO)									// Quando il pulsante viene rilasciato
		{
			xbot->stopFire();
			xbot->setAutoAim(false);
		}

	}
}






void XInputHandler::onJumpDown(UINT* out)
{
	XBot* xbot = XBot::getXBot();

	if(!xbot->gameStarted || !xbot->masterSwitch)
		return;


	if(xbot->easyDodgeSwitch == XBot::DODGEMODE_AUTO && ( GetKeyState(0x57) & 0x80 || GetKeyState(VK_UP) & 0x80 || GetKeyState(0x53) & 0x80 || GetKeyState(VK_DOWN) & 0x80) )
	{
		if(!xbot->dodger->isDodgeStarted())
		{
			xbot->dodger->startDodge();
			*out = 0;
		}
						
	}
	else if(xbot->easyDodgeSwitch == XBot::DODGEMODE_AUTO && xbot->dodger->isDodgeStarted())
		*out = 0;
}





