#include "XBot.h"
#include <winable.h>

#ifdef TEST
	#include <stdio.h>
	extern FILE* logfile;
#endif

extern IDirect3DDevice8 *pD3DDevice8;


/////STATIC MEMBERS//////////////
XBot* XBot::xbot = new XBot();

XBot* XBot::getXBot()
{
	if(xbot!=NULL)
		return xbot;
	else
	{
		xbot = new XBot();
		return xbot;
	}
}



XBot::XBot()
{
	currentPlayer	= new UTarget(); //Player values
	Crc32Calculator = new CCrc32();	 //Texture reconization
	tPrimary		= new UTarget(); //Used to lock players
	tSecondary		= new UTarget(); //Used to lock shockCores
	xconfig			= new XConfig(); //Keyboard and settings managment
	aimAssistant	= new XAim();	 //to Humanize perfect mouse movements
	xffReader		= new CXFileFormat();
	d3dAnalyzer		= new XD3DAnalyzer();
	inputHandler	= new XInputHandler();

	Crc32Calculator->Init();
	
	texturesList.clear();
	radarListHostile.clear();
	radarListFriendly.clear();
	radarGranadeList.clear();
	radarWeaponList.clear();

	lastWeaponCrc			= 0;
	currentWeaponCrc		= 0;
	lastPlayerSkinDrawnFlag = 0;

	//FPS Calculator
	QueryPerformanceFrequency(&freq);
	frameTime   = 0;
	currentTime	= 0;
	lastTime	= 0;

	//XBot status flags
	stealthMode			=   xconfig->stealthMode;
	gameStarted			=	false;
	lastGameStarted		=	false;
	targetLocked		=	false;
	isAutoFiring		=	false;
	isAltFireDown		=   false;
	playerTeam			=   XMenu::COLOR_NONE;
	primFireDown		=	false;
	secFireDown			=	false;
	imodeType			=	xconfig->imodeType;		 //Se viene avviato con l'autofire attivo allora si sta usando questa modalita'
	


	//XBot features stats
	masterSwitch		=	true;
	radarSwitch			=	xconfig->radarEnabled;
	autoAimSwitch		=	xconfig->autoAimEnabled;
	headshotSwitch		=	xconfig->headShotEnabled;
	primFireModeSwitch	=	true;							 //TRUE = PRIMARY   FALSE = SECONDARY
	unlockStr			=	DEFAULT_UNLOCK_STR;
	pingCorrection		=	xconfig->pingCompValue;
	aimSpeed			=	DEFAULT_AIM_SPEED;
	crosshairRadius		=	DEFAULT_XHAIR_SIZE;
	wallHack			=   false;
	mouseSensibility	=   xconfig->mouseSpeed;

	if(xconfig->imodeType != IMODE_NONE)
		imodeSwitch		=	true;
	else 
		imodeSwitch		=   false;

	
	
	//Load keyboard and Mouse settings from the ini file
	xconfig->readSettings();
	launcherPath	= xconfig->launchPath;
	keyEnableAim	= xconfig->enableAim;
	keyMenuUp		= xconfig->menuUp;
	keyMenuDown		= xconfig->menuDown;
	keyMenuPlus		= xconfig->menuPlus;
	keyMenuMinus	= xconfig->menuMinus;
	keyPrimFire		= xconfig->priFire;
	keyAltFire		= xconfig->altFire;
	keyHeadShot		= xconfig->enableHeadShot;
	keyMasterSwitch	= xconfig->masterSwitch;
	keyWallHack		= xconfig->enableDodge;

	if(keyPrimFire == VK_LBUTTON)
		keyPrimFire = DIMOFS_BUTTON0;

	memset(&InputDown, 0, sizeof(INPUT));
	memset(&InputUp, 0, sizeof(INPUT));
	InputDown.type = INPUT_KEYBOARD;
	InputUp.type = INPUT_KEYBOARD;
	InputUp.ki.dwFlags = KEYEVENTF_KEYUP;


	menu = new XMenu(launcherPath, &currentViewport);	 //Xbot interface

	//Menu inizialization
	menu->setInxRef((UINT *)&autoAimSwitch,		0, XMenu::TYPE_BOOL);
	menu->setInxRef((UINT *)&radarSwitch,		1, XMenu::TYPE_BOOL);
	menu->setInxRef(&imodeType ,				2, XMenu::TYPE_CUSTOM, 2, 0);
	menu->setInxRef((UINT *)&headshotSwitch,	3, XMenu::TYPE_BOOL);
	menu->setInxRef(&crosshairRadius,			4, XMenu::TYPE_UINT, 250);
	menu->setInxRef(&pingCorrection,			5, XMenu::TYPE_UINT, 500, 1);
	menu->setInxRef((UINT *)&wallHack,			6, XMenu::TYPE_BOOL);
	menu->setInxRef(&playerTeam,				7, XMenu::TYPE_COLOR);


	//XFF routines
	char temp[1024];
	strcpy(temp,launcherPath);
	xffReader->Open(strcat(temp,"\\data.xff"));

}

