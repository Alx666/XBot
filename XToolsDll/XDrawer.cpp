#include "XBot.h"
#include "XDrawer.h"


XDrawer::XDrawer()
{
	isReset = false;
	
	radarFont			 = 0;
    
	logoSprite			= 0;
	credtisSprite		= 0;
	targetRadius		= 0;
	radarPixCurrent		= 0;
	radarPixCombo		= 0;
	radarPixComboBlast	= 0;
	radarPixHostile		= 0;
	radarPixFriendly 	= 0;
	spriteDrawer		= 0;

	targetRadiusColor	= 0xBBFFFFFF;
	radarPixColor		= 0x99FFFFFF;
	radarTextColor		= 0xFFFF0000;
}

XDrawer::~XDrawer()
{

	spriteDrawer->OnLostDevice();
	radarFont->OnLostDevice();
	
	logoSprite->Release();
	credtisSprite->Release();
	targetRadius->Release();
	radarPixCurrent->Release();
	radarPixCombo->Release();
	radarPixComboBlast->Release();
	radarPixHostile->Release();
	radarPixFriendly->Release();
}


void XDrawer::loadTextures()
{
	XBot* xbot = XBot::getXBot();
	
	void* data;
	unsigned int fsize;
	
	fsize = xbot->xffReader->GetFile("XBot_logo","bmp",&data);
	D3DXCreateTextureFromFileInMemoryEx(d3dDevice,data,fsize	,256,256,		0, 0, D3DFMT_A8R8G8B8,	D3DPOOL_DEFAULT, D3DX_FILTER_LINEAR, D3DX_FILTER_LINEAR, 0xFF000000, NULL, NULL, &logoSprite);
	delete[] data;

	fsize = xbot->xffReader->GetFile("XBot_credits","bmp",&data);
	D3DXCreateTextureFromFileInMemoryEx(d3dDevice, data,fsize,1024,64,	0, 0, D3DFMT_UNKNOWN,	D3DPOOL_DEFAULT, D3DX_FILTER_LINEAR, D3DX_FILTER_LINEAR, 0xFF000000, NULL, NULL, &credtisSprite);	
	delete[] data;

	fsize = xbot->xffReader->GetFile("XBot_targetRadius","bmp",&data);
	D3DXCreateTextureFromFileInMemoryEx(d3dDevice, data,fsize,512,512,	0, 0, D3DFMT_UNKNOWN,	D3DPOOL_DEFAULT, D3DX_FILTER_LINEAR, D3DX_FILTER_LINEAR, 0xFF000000, NULL, NULL, &targetRadius);	
	delete[] data;

	fsize = xbot->xffReader->GetFile("XBot_radardPixCurrent","bmp",&data);
	D3DXCreateTextureFromFileInMemoryEx(d3dDevice, data,fsize	,64,64,		0, 0, D3DFMT_UNKNOWN,	D3DPOOL_DEFAULT, D3DX_FILTER_LINEAR, D3DX_FILTER_LINEAR, 0xFF000000, NULL, NULL, &radarPixCurrent);
	delete[] data;
	
	fsize = xbot->xffReader->GetFile("UT2k4_radardPixCombo","bmp",&data);
	D3DXCreateTextureFromFileInMemoryEx(d3dDevice, data,fsize	,32,32,		0, 0, D3DFMT_UNKNOWN,	D3DPOOL_DEFAULT, D3DX_FILTER_LINEAR, D3DX_FILTER_LINEAR, 0xFF000000, NULL, NULL, &radarPixCombo);
	delete[] data;
	
	fsize = xbot->xffReader->GetFile("UT2k4_radardPixComboBlast","bmp",&data);
	D3DXCreateTextureFromFileInMemoryEx(d3dDevice, data,fsize	,64,64,		0, 0, D3DFMT_UNKNOWN,	D3DPOOL_DEFAULT, D3DX_FILTER_LINEAR, D3DX_FILTER_LINEAR, 0xFF000000, NULL, NULL, &radarPixComboBlast);
	delete[] data;

	fsize = xbot->xffReader->GetFile("XBot_radardPixFriendly","bmp",&data);
	D3DXCreateTextureFromFileInMemoryEx(d3dDevice, data,fsize	,32,32,		0, 0, D3DFMT_UNKNOWN,	D3DPOOL_DEFAULT, D3DX_FILTER_LINEAR, D3DX_FILTER_LINEAR, 0xFF000000, NULL, NULL, &radarPixFriendly);
	delete[] data;
	
	fsize = xbot->xffReader->GetFile("XBot_radardPixHostile","bmp",&data);
	D3DXCreateTextureFromFileInMemoryEx(d3dDevice, data,fsize	,32,32,		0, 0, D3DFMT_UNKNOWN,	D3DPOOL_DEFAULT, D3DX_FILTER_LINEAR, D3DX_FILTER_LINEAR, 0xFF000000, NULL, NULL, &radarPixHostile);
	delete[] data;
}

