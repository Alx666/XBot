#include "XAim.h"
#include "XBot.h"


#ifdef TEST
	#include <stdio.h>
	extern FILE* logfile;
#endif


XAim::XAim()
{
	ignoreFactor = 8;
	smoothFactor  = 10;
	lineOfFire	= false;
	fireMode	= false;

	shiftVector.x = 0;
	shiftVector.y = 0;

	//TODO: Still not used
	originVector.x = 0;
	originVector.y = 0;
}


XAim::~XAim()
{

}

void XAim::clear()
{
	lineOfFire = false;
}

bool XAim::process(long *shiftX, long *shiftY)
{
	XBot* xbot =  XBot::getXBot();

	float ignore = ignoreFactor * xbot->frameTime;
	
	if(ignore < 5.0f)
		ignore = 5.0f;

	if(( abs(*shiftX) <= ignore) && ( abs(*shiftY) <= ignore))
	{
		lineOfFire = true;
	}
	else
	{

		if(( abs(*shiftX) >= xbot->aimSpeed))
		{
			shiftVector.x = *shiftX / abs(*shiftX);
			*shiftX = 	shiftVector.x * xbot->aimSpeed;
		}
		if(( abs(*shiftY) >= xbot->aimSpeed))
		{
			shiftVector.y = *shiftY / abs(*shiftY);
			*shiftY = 	shiftVector.y * xbot->aimSpeed;
		}
		//D3DXVec2Normalize(&shiftVector, &shiftVector);


		lineOfFire = false;

	}

	return lineOfFire;
}




void XAim::compensateMovement(UTarget* target)
{
	XBot* xbot = XBot::getXBot();
	
	target->aimAdjust.x -= (xbot->currentPlayer->direction.x * xbot->currentPlayer->speed);
	target->aimAdjust.y -= (xbot->currentPlayer->direction.y * xbot->currentPlayer->speed);
	target->aimAdjust.z -= (xbot->currentPlayer->direction.z * xbot->currentPlayer->speed);
}


void XAim::addWeaponOffset(UTarget* target)
{
	XBot* xbot = XBot::getXBot();

	target->aimAdjust.x = 0;
	target->aimAdjust.y = 0;
	target->aimAdjust.z = 0;

	instantAim(target);																			
}


void XAim::instantAim(UTarget* target)
{
	//Aggiunge la compensazione alla zona di mira
	target->aimAdjust.x = (target->direction.x * target->speed);
	target->aimAdjust.y = (target->direction.y * target->speed);
	target->aimAdjust.z = (target->direction.z * target->speed);
}

