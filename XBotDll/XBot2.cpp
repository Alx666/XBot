#include "XBot.h"

#ifdef TEST
	#include <stdio.h>
	extern FILE* logfile;
#endif

extern IDirect3DDevice8 *pD3DDevice8;

void XBot::Aim()
{
	if(!gameStarted)
		return;

	if(masterSwitch &&  tSecondary->isValid && blastCombo)
	{
		moveMouseX = (tSecondary->adjustedScreenCoords.x - (currentViewport.Width/2)) /mouseSensibility;
		moveMouseY = (tSecondary->adjustedScreenCoords.y - (currentViewport.Height/2)) /mouseSensibility;
		
		aimAssistant->process(&moveMouseX, &moveMouseY);

	}
	else if(masterSwitch && tPrimary->isValid)
	{
		moveMouseX = (tPrimary->adjustedScreenCoords.x - (currentViewport.Width/2)) /mouseSensibility;
		moveMouseY = (tPrimary->adjustedScreenCoords.y - (currentViewport.Height/2)) /mouseSensibility;

		aimAssistant->process(&moveMouseX, &moveMouseY);
	}
	else
		aimAssistant->lineOfFire = false;


	if(tPrimary->isValid == false)
	{
		tPrimary->lastWorldPosition.x = 0;
		tPrimary->lastWorldPosition.y = 0;
		tPrimary->lastWorldPosition.z = 0;

	}
}


void XBot::SetPlayerWorldPosition()
{
	//This is the base position of the player in worldspace
	D3DXVECTOR3 myVec(0, 0, 0);
	D3DXVec3Transform((D3DXVECTOR4*)&currentPlayer->currentWorldPosition, &myVec, (D3DXMATRIX*)&lastPlayerWorldPosition);
			
	currentPlayer->direction.x = currentPlayer->currentWorldPosition.x - currentPlayer->lastWorldPosition.x;
	currentPlayer->direction.y = currentPlayer->currentWorldPosition.y - currentPlayer->lastWorldPosition.y;
	currentPlayer->direction.z = currentPlayer->currentWorldPosition.z - currentPlayer->lastWorldPosition.z;
	
	if(fabs(currentPlayer->direction.x) < 3.0f)// annulliamo i piccoli movimenti della Z per il bobbing
		currentPlayer->direction.x = 0.0f;

	if(fabs(currentPlayer->direction.y) < 3.0f)// annulliamo i piccoli movimenti della Z per il bobbing
		currentPlayer->direction.y = 0.0f;
	
	if(fabs(currentPlayer->direction.z) < 6.0f)// annulliamo i piccoli movimenti della Z per il bobbing
		currentPlayer->direction.z = 0.0f;

	//D3DXVec3Normalize(&currentPlayer->direction,&currentPlayer->direction);

	currentPlayer->speed = PLAYER_SPEED_NON_NORMALIZED - 1;

	currentPlayer->lastWorldPosition = currentPlayer->currentWorldPosition;

	currentPlayer->screenCoords.x = currentViewport.Width/2;
	currentPlayer->screenCoords.y = currentViewport.Height/2;


}