void XDrawer::OnResetDevice()
{
	if(!isReset)
		isReset = true;
	else
	{
		char temp[1024];

		loadTextures();

		isReset = false;
	}
}

void XDrawer::setDevice(LPDIRECT3DDEVICE8 d3dDeviceRef)
{

	d3dDevice = d3dDeviceRef;

	//Creazione dei Font e posizionamento
	LOGFONT LogFont2 = {14,0,0,0,FW_NORMAL,false,false,false,DEFAULT_CHARSET,OUT_TT_PRECIS,CLIP_DEFAULT_PRECIS,PROOF_QUALITY,DEFAULT_PITCH,"Arial"};
	D3DXCreateFontIndirect(d3dDevice,&LogFont2,&radarFont);	


	loadTextures();


	//Creazione dei Sprite
    D3DXCreateSprite(d3dDevice, &spriteDrawer);

}

void XDrawer::DrawOnEndScene()
{
	XBot* xbot = XBot::getXBot();
	
	if(xbot->stealthMode)
		return;

	
	if(isReset)
		OnResetDevice();


	//save old state
	DWORD oldState;
	d3dDevice->CreateStateBlock(D3DSBT_ALL, &oldState);
	d3dDevice->CaptureStateBlock(oldState);
	
	
	///////////////////////////BEGIN SPRITE DRAWING/////////////////////////////////////////////////////////////////////
	spriteDrawer->Begin();
	
	if(xbot->gameStarted && xbot->masterSwitch)
	{		
		
		if(xbot->autoAimSwitch)		//TODO: (DISCUTERNE) Spostare la crossair e la sua gestione all'interno di XMENU
		{
			spriteDrawer->Draw(targetRadius,  NULL, &D3DXVECTOR2(xbot->crosshairRadius/256.0f,xbot->crosshairRadius/256.0f) , NULL, 0 ,  
									&D3DXVECTOR2(float((xbot->currentViewport.Width>>1))-(256*(xbot->crosshairRadius/256.0f)),
									float((xbot->currentViewport.Height>>1))-(256*(xbot->crosshairRadius/256.0f))), targetRadiusColor);
		}
						
	}

	spriteDrawer->End();

	if((xbot->gameStarted || xbot->menu->isOut) &&  xbot->masterSwitch)
		xbot->menu->draw();			//TODO: (PRIORITA' BASSA) xbot->menu->draw(); ===> xbot->drawHud(); che comprende anche la crosshair

	if(xbot->console->getIsOut())
		xbot->console->draw();

	///////////////////////////END SPRITE DRAWING/////////////////////////////////////////////////////////////////////


	// Restore old state
	d3dDevice->ApplyStateBlock(oldState);
	d3dDevice->DeleteStateBlock(oldState);

	DrawTargetsRadarPix();

	xbot->menu->playTimerSound();

}