XBot::~XBot()
{
}






void XBot::EndScene()
{

	SetPlayerWorldPosition();
	
	CurrentWeaponRoutines();

	Aim();

	EndSceneReset();
	
	DrawOnEndScene();

}



void XBot::BeginScene()
{
	SetFps();

	AutofireRoutine();
	
	BeginSceneReset();
}

void XBot::SetFps()
{
	LARGE_INTEGER count;

	QueryPerformanceCounter(&count); 
	
	currentTime=(float)((double)count.QuadPart/(double)freq.QuadPart);
	
	if(lastTime == 0)
		lastTime = currentTime;

	frameTime = currentTime - lastTime; 
	
	lastTime = currentTime;
}


void XBot::AutofireRoutine()
{
	if(imodeSwitch)
	{
		if(imodeType == IMODE_FIXER)
		{
			if(aimAssistant->lineOfFire && !isAutoFiring)
				startFire();
			else if(isAutoFiring && aimAssistant->lineOfFire && !primFireDown && !secFireDown)
			{
				stopFire();
				setAutoAim(false);
			}
			else if(isAutoFiring && !tPrimary->isValid && !primFireDown && !secFireDown && !tSecondary->isValid)
				stopFire();
		}
		else if(imodeType == IMODE_AUTO)
		{
			if(aimAssistant->lineOfFire && !isAutoFiring)
				startFire();
			else if(isAutoFiring && !tPrimary->isValid && !tSecondary->isValid)
				stopFire();
		}
	}

}

void XBot::EndSceneReset()
{
	if(!tSecondary->isValid && !tPrimary->isValid)
		aimAssistant->clear();

	if( !tPrimary->isInRange && !tPrimary->isValid && !tSecondary->isValid && imodeType==IMODE_FIXER)
		setAutoAim(false);

	if(tPrimary->isValid )
		targetLocked=true;

	lastGameStarted = gameStarted;	//CHECK FOR GAME START

}

void XBot::BeginSceneReset()
{
	gameStarted = false;
	
	if(!tPrimary->isValid)
		targetLocked=false;
	
	tPrimary->isValid = false;
	tPrimary->isInRange = false;

	tSecondary->isValid = false;
	tSecondary->isInRange = false;

	radarListHostile.clear();
	radarListFriendly.clear();
	radarGranadeList.clear();
	radarWeaponList.clear();

	lastPlayerSkinDrawnFlag = 0;

}




void XBot::CurrentWeaponRoutines()
{

	lastWeaponCrc = currentWeaponCrc;

	currentWeaponCrc = 0;
	//CURRENT WEAPON HANDLING
}