void XBot::setSecondaryTarget(D3DMATRIX* matrix)
{
	D3DXMATRIX Projection;
	D3DXMATRIX View;
	D3DXMATRIX World;
	

	pD3DDevice8->GetTransform(D3DTS_PROJECTION, &Projection);
	pD3DDevice8->GetTransform(D3DTS_VIEW, &View);
	pD3DDevice8->GetTransform(D3DTS_WORLD, &World);

	

	if( (lastWeaponCrc == CRC_SHOCKRIFLE && secFireDown && ( (currentPlayer->getDistanceFrom(&shockCoreList.back()) < SHOCK_CORE_MIN_TRACKING_DIST && shockCoreList.back().shkCoreRsvrdFlag == -1) ||
		tSecondary->isSameTarget(&World) && shockCoreList.back().shkCoreRsvrdFlag != -1)) || (lastWeaponCrc == CRC_SHOCKRIFLE && counterShockEnabled))
	{	
	
		D3DXVECTOR3 myVec(0, 0, 0);
		D3DXVec3Transform(&tSecondary->currentWorldPosition, &myVec, (D3DXMATRIX*)matrix);

		D3DXVECTOR3 Vector(0, 0, 0);
		D3DXVec3Project(&tSecondary->screenCoords, &Vector, &currentViewport, &Projection, &View, &World);


		tSecondary->distance = tSecondary->getDistanceFrom(currentPlayer);
		tSecondary->speed = 1.2f; //distance / millisec
		

		tSecondary->direction.x = tSecondary->currentWorldPosition.x - tSecondary->lastWorldPosition.x;
		tSecondary->direction.y = tSecondary->currentWorldPosition.y - tSecondary->lastWorldPosition.y;
		tSecondary->direction.z = tSecondary->currentWorldPosition.z - tSecondary->lastWorldPosition.z;
		
		D3DXVec3Normalize(&tSecondary->direction, &tSecondary->direction);


		tSecondary->lastWorldPosition = tSecondary->currentWorldPosition;

		tSecondary->aimAdjust.x = 0;
		tSecondary->aimAdjust.y = 0;
		tSecondary->aimAdjust.z = 0;

		aimAssistant->addWeaponOffset(tSecondary);
		aimAssistant->compensateMovement(tSecondary);
		aimAssistant->compensateRay(tSecondary);
		aimAssistant->compensatePing(tSecondary);
		
		
		D3DXVECTOR3 ZeroVec(0,0,0);
		D3DXMatrixIdentity(&World);
		
		D3DXMatrixTranslation(&World,(tSecondary->currentWorldPosition.x + tSecondary->aimAdjust.x),
									 (tSecondary->currentWorldPosition.y + tSecondary->aimAdjust.y),
									 (tSecondary->currentWorldPosition.z + tSecondary->aimAdjust.z));

		D3DXVec3Project(&tSecondary->adjustedScreenCoords, &ZeroVec, &currentViewport, &Projection, &View, &World);
		
		tSecondary->isValid = true;
	}


}




