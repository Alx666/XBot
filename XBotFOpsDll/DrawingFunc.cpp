#include "DrawingFunc.h"
#include "FAKE_IDirect3D8.h"
#include "XBot.h"
#include "structs.h"


#ifdef TEST
	#include <stdio.h>
	extern FILE* logfile;
#endif


//mettere statiche
extern FAKE_IDirect3D8 FAKE_D3D8;
extern FAKE_IDirect3D8 *pFAKE_D3D8;						
extern IDirect3D8 *pD3D8;						
extern FAKE_IDirect3DDevice8 FAKE_D3DDevice8;
extern FAKE_IDirect3DDevice8 *pFAKE_D3DDevice8;		
extern IDirect3DDevice8 *pD3DDevice8;

void DrawOnEndScene()
{
	XBot* xbot = XBot::getXBot();

	if(xbot->stealthMode)
		return;

	//save old state
	DWORD oldState;
	pD3DDevice8->CreateStateBlock(D3DSBT_ALL, &oldState);
	pD3DDevice8->CaptureStateBlock(oldState);
	
	
	///////////////////////////BEGIN SPRITE DRAWING/////////////////////////////////////////////////////////////////////
	xbot->spriteDrawer->Begin();

	if(xbot->gameStarted && xbot->masterSwitch)
	{		
		
		if(xbot->autoAimSwitch)		//TODO: (DISCUTERNE) Spostare la crossair e la sua gestione all'interno di XMENU
		{
			xbot->spriteDrawer->Draw(xbot->targetRadius,  NULL, &D3DXVECTOR2(xbot->crosshairRadius/256.0f,xbot->crosshairRadius/256.0f) , NULL, 0 ,  
									&D3DXVECTOR2(float((xbot->currentViewport.Width>>1))-(256*(xbot->crosshairRadius/256.0f)),
									float((xbot->currentViewport.Height>>1))-(256*(xbot->crosshairRadius/256.0f))), 0xBBFFFFFF);
		}
						
	}
	
	if((xbot->gameStarted || xbot->menu->isOut) &&  xbot->masterSwitch)
		xbot->menu->draw();			//TODO: (PRIORITA' BASSA) xbot->menu->draw(); ===> xbot->drawHud(); che comprende anche la crosshair

	xbot->spriteDrawer->End();
	///////////////////////////END SPRITE DRAWING/////////////////////////////////////////////////////////////////////


	// Restore old state
	pD3DDevice8->ApplyStateBlock(oldState);
	pD3DDevice8->DeleteStateBlock(oldState);

	DrawTargetsRadarPix();

}

