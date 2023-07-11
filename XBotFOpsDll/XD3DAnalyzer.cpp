#include "XD3DAnalyzer.h"
#include "XBot.h"
#include "FAKE_IDirect3D8.h"

#ifdef TEXTURE_LOGGER
	#include "XTextureLogger.h"
	extern XTextureLogger *texturelogger;
#endif

bool XD3DAnalyzer::isTeamSkin(unsigned int crc)
{
	XBot* xbot = XBot::getXBot();

	if(xbot->playerTeam == XBot::TEAM_NONE)
		return false;

	else if(xbot->playerTeam == XBot::TEAM_TERROR)
		switch(crc)
		{
			case TERROR_SKIN00: return true;
			case TERROR_SKIN01: return true;
			case TERROR_SKIN02: return true;
			case TERROR_SKIN03: return true;
			case TERROR_SKIN04: return true;
			case TERROR_SKIN05: return true;
			default : return false;
		}

	else 
		switch(crc)
		{	
			case SWAT_SKIN00: return true;
			case SWAT_SKIN01: return true;
			case SWAT_SKIN02: return true;
			case SWAT_SKIN03: return true;
			case SWAT_SKIN04: return true;
			default : return false;
		}


}


bool XD3DAnalyzer::isPlayerSkin(unsigned int crc)
{
	switch(crc)
	{
	case TERROR_SKIN00: return true;
	case TERROR_SKIN01: return true;
	case TERROR_SKIN02: return true;
	case TERROR_SKIN03: return true;
	case TERROR_SKIN04: return true;
	case TERROR_SKIN05: return true;
	case SWAT_SKIN00: return true;
	case SWAT_SKIN01: return true;
	case SWAT_SKIN02: return true;
	case SWAT_SKIN03: return true;
	case SWAT_SKIN04: return true;
	}

	return false;
}