void XBot::setPrimaryTarget(D3DMATRIX* matrix,D3DVECTOR *mPoint)
{



	D3DXMATRIX Projection;
	D3DXMATRIX View;
	D3DXMATRIX World;
	

	pD3DDevice8->GetTransform(D3DTS_PROJECTION, &Projection);
	pD3DDevice8->GetTransform(D3DTS_VIEW, &View);
	pD3DDevice8->GetTransform(D3DTS_WORLD, &World);

	
	float heightCorrection;
	if(tPrimary->type==TARGET_CHEST)
		heightCorrection=mPoint->z/4;
	else
		heightCorrection=0.0f;
	
	D3DXVECTOR3 tmp(mPoint->x,mPoint->y,mPoint->z+heightCorrection);		
	
	
	D3DXVECTOR3 screenSpace;
	D3DXVec3Project(&screenSpace, &tmp, &currentViewport, &Projection, &View, &World);


	if( (!targetLocked && abs(screenSpace.x-(currentViewport.Width/2))<crosshairRadius && abs(screenSpace.y-(currentViewport.Height/2))<crosshairRadius) 
		|| (targetLocked && tPrimary->isSameTarget(&World)))
	{

		tPrimary->screenCoords=screenSpace;

		D3DXVECTOR3 ZeroVec(0,0,0);

		D3DXVec3Transform(&tPrimary->currentWorldPosition, &ZeroVec, (D3DXMATRIX*)&World);
		D3DXVec3Transform(&tPrimary->bodyVector, &tmp, (D3DXMATRIX*)&World);

		tPrimary->distance		= tPrimary->getDistanceFrom(currentPlayer);
		tPrimary->distance2D	= tPrimary->get2dDistanceFrom(currentPlayer);

		
		if(tPrimary->lastWorldPosition.x!=0 || tPrimary->lastWorldPosition.y!=0 || tPrimary->lastWorldPosition.z!=0)
		{
			tPrimary->direction.x = tPrimary->bodyVector.x - tPrimary->lastWorldPosition.x;
			tPrimary->direction.y = tPrimary->bodyVector.y - tPrimary->lastWorldPosition.y;
			tPrimary->direction.z = tPrimary->bodyVector.z - tPrimary->lastWorldPosition.z;
		}
		else
		{
			tPrimary->direction.x = 0;
			tPrimary->direction.y = 0;
			tPrimary->direction.z = 0;

		}		


		if(fabs(tPrimary->direction.z) < 3.0f)// annulliamo i piccoli movimenti della Z per il bobbing
			tPrimary->direction.z = 0.0f;
		if(fabs(tPrimary->direction.y) < 3.0f)// annulliamo i piccoli movimenti della y per il bobbing
			tPrimary->direction.y = 0.0f;
		if(fabs(tPrimary->direction.x) < 3.0f)// annulliamo i piccoli movimenti della x per il bobbing
			tPrimary->direction.x = 0.0f;

		float dAngle;
		if(!normalizedPlayerSpeed)
		{
			tPrimary->speed = PLAYER_SPEED_NON_NORMALIZED;
			//D3DXVECTOR3 tmpNorm(0,0,0);
			//D3DXVec3Normalize(&tmpNorm, &tPrimary->direction);
			//dAngle = 57.2957795f * acos(tmpNorm.x);

		}
		else
		{
			tPrimary->speed = PLAYER_SPEED_NORMALIZED;
			D3DXVec3Normalize(&tPrimary->direction, &tPrimary->direction);
			//dAngle = 57.2957795f * acos(tPrimary->direction.x);
		}
		
		/*if(fabs(dAngle-tPrimary->directionAngle) < 40.0f )//test value
		{
			if(tPrimary->directionContinuity < 1.0f)
				tPrimary->directionContinuity *= 4.0f;
			if(tPrimary->directionContinuity > 1.0f)
				tPrimary->directionContinuity = 1.0f;
		}
		else 
			tPrimary->directionContinuity =  0.000001f;

		tPrimary->directionAngle = dAngle;*/

		
		tPrimary->lastWorldPosition = tPrimary->bodyVector;//currentWorldPosition;

		aimAssistant->addWeaponOffset(tPrimary);
		aimAssistant->compensateMovement(tPrimary);
		aimAssistant->compensateRay(tPrimary);
		//aimAssistant->compensatePing(tPrimary);

		D3DXMatrixIdentity(&World);
		D3DXMatrixTranslation(&World,(tPrimary->bodyVector.x)+(tPrimary->aimAdjust.x),
									 (tPrimary->bodyVector.y)+(tPrimary->aimAdjust.y),
									 (tPrimary->bodyVector.z)+(tPrimary->aimAdjust.z));

		D3DXVec3Project(&tPrimary->adjustedScreenCoords, &ZeroVec, &currentViewport, &Projection, &View, &World);

		if(tPrimary->isValid || (imodeType != IMODE_NONE && !autoAimSwitch))
			radarListHostile.push_back(*tPrimary);


		if(autoAimSwitch)
			tPrimary->isValid=true;
		else  
		{
			if(imodeSwitch) 
			{
				tPrimary->isInRange = true;	
				if(imodeType == IMODE_FIXER && checkHeldWeapon() && ((primFireDown && !blastCombo) || (secFireDown && lastWeaponCrc != CRC_SHOCKRIFLE)))
					setAutoAim(true);
			}
				
		}
		
		return;
		
	}
	
	if(tPrimary->type==TARGET_CHEST)
		addToRadar(matrix,mPoint);
	else
		addToRadar(matrix,mPoint,true,true);

}

