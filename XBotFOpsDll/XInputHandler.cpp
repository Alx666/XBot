#include "XInputHandler.h"
#include "XBot.h"


void XInputHandler::onSecFireKeyDown()
{
	
}

void XInputHandler::onSecFireKeyUp()
{
	
}

void XInputHandler::onMousePrimDown(LPDWORD dwData, LPDWORD pdwInOut)
{
	XBot* xbot = XBot::getXBot();

	
	if(!xbot->gameStarted || !xbot->masterSwitch)
	{
		xbot->primFireDown = false;
		xbot->secFireDown = false;
		xbot->setAutoAim(false);
		return;
	}

	switch(XBot::getXBot()->lastWeaponCrc)
	{
		case WEAP_FLASH_GRANADE:
		case WEAP_HE_GRANADE:
		case WEAP_NAPALM_GRANADE:
		case WEAP_RSMOKE_GRANADE:
		case WEAP_YSMOKE_GRANADE: return;

	}

	xbot->primFireDown = true;


	if(!xbot->imodeSwitch)									// Autofire OFF
	{
		
	}
	else												// Autofire ON
	{
		if(!xbot->secFireDown && !xbot->isAutoFiring)				// Quando il pulsante viene premuto
		{
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


void XInputHandler::onMousePrimUp(LPDWORD dwData, LPDWORD pdwInOut)
{
	XBot* xbot = XBot::getXBot();

	
	if(!xbot->gameStarted || !xbot->masterSwitch)
	{
		xbot->primFireDown = false;
		xbot->secFireDown = false;
		xbot->setAutoAim(false);
		return;
	}

	xbot->primFireDown = false;

	if(!xbot->imodeSwitch)			//Rilascio del pulsante
	{
	}
	else
	{
		if((!xbot->secFireDown && xbot->aimAssistant->lineOfFire && xbot->tPrimary->isValid && xbot->isAutoFiring)
			|| xbot->imodeType == XBot::IMODE_AUTO)									// Quando il pulsante viene rilasciato
		{
			xbot->stopFire();
			xbot->setAutoAim(false);
			//*pdwInOut = 0;								//Non c'e' bisognod i inibire onrealease
		}
	}
}


void XInputHandler::mouseSecOps(LPDWORD dwData, LPDWORD pdwInOut)
{

}