bool XD3DAnalyzer::isWeaponTexture(unsigned int crc)
{

	switch(crc)
	{
	case WEAP_FLASH_GRANADE:
	case WEAP_HE_GRANADE:
	case WEAP_UXP45:
	case WEAP_ARC_EAGLE:
	case WEAP_MACHETE:
	case WEAP_COMBAT_KNIFE:
	case WEAP_AMP7:
	case WEAP_NAPALM_GRANADE:
	case WEAP_RSMOKE_GRANADE:
	case WEAP_YSMOKE_GRANADE:
	case WEAP_RYGAR:
	case WEAP_MG5_SR:
	case WEAP_ULTRA90:
	case WEAP_RED_DRAGON:
	case WEAP_FKE103:
	case WEAP_FPN90:
	case WEAP_COMANCHE:
	case WEAP_STF_U30:
	case WEAP_CT42:		return true;
		
	default:			return false;
	}

}
bool XD3DAnalyzer::isWeaponHeldTexture(unsigned int crc)
{

	switch(crc)
	{
		case WEAP_HELD_UXP45:												
		case WEAP_HELD_ARCEAGLE:			
		case WEAP_HELD_AMP7:				
		case WEAP_HELD_MACHETE:			
		case WEAP_HELD_COMBAT_KNIFE:		
		case WEAP_HELD_RYGAR:						
		case WEAP_HELD_ULTRA90:				
		case WEAP_HELD_RED_DRAGON:				
		case WEAP_HELD_FKE103:			
		case WEAP_HELD_FPN90:				
		case WEAP_HELD_COMANCHE	:			
		case WEAP_HELD_STF_U30:			
		case WEAP_HELD_CT42:	
		case WEAP_HELD_8XENFORCER:			
		case WEAP_HELD_RMP9:					
		case WEAP_HELD_SMP45:					
		case WEAP_HELD_MG5_SR:				
		case WEAP_HELD_FMS556:				
		case WEAP_HELD_ZM8:				
		
		case THROWN_HE_GRANADE:		
		case THROWN_FLASH_GRANADE:		
		case THROWN_NAPALM_GRANADE:		
		case THROWN_RSMOKE_GRANADE:	  
		case THROWN_YSMOKE_GRANADE:	return true;
		
		default:					return false;
	}

}
void XD3DAnalyzer::getWeaponName(unsigned int crc,char* string)
{
	switch(crc)
	{
	case WEAP_FLASH_GRANADE:
	case THROWN_FLASH_GRANADE:	{sprintf(string,"FlashGranade");	return ;}
	case WEAP_HE_GRANADE:
	case THROWN_HE_GRANADE:		{sprintf(string,"HeGranade");		return ;}
	case WEAP_UXP45:
	case WEAP_HELD_UXP45:		{sprintf(string,"UXP45");			return ;}
	case WEAP_ARC_EAGLE:
	case WEAP_HELD_ARCEAGLE:	{sprintf(string,"ArcEagle");		return ;}
	case WEAP_MACHETE:	
	case WEAP_HELD_MACHETE:		{sprintf(string,"Machete");			return ;}
	case WEAP_COMBAT_KNIFE:
	case WEAP_HELD_COMBAT_KNIFE:{sprintf(string,"CombatKnife");		return ;}
	case WEAP_AMP7:	
	case WEAP_HELD_AMP7:		{sprintf(string,"AMP7");			return ;}
	case WEAP_NAPALM_GRANADE:
	case THROWN_NAPALM_GRANADE:	{sprintf(string,"Napalm");			return ;}
	case WEAP_RSMOKE_GRANADE:
	case THROWN_RSMOKE_GRANADE:	{sprintf(string,"SmokeGranade");	return ;}
	case WEAP_YSMOKE_GRANADE:
	case THROWN_YSMOKE_GRANADE:	{sprintf(string,"SmokeGranade");	return ;}
	case WEAP_RYGAR:
	case WEAP_HELD_RYGAR:		{sprintf(string,"Rygar");			return ;}
	case WEAP_MG5_SR:	
	case WEAP_HELD_MG5_SR:		{sprintf(string,"MG5-SR");			return ;}
	case WEAP_ULTRA90:
	case WEAP_HELD_ULTRA90:		{sprintf(string,"Ultra90");			return ;}
	case WEAP_RED_DRAGON:
	case WEAP_HELD_RED_DRAGON:	{sprintf(string,"RedDragon");		return ;}
	case WEAP_FKE103:
	case WEAP_HELD_FKE103:		{sprintf(string,"FKE103");			return ;}
	case WEAP_FPN90:
	case WEAP_HELD_FPN90:		{sprintf(string,"FPN90");			return ;}
	case WEAP_COMANCHE:	
	case WEAP_HELD_COMANCHE:	{sprintf(string,"Comanche");		return ;}
	case WEAP_STF_U30:
	case WEAP_HELD_STF_U30:		{sprintf(string,"STF-U30");			return ;}
	case WEAP_CT42:	
	case WEAP_HELD_CT42:		{sprintf(string,"CT42");			return ;}

	case WEAP_HELD_8XENFORCER:	{sprintf(string,"8x Enforcer");		return ;}		
	case WEAP_HELD_RMP9:		{sprintf(string,"RMP9");			return ;}			
	case WEAP_HELD_SMP45:		{sprintf(string,"SMP45");			return ;}			
	case WEAP_HELD_FMS556:		{sprintf(string,"FMS556");			return ;}		
	case WEAP_HELD_ZM8:			{sprintf(string,"ZM8	");			return ;}
	/*	case WEAP21:
	case WEAP22:
	case WEAP23:
	case WEAP24:
	case WEAP25:
	case WEAP26:
	case WEAP27:
	case WEAP28: */
		
	default:					{sprintf(string,"None");			return ;}
	}


}


bool XD3DAnalyzer::isGranadeTexture(unsigned int crc)
{
	switch(crc)
	{
		case THROWN_HE_GRANADE:		
		case THROWN_FLASH_GRANADE:		
		case THROWN_NAPALM_GRANADE:		
		case THROWN_RSMOKE_GRANADE:	  
		case THROWN_YSMOKE_GRANADE: break;

		default:
			return false;
		break;
	}
	return true;

}

bool XD3DAnalyzer::IsInTextureList(FAKE_IDirect3DTexture8* tex)
{
	XBot* xbot = XBot::getXBot();


	for (unsigned int i = 0; i < xbot->texturesList.size(); i++)
		if (tex == xbot->texturesList[i])
			return true;
	return false;
}