void XBot::addToRadar(D3DMATRIX* matrix,D3DVECTOR *mPoint,bool hostile,bool head)
{


	D3DXMATRIX Projection;
	D3DXMATRIX View;
	D3DXMATRIX World;
	

	pD3DDevice8->GetTransform(D3DTS_PROJECTION, &Projection);
	pD3DDevice8->GetTransform(D3DTS_VIEW, &View);
	pD3DDevice8->GetTransform(D3DTS_WORLD, &World);

	UTarget skin((D3DXMATRIX*)matrix);

	float heightCorrection;
	if(!head)
		heightCorrection=60.0f;
	else
		heightCorrection=-30.0f;

	skin.distance = skin.getDistanceFrom(currentPlayer);
	
	D3DXVECTOR3 tmp(mPoint->x,mPoint->y,mPoint->z + heightCorrection);		

	
	D3DXVec3Project(&skin.screenCoords, (D3DXVECTOR3*)&tmp, &currentViewport, &Projection, &View, &World);
	

	if(hostile)
		radarListHostile.push_back(skin);
	
	else
		radarListFriendly.push_back(skin);


}

void XBot::comboNearestTarget()
{

	UTarget t;
	t.currentWorldPosition = tSecondary->currentWorldPosition;
	t.direction = tSecondary->direction;

	for(int i = 0; i<radarListHostile.size(); i++)
	{
	
		
		float comboDist = t.getDistanceFrom(&radarListHostile[i]);

		if(comboDist < shockComboMAXAutoBlastRange)
		{

			t.currentWorldPosition.x += t.direction.x * 2;
			t.currentWorldPosition.y += t.direction.y * 2;
			t.currentWorldPosition.z += t.direction.z * 2;

			float comboDist2 = t.getDistanceFrom(&radarListHostile[i]);

			if(comboDist < shockComboMINAutoBlastRange || comboDist < comboDist2) 	
			{
				if(imodeSwitch && (imodeType != IMODE_NONE && imodeType != IMODE_AUTOCOMBO))
				{
					InputDown.ki.wVk = VK_LBUTTON;//keyPrimFire;
					blastCombo = true;
				}
				else
					tSecondary->isInRange = true;
			}		
			break;
		}
		
		
	}

}



int XBot::getXhairSize()
{
	switch(lastWeaponCrc)
	{
		case CRC_SHIELD_GUN:		return crosshairRadiusArray[0];

		case CRC_ASSAULT_RIFLE:		return crosshairRadiusArray[1];

		case CRC_GES:				return crosshairRadiusArray[2];

		case CRC_SHOCKRIFLE:		return crosshairRadiusArray[3];

		case CRC_LINK_GUN:			return crosshairRadiusArray[4];

		case CRC_MINIGUN:			return crosshairRadiusArray[5];

		case CRC_FLAK_CANNON:		return crosshairRadiusArray[6];

		case CRC_ROCKET_LAUNCHER:	return crosshairRadiusArray[7];
				
		case CRC_LIGHT_GUN:
		case CRC_SNIPER:			return crosshairRadiusArray[8];
	
		default:
		return DEFAULT_XHAIR_SIZE;
	}

}

UINT XBot::getAimSpeed()
{
	switch(lastWeaponCrc)
	{
		case CRC_SHIELD_GUN:		return aimSpeedArray[0];

		case CRC_ASSAULT_RIFLE:		return aimSpeedArray[1];

		case CRC_GES:				return aimSpeedArray[2];

		case CRC_SHOCKRIFLE:		return aimSpeedArray[3];

		case CRC_LINK_GUN:			return aimSpeedArray[4];

		case CRC_MINIGUN:			return aimSpeedArray[5];

		case CRC_FLAK_CANNON:		return aimSpeedArray[6];

		case CRC_ROCKET_LAUNCHER:	return aimSpeedArray[7];
				
		case CRC_LIGHT_GUN:
		case CRC_SNIPER:			return aimSpeedArray[8];
	
		default:
		return DEFAULT_AIM_SPEED;
	}

}