void XDrawer::DrawTargetsRadarPix()
{

	XBot* xbot = XBot::getXBot();
	static char str[32];

	if(!xbot->radarSwitch || !xbot->gameStarted)
		return;
	
	spriteDrawer->Begin();
	radarFont->Begin();

	//HOSTILE RADAR PIX
	for (int i=0;i<xbot->radarListHostile.size();i++)
	{
		spriteDrawer->Draw(radarPixHostile,  NULL,  NULL, NULL, 0 ,  &D3DXVECTOR2(xbot->radarListHostile[i].screenCoords.x-16,xbot->radarListHostile[i].screenCoords.y-16) , radarPixColor);             

		//DRAW DISTANCE
		fontPosition.left = xbot->radarListHostile[i].screenCoords.x + 16;
		fontPosition.right = xbot->radarListHostile[i].screenCoords.x + 50;
		fontPosition.top = xbot->radarListHostile[i].screenCoords.y -8;
		fontPosition.bottom = xbot->radarListHostile[i].screenCoords.x + 8;
		
		sprintf(str,"%i",(int)xbot->radarListHostile[i].distance/100);
		
		radarFont->DrawText(str, -1, &fontPosition, DT_CENTER, radarTextColor);
		
		
	}
	radarFont->End();

	//FRIENDLY RADAR PIX
	for (i=0;i<xbot->radarListFriendly.size();i++)
	{
		spriteDrawer->Draw(radarPixFriendly,  NULL,  NULL, NULL, 0 ,  &D3DXVECTOR2(xbot->radarListFriendly[i].screenCoords.x-16,xbot->radarListFriendly[i].screenCoords.y-16) , radarPixColor);             
	}


	//PRIMARY RADAR PIX
	if(xbot->tPrimary->isValid)
	{
		spriteDrawer->Draw(radarPixCurrent,  NULL,  NULL, NULL, 0 ,  &D3DXVECTOR2(xbot->tPrimary->screenCoords.x-32,xbot->tPrimary->screenCoords.y-32) , radarPixColor);             
		//DRAW DISTANCE
		fontPosition.left = xbot->tPrimary->screenCoords.x + 16;
		fontPosition.right = xbot->tPrimary->screenCoords.x + 50;
		fontPosition.top = xbot->tPrimary->screenCoords.y -8;
		fontPosition.bottom = xbot->tPrimary->screenCoords.x + 8;
		
		sprintf(str,"%i",(int)xbot->tPrimary->distance/100);
		
		radarFont->DrawText(str, -1, &fontPosition, DT_CENTER, radarTextColor);
	}
	
	//SECONDARY RADAR PIX
	if (xbot->tSecondary->isValid && !xbot->tSecondary->isInRange)
		spriteDrawer->Draw(radarPixCombo,  NULL,  NULL, NULL, 0 ,  &D3DXVECTOR2(xbot->tSecondary->screenCoords.x-16,xbot->tSecondary->screenCoords.y-16) , radarPixColor);             
	
	else if(xbot->tSecondary->isValid && xbot->tSecondary->isInRange)
		spriteDrawer->Draw(radarPixComboBlast,  NULL,  NULL, NULL, 0 ,  &D3DXVECTOR2(xbot->tSecondary->screenCoords.x-32,xbot->tSecondary->screenCoords.y-32) , radarPixColor);             

	spriteDrawer->End();



}


void XDrawer::DrawBotLogos()
{
	XBot* xbot = XBot::getXBot();

	if(xbot->stealthMode)
		return;


	DWORD oldState;
	d3dDevice->CreateStateBlock(D3DSBT_ALL, &oldState);
	d3dDevice->CaptureStateBlock(oldState);


	///////////////////////////BEGIN SPRITE DRAWING/////////////////////////////////////////////////////////////////////
	spriteDrawer->Begin();

	spriteDrawer->Draw(logoSprite,  NULL,  NULL, NULL, 0 ,  &D3DXVECTOR2(float(xbot->currentViewport.Width-300), 0) , 0xFFFFFFFF);             
	spriteDrawer->Draw(credtisSprite,  NULL,  NULL, NULL, 0 ,  &D3DXVECTOR2(0, xbot->currentViewport.Height-100) , 0xFFFFFFFF);             

	
	spriteDrawer->End();
	///////////////////////////END SPRITE DRAWING/////////////////////////////////////////////////////////////////////
	// Restore old state
	d3dDevice->ApplyStateBlock(oldState);
	d3dDevice->DeleteStateBlock(oldState);
		
	
}

void XDrawer::setAlpha(char alpha, const char* args)
{
	unsigned char* ptr = 0;
	if(strcmp(args,"crosshair")==0)
		 ptr = (unsigned char*)&targetRadiusColor;

	else if(strcmp(args,"radar_font")==0)
		ptr = (unsigned char*)&radarTextColor;
	
	else if(strcmp(args,"radar_pix")==0)
		 ptr = (unsigned char*)&radarPixColor;

	if(alpha > 100)
		alpha = 100;
	if(ptr)
		ptr[3] = 255*(alpha/100.0);


}