bool XD3DAnalyzer::ProcessDrawIndexedPrimitive(D3DPRIMITIVETYPE Type, UINT MinIndex, UINT NumVertices, UINT StartIndex, UINT PrimitiveCount)
{
	XBot* xbot = XBot::getXBot();

	
	switch(xbot->stride)
	{
		case 24:
		{

			if(currentRenderedObjectType == TYPE_GRANADE)
			{
				char TYPE = -1;
				switch(xbot->currentTexture->Crc32)
				{
					case THROWN_HE_GRANADE:		if(TYPE == -1) TYPE=UTarget::TARGET_GRANADE_HE;
					case THROWN_FLASH_GRANADE:	if(TYPE == -1) TYPE=UTarget::TARGET_GRANADE_FLASH;
					case THROWN_NAPALM_GRANADE:	if(TYPE == -1) TYPE=UTarget::TARGET_GRANADE_NAPALM;
					case THROWN_RSMOKE_GRANADE:	if(TYPE == -1) TYPE=UTarget::TARGET_GRANADE_RSMOKE;
					case THROWN_YSMOKE_GRANADE:	if(TYPE == -1) TYPE=UTarget::TARGET_GRANADE_YSMOKE;
						{
							D3DXMATRIX World;
							D3DXMATRIX Projection;
							D3DXMATRIX View;

							xbot->d3dDevice->GetTransform(D3DTS_WORLD,&World);
							xbot->d3dDevice->GetTransform(D3DTS_PROJECTION, &Projection);
							xbot->d3dDevice->GetTransform(D3DTS_VIEW, &View);
				
							if(!xbot->tSecondary->isValid)
							{
								xbot->tSecondary->setType(TYPE);
								xbot->setSecondaryTarget(&World);
							}					
						
							UTarget granade((D3DXMATRIX*)&World);
	
							D3DXVECTOR3 ZeroVec(0,0,0);
							D3DXVec3Project(&granade.screenCoords, &ZeroVec, &xbot->currentViewport, &Projection, &View, &World);
							
							granade.setType(TYPE);

							xbot->radarGranadeList.push_back(granade);
									
						}
						break;
					default: 
						break;
				}
			}


		}
		break;	
		
		case 32:
		{
	
			
			
			if(currentRenderedObjectType == TYPE_WEAPON)
			{
				xbot->d3dDevice->GetTransform(D3DTS_WORLD,&xbot->lastPlayerWorldPosition);
					
			}
			if((currentRenderedObjectType == TYPE_WEAPON_HELD || currentRenderedObjectType == TYPE_GRANADE)  && xbot->lastPlayerSkinDrawnFlag == 0)
			{
							D3DXMATRIX World;
				D3DXMATRIX Projection;
				D3DXMATRIX View;

				xbot->d3dDevice->GetTransform(D3DTS_WORLD,&World);
				xbot->d3dDevice->GetTransform(D3DTS_PROJECTION, &Projection);
				xbot->d3dDevice->GetTransform(D3DTS_VIEW, &View);

				UObject weapon((D3DXMATRIX*)&World);
	
				D3DXVec3Project(&weapon.screenCoords, &D3DXVECTOR3(0,0,0), &xbot->currentViewport, &Projection, &View, &World);
				getWeaponName(xbot->currentTexture->Crc32,weapon.name);

				xbot->radarWeaponList.push_back(weapon);

				xbot->lastPlayerSkinDrawnFlag = 0;
					
			}
			else if(currentRenderedObjectType == TYPE_TERROR_GLOVES  ) 
			{
				xbot->playerTeam = XBot::TEAM_TERROR;
				xbot->d3dDevice->GetTransform(D3DTS_WORLD,&xbot->lastPlayerWorldPosition);
			}

			else if(currentRenderedObjectType == TYPE_SWAT_GLOVES )
			{
				xbot->playerTeam = XBot::TEAM_SWAT;
				xbot->d3dDevice->GetTransform(D3DTS_WORLD,&xbot->lastPlayerWorldPosition);
			}
			//HEAD DETECTED
			else if(currentRenderedObjectType == TYPE_PLAYERHEAD)
			{
		
				if(xbot->masterSwitch && xbot->headshotSwitch ) 
				{
						
					D3DXMATRIX World;
					D3DXMATRIX Projection;
					D3DXMATRIX View;

					xbot->d3dDevice->GetTransform(D3DTS_WORLD,&World);
					xbot->d3dDevice->GetTransform(D3DTS_PROJECTION, &Projection);
					xbot->d3dDevice->GetTransform(D3DTS_VIEW, &View);
				
					D3DVECTOR middlePoint;
					UObject::getMiddlePoint(&middlePoint,  MinIndex,  NumVertices,  StartIndex);
						

					UTarget newTarget;
					D3DXVec3Project(&newTarget.screenCoords, (D3DXVECTOR3*)&middlePoint, &xbot->currentViewport, &Projection, &View, &World);

					if(	(xbot->autoAimSwitch || xbot->imodeType == XBot::IMODE_FIXER) && 
						(!xbot->tPrimary->isValid || (newTarget.get2dDistanceFrom(xbot->currentPlayer)<xbot->tPrimary->distance2D && !xbot->targetLocked))
					  )	
					{
						xbot->tPrimary->setType(UTarget::TARGET_HEAD);
						xbot->setPrimaryTarget(&World,&middlePoint);	
					}
					else 
						xbot->addToRadar(&World,&middlePoint,true,true);
					
									
				}
				
				currentRenderedObjectType = TYPE_OTHER;

			}

			else if(currentRenderedObjectType == TYPE_PLAYERSKIN)
			{
					
				if (xbot->masterSwitch)
				{
					D3DXMATRIX World;
					xbot->d3dDevice->GetTransform(D3DTS_WORLD,&World);
				
					D3DVECTOR middlePoint;
					UObject::getMiddlePoint(&middlePoint,  MinIndex,  NumVertices,  StartIndex);
					if(middlePoint.z>60.0f) //CHECK IF PLAYER IS DEAD
					{					
						if(!isTeamSkin(xbot->currentTexture->Crc32))//CHECK IF PLAYER IS HOSTILE
						{
							currentRenderedObjectType = TYPE_PLAYERHEAD;
								
							if(!xbot->headshotSwitch)
							{
								D3DXMATRIX Projection;
								D3DXMATRIX View;
									
								xbot->d3dDevice->GetTransform(D3DTS_PROJECTION, &Projection);
								xbot->d3dDevice->GetTransform(D3DTS_VIEW, &View);
									
								UTarget newTarget;
								D3DXVec3Project(&newTarget.screenCoords, (D3DXVECTOR3*)&middlePoint, &xbot->currentViewport, &Projection, &View, &World);

								if(	(xbot->autoAimSwitch || xbot->imodeType == XBot::IMODE_FIXER) && 
									(!xbot->tPrimary->isValid || (newTarget.get2dDistanceFrom(xbot->currentPlayer)<xbot->tPrimary->distance2D && !xbot->targetLocked))
								  )
								{
										
									xbot->tPrimary->setType(UTarget::TARGET_CHEST);
									xbot->setPrimaryTarget(&World,&middlePoint);
								}
								else
									xbot->addToRadar(&World,&middlePoint);
								
							}
						}
						else
						{
							xbot->lastPlayerSkinDrawnFlag = 1;
							xbot->addToRadar(&World,&middlePoint,false);
						}
					}
					else if(xbot->tPrimary->isSameTarget(&World))
							xbot->targetLocked = false;	
				}
			}
			

		}
		break;
		
		case 36:
		{

			if (currentRenderedObjectType == TYPE_FOPS_LOGO)
				DrawBotLogos();
			else if(xbot->wallHack && xbot->masterSwitch)
				return D3D_OK;

			
		}
		break;

		case 40:
		{
		}
		break;
		
		default:
		break;
	}
	if(currentRenderedObjectType != TYPE_PLAYERHEAD)
		currentRenderedObjectType = TYPE_OTHER;

	return true;	
}