void XBot::Aim()
{
	if(!gameStarted)
		return;

	if(masterSwitch &&  tSecondary->isValid )
	{
		moveMouseX = (tSecondary->adjustedScreenCoords.x - (currentViewport.Width/2)) /	 mouseSensibility;
		moveMouseY = (tSecondary->adjustedScreenCoords.y - (currentViewport.Height/2)) / mouseSensibility;
		
		aimAssistant->process(&moveMouseX, &moveMouseY);

	}
	else if(masterSwitch && tPrimary->isValid)
	{
		moveMouseX = (tPrimary->adjustedScreenCoords.x - (currentViewport.Width/2)) / mouseSensibility;
		moveMouseY = (tPrimary->adjustedScreenCoords.y - (currentViewport.Height/2)) / mouseSensibility;

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

	currentPlayer->speed = 2;//PLAYER_SPEED;

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
	
	D3DXVECTOR3 ZeroVec(0,0,0);
	D3DXVECTOR3 screenSpace;

	D3DXVec3Project(&screenSpace, &ZeroVec, &currentViewport, &Projection, &View, &World);


	if((abs(screenSpace.x-(currentViewport.Width/2))<crosshairRadius && abs(screenSpace.y-(currentViewport.Height/2))<crosshairRadius))
	{	
	
		D3DXVECTOR3 myVec(0, 0, 0);
		D3DXVec3Transform(&tSecondary->currentWorldPosition, &myVec, (D3DXMATRIX*)matrix);

		D3DXVECTOR3 Vector(0, 0, 0);
		D3DXVec3Project(&tSecondary->screenCoords, &Vector, &currentViewport, &Projection, &View, &World);
		
		tSecondary->direction.x = tSecondary->currentWorldPosition.x - tSecondary->lastWorldPosition.x;
		tSecondary->direction.y = tSecondary->currentWorldPosition.y - tSecondary->lastWorldPosition.y;
		tSecondary->direction.z = tSecondary->currentWorldPosition.z - tSecondary->lastWorldPosition.z;
		
		D3DXVec3Normalize(&tSecondary->direction,&tSecondary->direction);

		tSecondary->lastWorldPosition = tSecondary->currentWorldPosition;

		tSecondary->aimAdjust.x = 0;
		tSecondary->aimAdjust.y = 0;
		tSecondary->aimAdjust.z = 0;

		aimAssistant->compensateMovement(tSecondary);
		
		D3DXVECTOR3 ZeroVec(0,0,0);
		D3DXMatrixIdentity(&World);
		
		D3DXMatrixTranslation(&World,(tSecondary->currentWorldPosition.x + tSecondary->aimAdjust.x),
									 (tSecondary->currentWorldPosition.y + tSecondary->aimAdjust.y),
									 (tSecondary->currentWorldPosition.z + tSecondary->aimAdjust.z));

		D3DXVec3Project(&tSecondary->adjustedScreenCoords, &ZeroVec, &currentViewport, &Projection, &View, &World);
		
		if(autoAimSwitch)
			tSecondary->isValid=true;
		else 
		{
			if(imodeSwitch && imodeType == IMODE_FIXER)
			{
				tSecondary->isInRange = true;	
				if(primFireDown /*|| secFireDown*/)
					setAutoAim(true);

			}
				
		}

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
	if(tPrimary->type==UTarget::TARGET_CHEST)
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
		if(fabs(tPrimary->direction.y) < 3.0f)// annulliamo i piccoli movimenti della Z per il bobbing
			tPrimary->direction.y = 0.0f;
		if(fabs(tPrimary->direction.x) < 3.0f)// annulliamo i piccoli movimenti della Z per il bobbing
			tPrimary->direction.x = 0.0f;

		D3DXVec3Normalize(&tPrimary->direction,&tPrimary->direction);

		tPrimary->speed = PLAYER_SPEED;
		
		tPrimary->lastWorldPosition = tPrimary->bodyVector;//currentWorldPosition;

		aimAssistant->addWeaponOffset(tPrimary);

		aimAssistant->compensateMovement(tPrimary);

		D3DXMatrixIdentity(&World);
		D3DXMatrixTranslation(&World,(tPrimary->bodyVector.x)+(tPrimary->aimAdjust.x),
									 (tPrimary->bodyVector.y)+(tPrimary->aimAdjust.y),
									 (tPrimary->bodyVector.z)+(tPrimary->aimAdjust.z));

		D3DXVec3Project(&tPrimary->adjustedScreenCoords, &ZeroVec, &currentViewport, &Projection, &View, &World);

		if(tPrimary->isValid || (imodeType == IMODE_FIXER && !autoAimSwitch))
			radarListHostile.push_back(*tPrimary);


		if(autoAimSwitch)
			tPrimary->isValid=true;
		else 
		{
			if(imodeSwitch && imodeType == IMODE_FIXER)
			{
				tPrimary->isInRange = true;	
				if(primFireDown /* || secFireDown*/)
					setAutoAim(true);

			}
				
		}
		
		return;
		
	}
	
	if(tPrimary->type==UTarget::TARGET_CHEST)
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







void XBot::setDevice(LPDIRECT3DDEVICE8 d3dDeviceRef)
{
	d3dDevice = d3dDeviceRef;
	menu->setDevice(d3dDevice);

	
	//Creazione dei Font e posizionamento

	LOGFONT LogFont2 = {14,0,0,0,FW_NORMAL,false,false,false,DEFAULT_CHARSET,OUT_TT_PRECIS,CLIP_DEFAULT_PRECIS,PROOF_QUALITY,DEFAULT_PITCH,"Arial"};
	D3DXCreateFontIndirect(pD3DDevice8,&LogFont2,&radarFont);	


	//Creazione dei Sprite
    D3DXCreateSprite(pD3DDevice8, &spriteDrawer);
	
	void* data;
	unsigned int fsize;
	
	fsize = xffReader->GetFile("XBot_logo","bmp",&data);
	D3DXCreateTextureFromFileInMemoryEx(pD3DDevice8,data,fsize	,256,256,		0, 0, D3DFMT_A8R8G8B8,	D3DPOOL_DEFAULT, D3DX_FILTER_LINEAR, D3DX_FILTER_LINEAR, 0xFF000000, NULL, NULL, &logoSprite);
	delete[] data;

	fsize = xffReader->GetFile("XBot_credits","bmp",&data);
	D3DXCreateTextureFromFileInMemoryEx(pD3DDevice8, data,fsize,1024,64,	0, 0, D3DFMT_UNKNOWN,	D3DPOOL_DEFAULT, D3DX_FILTER_LINEAR, D3DX_FILTER_LINEAR, 0xFF000000, NULL, NULL, &credtisSprite);	
	delete[] data;

	fsize = xffReader->GetFile("XBot_targetRadius","bmp",&data);
	D3DXCreateTextureFromFileInMemoryEx(pD3DDevice8, data,fsize,512,512,	0, 0, D3DFMT_UNKNOWN,	D3DPOOL_DEFAULT, D3DX_FILTER_LINEAR, D3DX_FILTER_LINEAR, 0xFF000000, NULL, NULL, &targetRadius);	
	delete[] data;

	fsize = xffReader->GetFile("XBot_radardPixCurrent","bmp",&data);
	D3DXCreateTextureFromFileInMemoryEx(pD3DDevice8, data,fsize	,64,64,		0, 0, D3DFMT_UNKNOWN,	D3DPOOL_DEFAULT, D3DX_FILTER_LINEAR, D3DX_FILTER_LINEAR, 0xFF000000, NULL, NULL, &radarPixCurrent);
	delete[] data;
	
	fsize = xffReader->GetFile("FOps_radardPixGranadeHE","bmp",&data);
	D3DXCreateTextureFromFileInMemoryEx(pD3DDevice8, data,fsize	,32,32,		0, 0, D3DFMT_UNKNOWN,	D3DPOOL_DEFAULT, D3DX_FILTER_LINEAR, D3DX_FILTER_LINEAR, 0xFF000000, NULL, NULL, &radarPixGranade[0]);
	delete[] data;
	
	fsize = xffReader->GetFile("FOps_radardPixGranadeFlash","bmp",&data);
	D3DXCreateTextureFromFileInMemoryEx(pD3DDevice8, data,fsize	,32,32,		0, 0, D3DFMT_UNKNOWN,	D3DPOOL_DEFAULT, D3DX_FILTER_LINEAR, D3DX_FILTER_LINEAR, 0xFF000000, NULL, NULL, &radarPixGranade[1]);
	delete[] data;
	
	fsize = xffReader->GetFile("FOps_radardPixGranadeNapalm","bmp",&data);
	D3DXCreateTextureFromFileInMemoryEx(pD3DDevice8, data,fsize	,32,32,		0, 0, D3DFMT_UNKNOWN,	D3DPOOL_DEFAULT, D3DX_FILTER_LINEAR, D3DX_FILTER_LINEAR, 0xFF000000, NULL, NULL, &radarPixGranade[2]);
	delete[] data;
	
	fsize = xffReader->GetFile("FOps_radardPixGranadeRSmoke","bmp",&data);
	D3DXCreateTextureFromFileInMemoryEx(pD3DDevice8, data,fsize	,32,32,		0, 0, D3DFMT_UNKNOWN,	D3DPOOL_DEFAULT, D3DX_FILTER_LINEAR, D3DX_FILTER_LINEAR, 0xFF000000, NULL, NULL, &radarPixGranade[3]);
	delete[] data;
	
	fsize = xffReader->GetFile("FOps_radardPixGranadeYSmoke","bmp",&data);
	D3DXCreateTextureFromFileInMemoryEx(pD3DDevice8, data,fsize	,32,32,		0, 0, D3DFMT_UNKNOWN,	D3DPOOL_DEFAULT, D3DX_FILTER_LINEAR, D3DX_FILTER_LINEAR, 0xFF000000, NULL, NULL, &radarPixGranade[4]);
	delete[] data;

	fsize = xffReader->GetFile("XBot_radardPixFriendly","bmp",&data);
	D3DXCreateTextureFromFileInMemoryEx(pD3DDevice8, data,fsize	,32,32,		0, 0, D3DFMT_UNKNOWN,	D3DPOOL_DEFAULT, D3DX_FILTER_LINEAR, D3DX_FILTER_LINEAR, 0xFF000000, NULL, NULL, &radarPixFriendly);
	delete[] data;
	
	fsize = xffReader->GetFile("XBot_radardPixHostile","bmp",&data);
	D3DXCreateTextureFromFileInMemoryEx(pD3DDevice8, data,fsize	,32,32,		0, 0, D3DFMT_UNKNOWN,	D3DPOOL_DEFAULT, D3DX_FILTER_LINEAR, D3DX_FILTER_LINEAR, 0xFF000000, NULL, NULL, &radarPixHostile);
	delete[] data;

	xffReader->Close();

	//Setup drawing state
	pD3DDevice8->BeginStateBlock();
	pD3DDevice8->SetTexture(0,NULL);
	pD3DDevice8->EndStateBlock(&AIMBOT_D3D_STATE);
}



void XBot::startFire()
{
	if(InputDown.ki.wVk == 0)
		return;

	if(isAutoFiring)
		return;

	isAutoFiring = true;
	SendInput(1, &InputDown, sizeof(INPUT));

}

void XBot::stopFire()
{
	if(InputDown.ki.wVk == 0)
		return;
	
	InputUp.ki.wVk = InputDown.ki.wVk;

	SendInput(1, &InputUp, sizeof(INPUT));

	isAutoFiring = false;
	//InputDown.ki.wVk = 0;
}

void XBot::setAutoFireMode(UINT type)
{
	setAutoAim(false);

	if(type)
	{
		imodeSwitch = true;
		imodeType  = type;
	}
	else
	{
		imodeSwitch = 0;
		imodeType   = IMODE_NONE;
	}
}


void XBot::setAutoAim(BOOL active)
{
	if(active)
	{
		autoAimSwitch = 1;
		aimAssistant->clear();
	}
	else
	{
		autoAimSwitch = 0;
		aimAssistant->clear();
	}
}

void XBot::swapAutoAimOnOff()
{
	if(!gameStarted || !masterSwitch )
		return;

	if(imodeType != IMODE_NONE)
	{
		imodeSwitch =! imodeSwitch;

		if(!imodeSwitch)
			setAutoAim(false);
	}
	else
	{
		autoAimSwitch  =! autoAimSwitch;
	}
}



