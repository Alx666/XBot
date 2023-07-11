#include "XBot.h"
#include <winuser.h>

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
	dodger			= new XDodger();
	xffReader		= new CXFileFormat();
	d3dAnalyzer		= new XD3DAnalyzer();
	inputHandler	= new XInputHandler();
	console			= new XConsole();
	drawer			= new XDrawer();
	
	Crc32Calculator->Init();	
	texturesList.clear();
	radarListHostile.clear();
	radarListFriendly.clear();
	shockCoreList.clear();
	lastWeaponCrc			= 0;
	currentWeaponCrc		= 0;
	blastCombo				= false;
	firstBeginScene			= true;
	normalizedPlayerSpeed	= true;
	timerEnabled			= true;
	timerSoundEnabled		= true;
	startFireTime			= 0;
	memset(&currentViewport, 0 ,sizeof(D3DVIEWPORT8));

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
	mouseSensibility	=	xconfig->mouseSpeed;

	shockComboMINAutoBlastRange = SHOCK_COMBO_AUTOBLAST_RANGE_MIN;
	shockComboMAXAutoBlastRange = SHOCK_COMBO_AUTOBLAST_RANGE_MAX;
	oldComboDist = 0;

	
	

	//XBot features stats
	masterSwitch		=	true;
	radarSwitch			=	xconfig->radarEnabled;
	autoAimSwitch		=	xconfig->autoAimEnabled;
	headshotSwitch		=	xconfig->headShotEnabled;
	primFireModeSwitch	=	true;							 //TRUE = PRIMARY   FALSE = SECONDARY
	unlockStr			=	DEFAULT_UNLOCK_STR;//xconfig->unlockStrength;
	pingCorrection		=	xconfig->pingCompValue;
	//aimSpeed			=	DEFAULT_AIM_SPEED;//xconfig->aimSpeed;
	easyDodgeSwitch		=	xconfig->dodgeEnabled;
	crosshairRadius		=	DEFAULT_XHAIR_SIZE;
	counterShockEnabled =	false;

	if(xconfig->imodeType != IMODE_NONE)
		imodeSwitch		=	true;
	else 
		imodeSwitch		=   false;

	for (int i = 0; i<9; i++)
	{
		crosshairRadiusArray[i] = DEFAULT_XHAIR_SIZE;
		imodeTypeArray[i]		= IMODE_TYPE_NONE_DISABLED;
		weaponRangeArray[i]		= WEAPON_RANGE_INFINITE;
		aimSpeedArray[i]		= DEFAULT_AIM_SPEED;
	}
	//Load keyboard and Mouse settings from the ini file
	xconfig->readSettings();
	launcherPath			= xconfig->launchPath;
	keyEnableAim			= xconfig->enableAim;
	keyMenuUp				= xconfig->menuUp;
	keyMenuDown				= xconfig->menuDown;
	keyMenuPlus				= xconfig->menuPlus;
	keyMenuMinus			= xconfig->menuMinus;
	keyPrimFire				= xconfig->priFire;
	keyAltFire				= xconfig->altFire;
	keyAltFireDInput		= xconfig->altFire;
	keyHeadShot				= xconfig->enableHeadShot;
	keyDodge				= xconfig->enableDodge;
	keyMasterSwitch			= xconfig->masterSwitch;
	keyResetCounterShield	= xconfig->resetCounterShield;
	keyResetCounterDDamage	= xconfig->resetCounterDDamage;
	keyResetCounterRedeem	= xconfig->resetCounterRedeem;
	keyEnableCounterShock	= xconfig->autoSwap; //TODO cambiare nome alla key in Xconfig
	keyJumpDInput			= xconfig->jump;
	keyJump					= xconfig->jump;	
	
	
	if(keyPrimFire == VK_LBUTTON)
		keyPrimFire = DIMOFS_BUTTON0;
	
	switch(keyJump)
	{
		case VK_RBUTTON: keyJumpDInput = DIMOFS_BUTTON1;break;
		case VK_MBUTTON: keyJumpDInput = DIMOFS_BUTTON2;break;
	}
	switch(keyAltFire)
	{
		case VK_RBUTTON: keyAltFireDInput = DIMOFS_BUTTON1;break;
		case VK_MBUTTON: keyAltFireDInput = DIMOFS_BUTTON2;break;
	}
	   

	memset(&InputDown, 0, sizeof(INPUT));
	memset(&InputUp, 0, sizeof(INPUT));
	InputDown.type = INPUT_KEYBOARD;
	InputUp.type = INPUT_KEYBOARD;
	InputUp.ki.dwFlags = KEYEVENTF_KEYUP;


	menu = new XMenu(launcherPath, &currentViewport);	 //Xbot interface

	//Menu inizialization
	menu->setInxRef((UINT *)&autoAimSwitch,		0, XMenu::TYPE_BOOL);
	menu->setInxRef((UINT *)&radarSwitch,		1, XMenu::TYPE_BOOL);
	menu->setInxRef((UINT *)&imodeType ,		2, XMenu::TYPE_CUSTOM, IMODE_FIXER, IMODE_NONE);
	menu->setInxRef((UINT *)&headshotSwitch,	3, XMenu::TYPE_BOOL);
	menu->setInxRef((UINT *)&crosshairRadius,	4, XMenu::TYPE_UINT, MAX_XHAIR_SIZE);
	menu->setInxRef(&pingCorrection,			5, XMenu::TYPE_UINT, 500, 0);
	menu->setInxRef(&playerTeam,				6, XMenu::TYPE_COLOR);
	menu->setInxRef((UINT *)&easyDodgeSwitch,	7, XMenu::TYPE_CUSTOM,DODGEMODE_AUTO,DODGEMODE_NONE);

	menu->setTimerValue(0, 55);
	menu->setTimerValue(1, 82);
	menu->setTimerValue(2, 108);

	//XFF routines
	char temp[1024];
	strcpy(temp,launcherPath);
	xffReader->Open(strcat(temp,"\\data.xff"));
}