void XD3DAnalyzer::ProcessDrawPrimitive(D3DPRIMITIVETYPE PrimitiveType, UINT StartVertex, UINT PrimitiveCount)
{
	XBot* xbot = XBot::getXBot();

	switch(xbot->currentTexture->Crc32)
	{
		case CRC_MENU_MOUSEICON:
		case CRC_MENU_MOUSEICON2:
			xbot->gameStarted = false;
			break;
		case CRC_INGAME_CLOCK:
			xbot->gameStarted=true;
	
	}
	

}

void XD3DAnalyzer::AnalyzeTexture(unsigned int crc)
{
	if(isPlayerSkin(crc))
		currentRenderedObjectType = TYPE_PLAYERSKIN;
	
	else if(isWeaponTexture(crc))
	{
		currentRenderedObjectType = TYPE_WEAPON;
		XBot::getXBot()->currentWeaponCrc = crc;
	}
		
	else if(isGranadeTexture(crc))
		currentRenderedObjectType = TYPE_GRANADE;
	
	else if(isWeaponHeldTexture(crc))
		currentRenderedObjectType = TYPE_WEAPON_HELD;

	else if(crc == SWAT_GLOVES)
		currentRenderedObjectType = TYPE_SWAT_GLOVES;

	else if(crc == TERROR_GLOVES)
		currentRenderedObjectType = TYPE_TERROR_GLOVES;
			
	else if(crc == CRC_NVIDIA_SLOGAN)
		currentRenderedObjectType = TYPE_FOPS_LOGO;


}
	
