#include "XBot.h"
#include "XAim.h"


#ifdef TEST
	#include <stdio.h>
	extern FILE* logfile;
#endif


XAim::XAim()
{
	ignoreFactor = 500;
	smoothFactor  = 10;
	lineOfFire	= false;
	fireMode	= false;

	shiftVector.x = 0;
	shiftVector.y = 0;

	//TODO: Still not used
	originVector.x = 0;
	originVector.y = 0;

	//TEST CODE
	rayOffset = 20; 
	lastRayOffset = 0;
	rayCompensationSet = false;
}


XAim::~XAim()
{

}

void XAim::clear()
{
	lineOfFire = false;
	rayCompensationSet = false; //TEST CODE
}

bool XAim::process(long *shiftX, long *shiftY)
{
	XBot* xbot =  XBot::getXBot();
	
	UINT aimSpeed = xbot->getAimSpeed();

	float ignore = ignoreFactor * xbot->frameTime;
	
	if(ignore < 5.5f)
		ignore = 5.5f;

	if(( abs(*shiftX) <= ignore) && ( abs(*shiftY) <= ignore))
	{
		lineOfFire = true;
	}
	else
	{

		if(( abs(*shiftX) >= aimSpeed>>2))
		{
			shiftVector.x = *shiftX / abs(*shiftX);
			*shiftX = 	shiftVector.x * (aimSpeed>>2);
		}
		if(( abs(*shiftY) >= aimSpeed>>2))
		{
			shiftVector.y = *shiftY / abs(*shiftY);
			*shiftY = 	shiftVector.y * (aimSpeed>>2);
		}

		lineOfFire = false;

	}

	return lineOfFire;
}

/*
float XAim::getDistance(long x, long y)
{
	return sqrt( (x * x) + (y * y) );
}
*/

//TEST CODE
void XAim::compensateRay(UTarget* target)
{
	
	XBot* xbot = XBot::getXBot();
	

	//biogna modificare la current world position
	D3DXVECTOR4 playerPosition = xbot->currentPlayer->currentWorldPosition;						//the absolute player location
	D3DXVECTOR4 targetRelative = -(target->currentWorldPosition - playerPosition);	//the player position relative to the target location
	targetRelative.w = 1;

	D3DXMATRIX rotateMatrix;
	D3DXMatrixRotationZ(&rotateMatrix, (90*0.0174532925));				//Creates a matrix that rotate a vector of 90 degrees
	D3DXVec4Transform(&targetRelative, &targetRelative, &rotateMatrix);	//Rotates the original vector, to take another orthogonal
	D3DXVec4Normalize(&targetRelative, &targetRelative);


	//rilevamento di dx o sx
	D3DXMATRIX vm;
	D3DXVECTOR4 viewVector;
	xbot->d3dDevice->GetTransform(D3DTS_VIEW, &vm);
	
	D3DXVec4Transform(&viewVector, &target->currentWorldPosition, &vm);

	//if we're going to fire, we choose the proper offset
	if(xbot->isAutoFiring && !rayCompensationSet)
	{
		rayCompensationSet = true;

		if(viewVector.x < 0) //is on the left
		{
			lastRayOffset = rayOffset;
			targetRelative *= lastRayOffset;
		}
		else				//is on the right
		{
			lastRayOffset = 0;
		}

	}
	else if(rayCompensationSet)
	{
		targetRelative *= lastRayOffset;
	}


	


	target->currentWorldPosition.x =  targetRelative.x + target->currentWorldPosition.x;
	target->currentWorldPosition.y =  targetRelative.y + target->currentWorldPosition.y;	

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

	switch(xbot->lastWeaponCrc)
	{
		case CRC_SHIELD_GUN:		instantAim(target);																				break;
		case CRC_ASSAULT_RIFLE:		xbot->primFireModeSwitch ? instantAim(target)				   : ballisticAim(target, SPEED_GRANADE);	break;
		case CRC_GES:				xbot->primFireModeSwitch ? parabolicAim(target, SPEED_GES, SPEED_PGES_V0)   : parabolicAim(target, SPEED_GES, SPEED_SGES_V0);		break;
		case CRC_SHOCKRIFLE:		instantAim(target); break;
		case CRC_ROCKET_LAUNCHER:	rocketAim(target,SPEED_ROCKET);break;//instantAim(target);																				break;
		case CRC_LINK_GUN:			xbot->primFireModeSwitch ? linkGunAim(target)  : instantAim(target);						break;
		case CRC_MINIGUN:			instantAim(target);																				break;
		case CRC_FLAK_CANNON:		xbot->primFireModeSwitch ? ballisticAim(target, SPEED_PFLAK) : parabolicAim(target,SPEED_SFLAK,SPEED_SFLAK_V0);																break;
		case CRC_LIGHT_GUN:			instantAim(target);																				break;
		case CRC_SNIPER:			instantAim(target);																				break;
		default:					instantAim(target);																				break;
	}
}