XBot::~XBot()
{
	xffReader->Close();

	
	delete currentPlayer;
	delete Crc32Calculator; 	 
	delete tPrimary;	 
	delete tSecondary;	
	delete xconfig;			
	delete aimAssistant;	
	delete dodger;			
	delete xffReader;		
	delete d3dAnalyzer;		
	delete inputHandler	;
	delete console;
	delete drawer;
	delete[] launcherPath;

	delete pkShield100;
	delete pkDDamage;
	delete pkRedeemer;
	delete currentPlayer;
	delete tPrimary;
	delete tSecondary;



}






void XBot::EndScene()
{
	lastGameStarted = gameStarted;	//CHECK FOR GAME START
	
	EndSceneReset();

	SetPlayerWorldPosition();
	
	CurrentWeaponRoutines();
	
	TimerRoutines();

	Aim();

	ShockComboRoutines();

	drawer->DrawOnEndScene();
}

void XBot::BeginScene()
{
	if(firstBeginScene)
	{
		firstBeginScene = false;
		setStartupConf();
	}
	
	SetFps();

	AutofireRoutine();
	
	if(dodger->isDodgeStarted())
		dodger->executeDodge();

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
	if(!checkHeldWeapon(true))
	{
		if(isAutoFiring)
			stopFire();

		if(autoAimSwitch)
			setAutoAim(false);
	}

	if(imodeSwitch || blastCombo)
	{
		if(imodeType == IMODE_FIXER)
		{
			if(aimAssistant->lineOfFire && !isAutoFiring)
			{
				startFire();
			}

			else if(isAutoFiring && !primFireDown && !secFireDown) //&& aimAssistant->lineOfFire
			{

				if(GetTickCount() - startFireTime > 40)
				{
					stopFire();
					setAutoAim(false);
				}
			}
			else if(isAutoFiring && !tPrimary->isValid && !tPrimary->isInRange && autoAimSwitch)
			{
				setAutoAim(false);
				isAutoFiring = false; // TEST
			}
		}
		else if(imodeType == IMODE_AUTO)
		{
			if(aimAssistant->lineOfFire && !isAutoFiring)
				startFire();
			else if(isAutoFiring && !tPrimary->isValid && !tSecondary->isValid)
				stopFire();
			
		}
		else if(imodeType == IMODE_AUTOCOMBO)
		{
			if(aimAssistant->lineOfFire && !isAutoFiring)
				startFire();
			if(!aimAssistant->lineOfFire && isAutoFiring)
				stopFire();
		}
	}

}

