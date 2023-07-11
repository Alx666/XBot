#include "XBot.h"
#include "XD3DAnalyzer.h"
#include "FAKE_IDirect3D8.h"

#ifdef TEXTURE_LOGGER
	#include "XTextureLogger.h"
	extern XTextureLogger *texturelogger;
#endif
#ifdef TEST
	#include <stdio.h>
	extern FILE* logfile;
#endif

bool XD3DAnalyzer::isWeaponTexture(unsigned int crc)
{

	switch(crc)
	{
		case CRC_SHOCKRIFLE:
		break;

		case CRC_FLAK_CANNON:
		break;

		case CRC_LINK_GUN:
		break;

		case CRC_GES:
		break;
					 
		case CRC_MINIGUN:
		break;

		case CRC_ASSAULT_RIFLE:
		break;

		case CRC_SHIELD_GUN:
		break;
				
		case CRC_LIGHT_GUN:
		break;
		
		case CRC_ROCKET_LAUNCHER:
		break;
		
		case CRC_SNIPER:
		break;
		
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

bool XD3DAnalyzer::isPickupTexture(unsigned int crc)
{
	switch(crc)
	{
	case CRC_SHIELDPACK_100:	return true;
	case CRC_REDEEMER:			return true;
	case CRC_DOUBLE_DAMAGE:		return true;
	}
	return false;
}

bool XD3DAnalyzer::isTeamSkin(unsigned int crc)
{
	
	switch(XBot::getXBot()->playerTeam)
	{
	case XMenu::COLOR_RED: return  isRedSkin(crc);	
	case XMenu::COLOR_BLUE:return  isBlueSkin(crc);	
	case XMenu::COLOR_NONE:return  false;	
	default: return false;
	}
	
}

bool XD3DAnalyzer::isPlayerSkin(unsigned int crc)
{
	return isRedSkin(crc) | isBlueSkin(crc) | isDMSkin(crc);
	
}

bool XD3DAnalyzer::isRedSkin(unsigned int crc)
{
	
	bool result = true;

	switch(crc)
	{
		case PLAYER_RED_SKIN_0:
		break;

		case PLAYER_RED_SKIN_1:
		break;

		case PLAYER_RED_SKIN_2:
		break;

		case PLAYER_RED_SKIN_3:
		break;

		case PLAYER_RED_SKIN_4:
		break;

		case PLAYER_RED_SKIN_5:
		break;
					 
		case PLAYER_RED_SKIN_6:
		break;

		case PLAYER_RED_SKIN_7:
		break;

		case PLAYER_RED_SKIN_8:
		break;
				
		case PLAYER_RED_SKIN_9:
		break;
		
		case PLAYER_RED_SKIN_10:
		break;

		case PLAYER_RED_SKIN_11:
		break;

		case PLAYER_RED_SKIN_12:
		break;

		case PLAYER_RED_SKIN_13:
		break;

		case PLAYER_RED_SKIN_14:
		break;

		case PLAYER_RED_SKIN_15:
		break;
					 
		case PLAYER_RED_SKIN_16:
		break;

		case PLAYER_RED_SKIN_17:
		break;

		case PLAYER_RED_SKIN_18:
		break;
				
		case PLAYER_RED_SKIN_19:
		break;
		
		case PLAYER_RED_SKIN_20:
		break;

		case PLAYER_RED_SKIN_21:
		break;

		case PLAYER_RED_SKIN_22:
		break;

		case PLAYER_RED_SKIN_23:
		break;

		case PLAYER_RED_SKIN_24:
		break;

		case PLAYER_RED_SKIN_25:
		break;
					 
		case PLAYER_RED_SKIN_26:
		break;

		case PLAYER_RED_SKIN_27:
		break;

		case PLAYER_RED_SKIN_28:
		break;
				
		case PLAYER_RED_SKIN_29:
		break;
		
		case PLAYER_RED_SKIN_30:
		break;

		case PLAYER_RED_SKIN_31:
		break;

		case PLAYER_RED_SKIN_32:
		break;

		case PLAYER_RED_SKIN_33:
		break;

		case PLAYER_RED_SKIN_34:
		break;

		case PLAYER_RED_SKIN_35:
		break;
					 
		case PLAYER_RED_SKIN_36:
		break;

		case PLAYER_RED_SKIN_37:
		break;

		case PLAYER_RED_SKIN_38:
		break;
				
		case PLAYER_RED_SKIN_39:
		break;
		
		case PLAYER_RED_SKIN_40:
		break;

		case PLAYER_RED_SKIN_41:
		break;

		case PLAYER_RED_SKIN_42:
		break;

		case PLAYER_RED_SKIN_43:
		break;

		case PLAYER_RED_SKIN_44:
		break;

		case PLAYER_RED_SKIN_45:
		break;
					 
		case PLAYER_RED_SKIN_46:
		break;

		case PLAYER_RED_SKIN_47:
		break;

		case PLAYER_RED_SKIN_48:
		break;
				
		case PLAYER_RED_SKIN_49:
		break;
		
		case PLAYER_RED_SKIN_50:
		break;

		case PLAYER_RED_SKIN_51:
		break;

		case PLAYER_RED_SKIN_52:
		break;

		case PLAYER_RED_SKIN_53:
		break;

		case PLAYER_RED_SKIN_54:
		break;

		case PLAYER_RED_SKIN_55:
		break;
					 
		case PLAYER_RED_SKIN_56:
		break;

		case PLAYER_RED_SKIN_57:
		break;

		case PLAYER_RED_SKIN_58:
		break;
				
		case PLAYER_RED_SKIN_59:
		break;

		case	PLAYER_RED_SKIN_61:		break;
		case	PLAYER_RED_SKIN_62:		break;
		case	PLAYER_RED_SKIN_63:		break;
		case	PLAYER_RED_SKIN_64:		break;
		case	PLAYER_RED_SKIN_65:		break;
		case	PLAYER_RED_SKIN_66:		break;

		default:
			result = false;
		break;
	}

	return result;
}


bool XD3DAnalyzer::isBlueSkin(unsigned int crc)
{

	bool result = true;

	switch(crc)
	{
		case PLAYER_BLUE_SKIN_0:
		break;

		case PLAYER_BLUE_SKIN_1:
		break;

		case PLAYER_BLUE_SKIN_2:
		break;

		case PLAYER_BLUE_SKIN_3:
		break;

		case PLAYER_BLUE_SKIN_4:
		break;

		case PLAYER_BLUE_SKIN_5:
		break;
					 
		case PLAYER_BLUE_SKIN_6:
		break;

		case PLAYER_BLUE_SKIN_7:
		break;

		case PLAYER_BLUE_SKIN_8:
		break;
				
		case PLAYER_BLUE_SKIN_9:
		break;
		
		case PLAYER_BLUE_SKIN_10:
		break;

		case PLAYER_BLUE_SKIN_11:
		break;

		case PLAYER_BLUE_SKIN_12:
		break;

		case PLAYER_BLUE_SKIN_13:
		break;

		case PLAYER_BLUE_SKIN_14:
		break;

		case PLAYER_BLUE_SKIN_15:
		break;
					 
		case PLAYER_BLUE_SKIN_16:
		break;

		case PLAYER_BLUE_SKIN_17:
		break;

		case PLAYER_BLUE_SKIN_18:
		break;
				
		case PLAYER_BLUE_SKIN_19:
		break;
		
		case PLAYER_BLUE_SKIN_20:
		break;

		case PLAYER_BLUE_SKIN_21:
		break;

		case PLAYER_BLUE_SKIN_22:
		break;

		case PLAYER_BLUE_SKIN_23:
		break;

		case PLAYER_BLUE_SKIN_24:
		break;

		case PLAYER_BLUE_SKIN_25:
		break;
					 
		case PLAYER_BLUE_SKIN_26:
		break;

		case PLAYER_BLUE_SKIN_27:
		break;

		case PLAYER_BLUE_SKIN_28:
		break;
				
		case PLAYER_BLUE_SKIN_29:
		break;
		
		case PLAYER_BLUE_SKIN_30:
		break;

		case PLAYER_BLUE_SKIN_31:
		break;

		case PLAYER_BLUE_SKIN_32:
		break;

		case PLAYER_BLUE_SKIN_33:
		break;

		case PLAYER_BLUE_SKIN_34:
		break;

		case PLAYER_BLUE_SKIN_35:
		break;
					 
		case PLAYER_BLUE_SKIN_36:
		break;

		case PLAYER_BLUE_SKIN_37:
		break;

		case PLAYER_BLUE_SKIN_38:
		break;
				
		case PLAYER_BLUE_SKIN_39:
		break;
		
		case PLAYER_BLUE_SKIN_40:
		break;

		case PLAYER_BLUE_SKIN_41:
		break;

		case PLAYER_BLUE_SKIN_42:
		break;

		case PLAYER_BLUE_SKIN_43:
		break;

		case PLAYER_BLUE_SKIN_44:
		break;

		case PLAYER_BLUE_SKIN_45:
		break;
					 
		//case PLAYER_BLUE_SKIN_46:
		//break;

		case PLAYER_BLUE_SKIN_47:
		break;

		case PLAYER_BLUE_SKIN_48:
		break;
				
		case PLAYER_BLUE_SKIN_49:
		break;
		
		case PLAYER_BLUE_SKIN_50:
		break;

		case PLAYER_BLUE_SKIN_51:
		break;

		case PLAYER_BLUE_SKIN_52:
		break;

		case PLAYER_BLUE_SKIN_53:
		break;

		case PLAYER_BLUE_SKIN_54:
		break;

		case PLAYER_BLUE_SKIN_55:
		break;
					 
		case PLAYER_BLUE_SKIN_56:
		break;

		case PLAYER_BLUE_SKIN_57:
		break;

		case PLAYER_BLUE_SKIN_58:
		break;
				
		case PLAYER_BLUE_SKIN_59:
		break;

		case	PLAYER_BLUE_SKIN_61:	break;
		case	PLAYER_BLUE_SKIN_62:	break;
		case	PLAYER_BLUE_SKIN_63:	break;
		case	PLAYER_BLUE_SKIN_64:	break;
		case	PLAYER_BLUE_SKIN_65:	break;
		case	PLAYER_BLUE_SKIN_66:	break;

		default:
			result = false;
		break;
	}

	return result;
}

bool XD3DAnalyzer::isDMSkin(unsigned int crc)
{
	
	bool result = true;

	switch(crc)
	{
		case PLAYER_DM_SKIN_1:	break;
		case PLAYER_DM_SKIN_2:	break;
		case PLAYER_DM_SKIN_3:	break;
		case PLAYER_DM_SKIN_4:	break;
		case PLAYER_DM_SKIN_5:	break;
		case PLAYER_DM_SKIN_6:	break;
		case PLAYER_DM_SKIN_7:	break;
		case PLAYER_DM_SKIN_8:	break;
		case PLAYER_DM_SKIN_9:	break;
		case PLAYER_DM_SKIN_10:	break;
		case PLAYER_DM_SKIN_11:	break;
		case PLAYER_DM_SKIN_12:	break;
		case PLAYER_DM_SKIN_13:	break;
		case PLAYER_DM_SKIN_14:	break;
		case PLAYER_DM_SKIN_15:	break;
		case PLAYER_DM_SKIN_16:	break;
		case PLAYER_DM_SKIN_17:	break;
		case PLAYER_DM_SKIN_18:	break;
		case PLAYER_DM_SKIN_19:	break;
		case PLAYER_DM_SKIN_20:	break;
		case PLAYER_DM_SKIN_21:	break;
		case PLAYER_DM_SKIN_22:	break;
		case PLAYER_DM_SKIN_23:	break;
		case PLAYER_DM_SKIN_24:	break;
		case PLAYER_DM_SKIN_25:	break;
		case PLAYER_DM_SKIN_26:	break;
		case PLAYER_DM_SKIN_27:	break;
		case PLAYER_DM_SKIN_28:	break;
		case PLAYER_DM_SKIN_29:	break;
		case PLAYER_DM_SKIN_30:	break;
		case PLAYER_DM_SKIN_31:	break;
		case PLAYER_DM_SKIN_32:	break;
		case PLAYER_DM_SKIN_33:	break;
		case PLAYER_DM_SKIN_34:	break;
		case PLAYER_DM_SKIN_35:	break;
		case PLAYER_DM_SKIN_36:	break;
		case PLAYER_DM_SKIN_37:	break;
		case PLAYER_DM_SKIN_38:	break;
		case PLAYER_DM_SKIN_39:	break;
		case PLAYER_DM_SKIN_40:	break;
		case PLAYER_DM_SKIN_41:	break;
		case PLAYER_DM_SKIN_42:	break;
		case PLAYER_DM_SKIN_43:	break;
		case PLAYER_DM_SKIN_44:	break;
		case PLAYER_DM_SKIN_45:	break;
		case PLAYER_DM_SKIN_46:	break;
		case PLAYER_DM_SKIN_47:	break;
	  //case PLAYER_DM_SKIN_48: break;			
		case PLAYER_DM_SKIN_49:	break;
		case PLAYER_DM_SKIN_50:	break;
		case PLAYER_DM_SKIN_51:	break;
		case PLAYER_DM_SKIN_52:	break;
		case PLAYER_DM_SKIN_53:	break;
		case PLAYER_DM_SKIN_54:	break;
		case PLAYER_DM_SKIN_55:	break;	 
		case PLAYER_DM_SKIN_56:	break;
		case PLAYER_DM_SKIN_57:	break;
		case PLAYER_DM_SKIN_58:	break;
		case PLAYER_DM_SKIN_59:	break;
		case PLAYER_DM_SKIN_60:	break;
		case PLAYER_DM_SKIN_61:	break;
		case PLAYER_DM_SKIN_62:	break;
		case PLAYER_DM_SKIN_63:	break;
		case PLAYER_DM_SKIN_64:	break;
		case PLAYER_DM_SKIN_65:	break;
		case PLAYER_DM_SKIN_66:	break;

		default:
			result = false;
		break;
	}
	
	return result;

}

bool XD3DAnalyzer::ProcessDrawIndexedPrimitive(D3DPRIMITIVETYPE Type, UINT MinIndex, UINT NumVertices, UINT StartIndex, UINT PrimitiveCount)
{
	XBot* xbot = XBot::getXBot();

	
	switch(xbot->stride)
	{
		case 24:
		{

			if(currentRenderedObjectType == TYPE_PICKUP)
			{
				switch(xbot->currentTexture->Crc32)
				{
					case CRC_SHIELDPACK_100:xbot->pkShield100->setCoords(); break;
					case CRC_REDEEMER:		xbot->pkRedeemer->setCoords();  break;
					case CRC_DOUBLE_DAMAGE:	xbot->pkDDamage->setCoords();   break;
										
					default: break;
				}
			}


			/*#ifdef TEST
			char str[256];
			sprintf(str,"\n-> Current Texture, Crc32 : %x , Format: %u , Height : %i , Width : %i ",
																								 xbot->currentTexture->Crc32,
																								 xbot->currentTexture->Format,
																								 xbot->currentTexture->Height,
																								 xbot->currentTexture->Width);
			fwrite(str,sizeof(char),strlen(str),logfile);
			#endif*/

		}
		break;	
		
		case 32:
		{
	
			//HEAD DETECTED
			if(currentRenderedObjectType == TYPE_PLAYERHEAD)
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
						

					UTarget newTarget(&World);
					D3DXVec3Project(&newTarget.screenCoords, (D3DXVECTOR3*)&middlePoint, &xbot->currentViewport, &Projection, &View, &World);

					if(xbot->getIsInWeaponRange(&newTarget)  && (xbot->autoAimSwitch || xbot->imodeType != XBot::IMODE_NONE) && 
						(!xbot->tPrimary->isValid || (newTarget.get2dDistanceFrom(xbot->currentPlayer)<xbot->tPrimary->distance2D && !xbot->targetLocked))
					  )	
					{
						xbot->tPrimary->setType(TARGET_HEAD);
						xbot->setPrimaryTarget(&World,&middlePoint);	
					}
					else 
						xbot->addToRadar(&World,&middlePoint,true,true);
					
									
				}
				
				currentRenderedObjectType = TYPE_OTHER;

			}
			
			else if(currentRenderedObjectType == TYPE_WEAPON)
			{
				xbot->nOfDrawnWeapon++;

				//if (xbot->nOfDrawnWeapon > xbot->radarListHostile.size())
				{
					xbot->currentWeaponCrc = xbot->currentTexture->Crc32;
					xbot->d3dDevice->GetTransform(D3DTS_WORLD,&xbot->lastPlayerWorldPosition);
				}	
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
									
								UTarget newTarget(&World);
								D3DXVec3Project(&newTarget.screenCoords, (D3DXVECTOR3*)&middlePoint, &xbot->currentViewport, &Projection, &View, &World);

								if(xbot->getIsInWeaponRange(&newTarget)  && (xbot->autoAimSwitch || xbot->imodeType != XBot::IMODE_NONE) && 
									(!xbot->tPrimary->isValid || (newTarget.get2dDistanceFrom(xbot->currentPlayer)<xbot->tPrimary->distance2D && !xbot->targetLocked))
								  )
								{
									
									xbot->tPrimary->setType(TARGET_CHEST);
									xbot->setPrimaryTarget(&World,&middlePoint);
								}
								else
									xbot->addToRadar(&World,&middlePoint);
								
							}
						}
						else
						{
							xbot->addToRadar(&World,&middlePoint,false);
						}
					}
					else if(xbot->tPrimary->isSameTarget(&World))
							xbot->targetLocked = false;	
				}
			}
			else if(currentRenderedObjectType == TYPE_SHOCKCORE)
			{
					
				if(xbot->masterSwitch)
				{
					D3DMATRIX m;
					xbot->d3dDevice->GetTransform(D3DTS_WORLD,&m);
	
					bool alreadyIn = false;
					for(int i = 0; i<xbot->shockCoreList.size(); i++)
					{
						if (xbot->shockCoreList[i].isSameTarget(&m))
						{
							xbot->shockCoreList[i] =  UTarget((D3DXMATRIX*)&m);
							xbot->shockCoreList[i].shkCoreRsvrdFlag = 1;
							alreadyIn=true;
							break;
						}
					}
								
					if (!alreadyIn)
						xbot->shockCoreList.push_back(UTarget((D3DXMATRIX*)&m));

					if(!xbot->tSecondary->isValid )
					{
						xbot->tSecondary->setType(TARGET_SHOCK_CORE);
						xbot->setSecondaryTarget(&m);
					}
				}	
			
			}

		}
		break;
		
		case 36:
		{

			if (currentRenderedObjectType == TYPE_NVIDIALOGO)
				xbot->drawer->DrawBotLogos();
			
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
		case CRC_LIGHT_GUN_ZOOM:
		case CRC_SNIPER_ZOOM:
			xbot->currentWeaponCrc = CRC_LIGHT_GUN;
			break;
		case CRC_MENU_MOUSEICON:
		case CRC_MENU_MOUSEICON2:
			xbot->gameStarted = false;
			break;
		case CRC_INGAME_CLOCK:
			xbot->gameStarted=true;
			break;
	
	}
	

}

void XD3DAnalyzer::AnalyzeTexture(FAKE_IDirect3DTexture8* pTexture)
{
	unsigned int crc = pTexture->Crc32;
	
	if(isPlayerSkin(crc))
		currentRenderedObjectType = TYPE_PLAYERSKIN;
	
	else if(isWeaponTexture(crc))
	{
		currentRenderedObjectType = TYPE_WEAPON;
		XBot::getXBot()->currentTexture = pTexture;
	}	
	else if(isPickupTexture(crc))
		currentRenderedObjectType = TYPE_PICKUP;
			
	else if(crc == CRC_SHOCKCORE)
		currentRenderedObjectType = TYPE_SHOCKCORE;
				
	else if(crc == CRC_NVIDIA_SLOGAN)
		currentRenderedObjectType = TYPE_NVIDIALOGO;

	//else
	//	currentRenderedObjectType = TYPE_OTHER;

}
	