void XAim::instantAim(UTarget* target)
{
	//Aggiunge la compensazione alla zona di mira
	target->aimAdjust.x = (target->direction.x * target->speed);
	target->aimAdjust.y = (target->direction.y * target->speed);
	target->aimAdjust.z = (target->direction.z * target->speed);
}

void XAim::parabolicAim(UTarget* target, float bulletSpeed, float V0)
{
	
	float G=9.8f;
	float angle = asinf( (target->distance*G) / ((V0*V0)))/2.0f;
	float z = target->distance*tan(angle);
	//Aggiunge la compensazione alla zona di mira
	
	float time = target->distance / bulletSpeed;
	
	target->aimAdjust.x = (target->direction.x * target->speed * time /* target->directionContinuity*/);
	target->aimAdjust.y = (target->direction.y * target->speed * time /* target->directionContinuity */);
	target->aimAdjust.z = -(fabs(target->bodyVector.z - target->currentWorldPosition.z)/4.0f) + 
							   (target->direction.z * target->speed * time /* target->directionContinuity */)+z;
}

void XAim::linkGunAim(UTarget* target)
{


	float bulletSpeed = sqrt (SPEED_PLINK*SPEED_PLINK + (2*ACCEL_PLINK*target->distance));

	float time = (bulletSpeed-SPEED_PLINK)/ACCEL_PLINK;

	target->aimAdjust.x = (target->direction.x * target->speed * time /* target->directionContinuity*/ );
	target->aimAdjust.y = (target->direction.y * target->speed * time /* target->directionContinuity*/ );
	target->aimAdjust.z = (target->direction.z * target->speed * time /* target->directionContinuity*/ );
}
void XAim::ballisticAim(UTarget* target, UINT bulletSpeed)
{

	float time = target->distance / bulletSpeed;

	target->aimAdjust.x = (target->direction.x * target->speed * time /** tPrimary->directionContinuity*/ );
	target->aimAdjust.y = (target->direction.y * target->speed * time /** tPrimary->directionContinuity*/ );
	target->aimAdjust.z = (target->direction.z * target->speed * time /** tPrimary->directionContinuity*/ );
}

void XAim::rocketAim(UTarget* target, UINT bulletSpeed)
{

	float time = target->distance / bulletSpeed;

	target->aimAdjust.x = (target->direction.x * target->speed * time );
	target->aimAdjust.y = (target->direction.y * target->speed * time  );
	target->aimAdjust.z = -(fabs(target->bodyVector.z - target->currentWorldPosition.z)/2.0f) + (target->direction.z * target->speed * time  );
}

void XAim::compensatePing(UTarget* target)
{
	int ping = XBot::getXBot()->pingCorrection ;

	target->aimAdjust.x += (target->direction.x * target->speed * ping);
	target->aimAdjust.y += (target->direction.y * target->speed * ping );
	target->aimAdjust.z += (target->direction.z * target->speed * ping );
}