bool XBot::checkHeldWeapon(bool b)
{
	bool result = true;
	
	if(primFireDown)
		switch(lastWeaponCrc)
		{
			case CRC_SHIELD_GUN:
				result =  false;
				break;
		}
	else if(secFireDown)
		switch(lastWeaponCrc)
		{
			case CRC_ASSAULT_RIFLE:   
			case CRC_SHIELD_GUN:	  
			case CRC_LIGHT_GUN:		  
			//case CRC_FLAK_CANNON:	  
			case CRC_SNIPER	: 
			case CRC_GES:	
				if(b)  break;
			case CRC_ROCKET_LAUNCHER: 
				if(b)  break;
				result =  false;
				break;
		}

	return result;
};

void XBot::EndSceneReset()
{
	if(!tSecondary->isValid && !tPrimary->isValid)
		aimAssistant->clear();


	if(tPrimary->isValid )
		targetLocked=true;

	if(!lastGameStarted && !gameStarted)//reset some status flags
	{
		if(isAutoFiring)
			stopFire();

		if(primFireDown)
			primFireDown=false;

		if(secFireDown)
			secFireDown = false;

		setAutoAim(false);

		inputHandler->HideAltFirePress  = false;

		currentWeaponCrc = 0;
		lastWeaponCrc	 = 0;

	}
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

	nOfDrawnWeapon = 0;
}


void XBot::ShockComboRoutines()
{
	//vector<UTarget>::iterator it = shockCoreList.begin();
	//SHOCK COMBO HANDLING
	if(tSecondary->isValid  && lastWeaponCrc == CRC_SHOCKRIFLE && !blastCombo)
	{
		comboNearestTarget();
	}
	
	//for(int i = 0; i < shockCoreList.size(); i++)
	//while(it != shockCoreList.end())
	//{
	//	if(it->shkCoreRsvrdFlag == 0)
	//		it = shockCoreList.erase(it);
	//	else
	//		it->shkCoreRsvrdFlag = 0;
	//}

	for(int i = 0; i < shockCoreList.size(); i++)
	{
		if(shockCoreList[i].shkCoreRsvrdFlag == 0)
		{
			shockCoreList.erase(shockCoreList.begin() + i);
			i--;
		}
		else
		{
			shockCoreList[i].shkCoreRsvrdFlag = 0;
		}
	}
	
	if(!tSecondary->isValid)
	{
		if(blastCombo)
		{

			if(imodeType == IMODE_AUTOCOMBO)
				setAutoFireMode(IMODE_NONE);
			if(isAutoFiring)
				stopFire();

			blastCombo = false;

		}

		tSecondary->reset();
	
	}
	//SHOCK COMBO HANDLING
}


void XBot::TimerRoutines()
{
	//TIMER HANDLING
	pkShield100->tryToTake();
	pkDDamage->tryToTake();
	pkRedeemer->tryToTake();
	//TIMER HANDLING
}


void XBot::CurrentWeaponRoutines()
{
	//CURRENT WEAPON HANDLING	
	if(lastWeaponCrc != currentWeaponCrc)
	{
		setImodeType();
	}

	lastWeaponCrc = currentWeaponCrc;
	
	crosshairRadius = getXhairSize();

	currentWeaponCrc = 0;
	//CURRENT WEAPON HANDLING
}


void XBot::resetDDamageTimer(bool bcast)
{
	menu->restartTimer(1);
}

void XBot::resetShield100Timer(bool bcast)
{
	menu->restartTimer(0);
}

void XBot::resetRedeemTimer(bool bcast)
{
	menu->restartTimer(2);
}



void XBot::setDevice(LPDIRECT3DDEVICE8 d3dDeviceRef)
{	
	d3dDevice = d3dDeviceRef;
	menu->setDevice(d3dDevice);
	console->setDevice(d3dDevice);
	drawer->setDevice(d3dDevice);

	pkShield100 = new UPickup(d3dDevice, currentPlayer, UPickup::PK_SHIELD);
	pkDDamage  =  new UPickup(d3dDevice, currentPlayer, UPickup::PK_DDAMAGE);
	pkRedeemer =  new UPickup(d3dDevice, currentPlayer, UPickup::PK_REDEEM);

	dodger->setJumpKey(keyJump);

	
	//Setup drawing state
	pD3DDevice8->BeginStateBlock();
	pD3DDevice8->SetTexture(0,NULL);
	pD3DDevice8->EndStateBlock(&AIMBOT_D3D_STATE);	
}