void XBot::modifyXHairSize()
{

	switch(lastWeaponCrc)
	{
		case CRC_SHIELD_GUN:		crosshairRadiusArray[0] = crosshairRadius;
		break;

		case CRC_ASSAULT_RIFLE:		crosshairRadiusArray[1] = crosshairRadius;
		break;

		case CRC_GES:				crosshairRadiusArray[2] = crosshairRadius;
		break;

		case CRC_SHOCKRIFLE:		crosshairRadiusArray[3] = crosshairRadius;
		break;

		case CRC_LINK_GUN:			crosshairRadiusArray[4] = crosshairRadius;
		break;

		case CRC_MINIGUN:			crosshairRadiusArray[5] = crosshairRadius;
		break;

		case CRC_FLAK_CANNON:		crosshairRadiusArray[6] = crosshairRadius;
		break;

		case CRC_ROCKET_LAUNCHER:	crosshairRadiusArray[7] = crosshairRadius;
		break;	
		
		case CRC_LIGHT_GUN:
		case CRC_SNIPER:			crosshairRadiusArray[8] = crosshairRadius;
		break;	
			
		default:
			return;
		break;
	}
	

}

void XBot::setImodeType()
{

	int i = 0;
	switch(currentWeaponCrc)
	{
		case CRC_SHIELD_GUN:		i = 0;
		break;

		case CRC_ASSAULT_RIFLE:		i = 1;
		break;

		case CRC_GES:				i = 2;
		break;

		case CRC_SHOCKRIFLE:		i = 3;
		break;

		case CRC_LINK_GUN:			i = 4;
		break;

		case CRC_MINIGUN:			i = 5;
		break;

		case CRC_FLAK_CANNON:		i = 6;
		break;

		case CRC_ROCKET_LAUNCHER:	i = 7;
		break;	
		
		case CRC_LIGHT_GUN:
		case CRC_SNIPER:			i = 8;
		break;	

		default:
			return;
		break;
	}

	switch(imodeTypeArray[i])
	{
	case IMODE_TYPE_FIXER:
		imodeType = IMODE_FIXER;
		//setAutoAim(false);
		//imodeSwitch = true;
		break;
	case IMODE_TYPE_AUTO:
		imodeType = IMODE_AUTO;
		//setAutoAim(false);
		//imodeSwitch = false;
		break;
	case IMODE_TYPE_NONE_ENABLED:
		imodeType = IMODE_NONE;
		//imodeSwitch = false;
		//setAutoAim(true);
		break;
	case IMODE_TYPE_NONE_DISABLED:
		imodeType = IMODE_NONE;
		//imodeSwitch = false;
		//setAutoAim(false);
		break;
	}

	return;
}

void XBot::modifyImodeType()
{

	
	int i = 0;
	switch(lastWeaponCrc)
	{
		case CRC_SHIELD_GUN:		i = 0;
		break;

		case CRC_ASSAULT_RIFLE:		i = 1;
		break;

		case CRC_GES:				i = 2;
		break;

		case CRC_SHOCKRIFLE:		i = 3;
		break;

		case CRC_LINK_GUN:			i = 4;
		break;

		case CRC_MINIGUN:			i = 5;
		break;

		case CRC_FLAK_CANNON:		i = 6;
		break;

		case CRC_ROCKET_LAUNCHER:	i = 7;
		break;	
		
		case CRC_LIGHT_GUN:
		case CRC_SNIPER:			i = 8;
		break;	

		default:
			return;
		break;
	}
	

	switch(imodeType)
	{
	case IMODE_FIXER:
		imodeTypeArray[i] = IMODE_TYPE_FIXER;
		break;
	case IMODE_AUTO:
		imodeTypeArray[i] = IMODE_TYPE_AUTO;
		break;
	case IMODE_NONE:
		if(autoAimSwitch)
			imodeTypeArray[i] = IMODE_TYPE_NONE_ENABLED;
		else
			imodeTypeArray[i] = IMODE_TYPE_NONE_DISABLED;
		break;
	}
	


}