void DrawTargetsRadarPix()
{

	XBot* xbot = XBot::getXBot();
	static char str[32];

	if(!xbot->radarSwitch || !xbot->gameStarted || !xbot->masterSwitch)
		return;
	
	xbot->spriteDrawer->Begin();
	xbot->radarFont->Begin();

	//HOSTILE RADAR PIX
	for (int i=0;i<xbot->radarListHostile.size();i++)
	{
		xbot->spriteDrawer->Draw(xbot->radarPixHostile,  NULL,  NULL, NULL, 0 ,  &D3DXVECTOR2(xbot->radarListHostile[i].screenCoords.x-16,xbot->radarListHostile[i].screenCoords.y-16) , 0x99FFFFFF);             

		//DRAW DISTANCE
		xbot->fontPosition.left = xbot->radarListHostile[i].screenCoords.x + 16;
		xbot->fontPosition.right = xbot->radarListHostile[i].screenCoords.x + 50;
		xbot->fontPosition.top = xbot->radarListHostile[i].screenCoords.y -8;
		xbot->fontPosition.bottom = xbot->radarListHostile[i].screenCoords.x + 8;
		
		sprintf(str,"%i",(int)xbot->radarListHostile[i].distance/100);
		
		xbot->radarFont->DrawText(str, -1, &xbot->fontPosition, DT_CENTER, 0xFFFF0000);
		
		
	}


	//DRAW WEAPON NAME
	for ( i=0;i<xbot->radarWeaponList.size();i++)
	{

		xbot->fontPosition.left = xbot->radarWeaponList[i].screenCoords.x + 10;
		xbot->fontPosition.right = xbot->radarWeaponList[i].screenCoords.x + 90;
		xbot->fontPosition.top = xbot->radarWeaponList[i].screenCoords.y -30;
		xbot->fontPosition.bottom = xbot->radarWeaponList[i].screenCoords.x - 20;
		
		xbot->radarFont->DrawText(xbot->radarWeaponList[i].name, -1, &xbot->fontPosition, DT_LEFT, 0xFFFFFFFF);

	}

	//FRIENDLY RADAR PIX
	for (i=0;i<xbot->radarListFriendly.size();i++)
	{
		xbot->spriteDrawer->Draw(xbot->radarPixFriendly,  NULL,  NULL, NULL, 0 ,  &D3DXVECTOR2(xbot->radarListFriendly[i].screenCoords.x-16,xbot->radarListFriendly[i].screenCoords.y-16) , 0x99FFFFFF);             
	}


	//PRIMARY RADAR PIX
	if(xbot->tPrimary->isValid)
	{
		xbot->spriteDrawer->Draw(xbot->radarPixCurrent,  NULL,  NULL, NULL, 0 ,  &D3DXVECTOR2(xbot->tPrimary->screenCoords.x-32,xbot->tPrimary->screenCoords.y-32) , 0x99FFFFFF);             
		//DRAW DISTANCE
		xbot->fontPosition.left = xbot->tPrimary->screenCoords.x + 16;
		xbot->fontPosition.right = xbot->tPrimary->screenCoords.x + 50;
		xbot->fontPosition.top = xbot->tPrimary->screenCoords.y -8;
		xbot->fontPosition.bottom = xbot->tPrimary->screenCoords.x + 8;
		
		sprintf(str,"%i",(int)xbot->tPrimary->distance/100);
		
		xbot->radarFont->DrawText(str, -1, &xbot->fontPosition, DT_CENTER, 0xFFFF0000);
	}
	
	//GRANADES RADAR PIX
	for (i=0;i<xbot->radarGranadeList.size();i++)
	{
		xbot->spriteDrawer->Draw(xbot->radarPixGranade[xbot->radarGranadeList[i].type],  NULL,  NULL, NULL, 0 ,  &D3DXVECTOR2(xbot->radarGranadeList[i].screenCoords.x-16,xbot->radarGranadeList[i].screenCoords.y-16) , 0x99FFFFFF);             
	}

	xbot->radarFont->End();
	xbot->spriteDrawer->End();



}


void DrawBotLogos()
{
	XBot* xbot = XBot::getXBot();

	if(xbot->stealthMode)
		return;

	DWORD oldState;
	pD3DDevice8->CreateStateBlock(D3DSBT_ALL, &oldState);
	pD3DDevice8->CaptureStateBlock(oldState);


	///////////////////////////BEGIN SPRITE DRAWING/////////////////////////////////////////////////////////////////////
	xbot->spriteDrawer->Begin();

	xbot->spriteDrawer->Draw(xbot->logoSprite,  NULL,  NULL, NULL, 0 ,  &D3DXVECTOR2(float(xbot->currentViewport.Width-250), 0) , 0xFFFFFFFF);             
	xbot->spriteDrawer->Draw(xbot->credtisSprite,  NULL,  NULL, NULL, 0 ,  &D3DXVECTOR2(0, xbot->currentViewport.Height-64) , 0xFFFFFFFF);             

	
	xbot->spriteDrawer->End();
	///////////////////////////END SPRITE DRAWING/////////////////////////////////////////////////////////////////////
	// Restore old state
	pD3DDevice8->ApplyStateBlock(oldState);
	pD3DDevice8->DeleteStateBlock(oldState);
		
	
}