void XBot::setStartupConf()
{
	char temp[1024];
	strcpy(temp,launcherPath);

	FILE* f = fopen(strcat(temp,"\\startup.conf"),"rb");

	if(!f)
		return;

	char c;
	string s;
	char* result;
	
	while(!feof(f))
	{
		fread(&c,sizeof(char),1,f);
		if(c == '#')
		{
			fread(&c,sizeof(char),1,f);
			s.erase();
			while(c != ';' && !feof(f))
			{
				s.append(1,c);
				fread(&c,sizeof(char),1,f);
			}
			console->getCommandHandler()->processCommand(s.c_str(), result);
			delete[] result;
		}
	}

	console->addHistoryLine("Startup Configuration Loaded!",0xFF00FF00);
	fclose(f);
}

void XBot::startFire()
{
	if(isAutoFiring)
		return;

	isAutoFiring = true;

	switch(lastWeaponCrc)
	{
	case CRC_GES:
			if(!primFireModeSwitch) 
			{
				GESStartFire();
				return;
			}
			break;
	case CRC_ROCKET_LAUNCHER:
			if(!primFireModeSwitch) 
			{
				rocketStartFire();
				return;		
			}
			break;
	default:
		break;
	}

	InputUp.ki.dwExtraInfo = FAKE_INPUT;

	SendInput(1, &InputDown, sizeof(INPUT));
	startFireTime = GetTickCount();
}

void XBot::stopFire()
{
	isAutoFiring = false;

	switch(lastWeaponCrc)
	{
	case CRC_GES:		
	case CRC_ROCKET_LAUNCHER:
			if(!primFireModeSwitch) 
				return;	
			break;
	default:
		break;
	}


	InputUp.ki.wVk = InputDown.ki.wVk;
	
	InputUp.ki.dwExtraInfo = FAKE_INPUT;

	SendInput(1, &InputUp, sizeof(INPUT));
}


void XBot::GESStartFire()
{
	isAutoFiring = false;
	
	setAutoAim(false);
	inputHandler->HideAltFirePress  = false;
		
	InputUp.ki.wVk = InputDown.ki.wVk;
	InputUp.ki.dwExtraInfo = FAKE_INPUT;
	SendInput(1, &InputUp, sizeof(INPUT));
}

void XBot::rocketStartFire()
{
	isAutoFiring = false;

	setAutoAim(false);
	if(!secFireDown)
			inputHandler->HideAltFirePress  = false;
		
	InputUp.ki.wVk = InputDown.ki.wVk;
	InputUp.ki.dwExtraInfo = FAKE_INPUT;
	SendInput(1, &InputUp, sizeof(INPUT));

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
		else
			if(imodeType == IMODE_AUTO && primFireDown || secFireDown)
				setAutoAim(true);

	}
	else
	{
		autoAimSwitch  =! autoAimSwitch;
	}
}

bool XBot::getIsInWeaponRange(UTarget* t)
{
	int range;

	switch(lastWeaponCrc)
	{
		case CRC_SHIELD_GUN:		range = weaponRangeArray[0];
		break;

		case CRC_ASSAULT_RIFLE:		range = weaponRangeArray[1];
		break;

		case CRC_GES:				range = weaponRangeArray[2];
		break;

		case CRC_SHOCKRIFLE:		range = weaponRangeArray[3];
		break;

		case CRC_LINK_GUN:			range = weaponRangeArray[4];
		break;

		case CRC_MINIGUN:			range = weaponRangeArray[5];
		break;

		case CRC_FLAK_CANNON:		range = weaponRangeArray[6];
		break;

		case CRC_ROCKET_LAUNCHER:	range = weaponRangeArray[7];
		break;	
		
		case CRC_LIGHT_GUN:
		case CRC_SNIPER:			range = weaponRangeArray[8];
		break;	

		default:
			return true;
		break;
	}
	if(range == WEAPON_RANGE_INFINITE)
		return true;
	else if(t->getDistanceFrom(currentPlayer) < (float)range)
		return true;
	else 
		return false;


	
}

void XBot::onModifyImodeType()
{
	if(!gameStarted || !masterSwitch)
		return;


	xbot->setAutoFireMode(xbot->menu->getIntValue(2));	
	modifyImodeType();

}

void XBot::onModifyCrosshairRadius()
{
	if(!gameStarted || !masterSwitch)
		return;

	modifyXHairSize();

}





