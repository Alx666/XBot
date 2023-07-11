#include "XConfig.h"

#define DIRECTINPUT_VERSION 0x0800
#include "dinput.h"

#include <iostream>



XConfig::XConfig()
{
	ZeroMemory(launchPath,1024);
	memset(playerlist, 0, sizeof(XPlayer)*MAX_PLAYERS);

	GetCurrentDirectory(1024,launchPath);
	
	char temp[1024];
	strcpy(temp,launchPath);
	cfgFile = strcat(temp,"\\XBot.ini");
	
	inireader = new CIniFile(cfgFile);


	if(!readSettings())
	{
		buildDefault();
	}

	pathToUT		   = (char*)(inireader->GetValue("Path", "Unreal2004Path")).data();
	exeParam		   = (char*)(inireader->GetValue("Path", "Parameters")).data();
	threadID		   = (DWORD)inireader->GetValueI("Path", "ThreadId");

	enableAim          = inireader->GetValueI("KeySettings", "enableAim");
	menuUp             = inireader->GetValueI("KeySettings", "menuUp");
	menuDown           = inireader->GetValueI("KeySettings", "menuDown");
	menuPlus           = inireader->GetValueI("KeySettings", "menuPlus");
	menuMinus          = inireader->GetValueI("KeySettings", "menuMinus");
	priFire			   = inireader->GetValueI("KeySettings", "priFire");
	altFire            = inireader->GetValueI("KeySettings", "altFire");
	jump			   = inireader->GetValueI("KeySettings", "jump");
	mouseSpeed		   = inireader->GetValueF("KeySettings" , "mouseSpeed");
	enableDodge		   = inireader->GetValueI("KeySettings", "enableDodge");
	enableHeadShot	   = inireader->GetValueI("KeySettings", "enableHeadShot");
	masterSwitch	   = inireader->GetValueI("KeySettings", "masterSwitch");
	resetCounterShield = inireader->GetValueI("KeySettings", "resetCounterShield");
	resetCounterDDamage= inireader->GetValueI("KeySettings", "resetCounterDDamage");
	resetCounterRedeem = inireader->GetValueI("KeySettings", "resetCounterRedeem");	
	autoSwap		   = inireader->GetValueI("KeySettings", "autoSwap");

	stealthMode				= inireader->GetValueI("XBotStatus", "stealthMode");
	autoAimEnabled			= inireader->GetValueI("XBotStatus", "autoAimEnabled");
	radarEnabled			= inireader->GetValueI("XBotStatus", "radarEnabled");
	imodeType  				= inireader->GetValueI("XBotStatus", "imodeType");
	headShotEnabled			= inireader->GetValueI("XBotStatus", "headShotEnabled");
	pingCompValue			= inireader->GetValueI("XBotStatus", "pingCompValue");
	dodgeEnabled			= inireader->GetValueI("XBotStatus", "dodgeEnabled");


	for(int i = 0; i < MAX_PLAYERS; i++)
	{
		playerlist[i].name = 0;//"";
		playerlist[i].codedIp = 0;

		const char *tmpStr = inireader->GetValueName("XAddr", i).c_str();

		if(*tmpStr != 0)
		{
			playerlist[i].name = new char[128];
			memset(playerlist[i].name, 0, sizeof(char[128]));
			strncpy(playerlist[i].name, tmpStr, sizeof(char[128]));

			playerlist[i].codedIp = (UINT)inireader->GetValueI("XAddr", playerlist[i].name);
		}
		else
			break;
	}

}

XConfig::~XConfig()
{
	delete inireader; 
	
	for(int i = 0; i<MAX_PLAYERS; i++)
	{
		if(playerlist[i].name != 0)
		{
			delete playerlist[i].name;
			playerlist[i].name = 0;
		}
	}
}

void XConfig::buildDefault()
{
	pathToUT			= "enter ut2004.exe path";
	exeParam			= "";
	GetCurrentDirectory(1024,launchPath);
	enableAim			= 0x45;
	enableHeadShot		= 0x48;
	autoSwap			= 0x46;
	menuUp				= VK_PRIOR;
	menuDown			= VK_NEXT;
	menuPlus			= VK_ADD ;
	menuMinus			= VK_SUBTRACT;
	priFire				= VK_LBUTTON;
	altFire				= VK_CONTROL;
	jump				= VK_RBUTTON;
	enableDodge		    = VK_SPACE;
	masterSwitch		= VK_NUMPAD0;
	resetCounterShield  = 0x5A;
	resetCounterDDamage = 0x58;
	resetCounterRedeem  = 0x43;
	mouseSpeed = 3.00f;


	//stato iniziale delle key e dei path
	inireader->SetValue("Path", "Unreal2004Path", pathToUT, true);
	inireader->SetValue("Path", "Parameters", exeParam, true);
	inireader->SetValue("Path", "Launcher", launchPath, true);
	inireader->SetValueI("KeySettings", "enableAim"          , enableAim);
	inireader->SetValueI("KeySettings", "menuUp"             , menuUp);
	inireader->SetValueI("KeySettings", "menuDown"           , menuDown);
	inireader->SetValueI("KeySettings", "menuPlus"           , menuPlus);
	inireader->SetValueI("KeySettings", "menuMinus"          , menuMinus);
	inireader->SetValueI("KeySettings", "priFire"            , priFire);
	inireader->SetValueI("KeySettings", "altFire"            , altFire);
	inireader->SetValueI("KeySettings", "jump"				 , jump);
	inireader->SetValueF("KeySettings", "mouseSpeed"		 , mouseSpeed);
	inireader->SetValueI("KeySettings", "enableDodge"		 , enableDodge);
	inireader->SetValueI("KeySettings", "enableHeadShot"	 , enableHeadShot);
	inireader->SetValueI("KeySettings", "masterSwitch"       , masterSwitch);
	inireader->SetValueI("KeySettings", "resetCounterShield" , resetCounterShield);
	inireader->SetValueI("KeySettings", "resetCounterDDamage", resetCounterDDamage);
	inireader->SetValueI("KeySettings", "resetCounterRedeem" , resetCounterRedeem);
	inireader->SetValueI("KeySettings", "autoSwap"			 , autoSwap);


	//stato iniziale delle features
	inireader->SetValueB("XBotStatus", "stealthMode"			, false);
	inireader->SetValueB("XBotStatus", "autoAimEnabled"			, false);
	inireader->SetValueB("XBotStatus", "radarEnabled"			, true);
	inireader->SetValueI("XBotStatus", "imodeType"				, 0);
	inireader->SetValueB("XBotStatus", "headShotEnabled"		, false);
	inireader->SetValueI("XBotStatus", "pingCompValue"			, 1);
	inireader->SetValueI("XBotStatus", "dodgeEnabled"			, 3);
}

void XConfig::writeSettings()
{
	inireader->SetValue("Path", "Unreal2004Path", pathToUT);
	inireader->SetValue("Path", "Parameters", exeParam);
	inireader->SetValue("Path", "Launcher", launchPath);
	inireader->SetValueI("Path", "ThreadId", (DWORD)threadID);

	inireader->SetValueF("KeySettings", "mouseSpeed"		 , mouseSpeed);
	inireader->SetValueI("KeySettings", "enableAim"          , enableAim);
	inireader->SetValueI("KeySettings", "menuUp"             , menuUp);
	inireader->SetValueI("KeySettings", "menuDown"           , menuDown);
	inireader->SetValueI("KeySettings", "menuPlus"           , menuPlus);
	inireader->SetValueI("KeySettings", "menuMinus"          , menuMinus);
	inireader->SetValueI("KeySettings", "priFire"            , priFire);
	inireader->SetValueI("KeySettings", "altFire"            , altFire);
	inireader->SetValueI("KeySettings", "jump"				 , jump);
	inireader->SetValueI("KeySettings", "enableDodge"		 , enableDodge);
	inireader->SetValueI("KeySettings", "enableHeadShot"	 , enableHeadShot);
	inireader->SetValueI("KeySettings", "masterSwitch"       , masterSwitch);
	inireader->SetValueI("KeySettings", "resetCounterShield" , resetCounterShield);
	inireader->SetValueI("KeySettings", "resetCounterDDamage", resetCounterDDamage);
	inireader->SetValueI("KeySettings", "resetCounterRedeem" , resetCounterRedeem);
	inireader->SetValueI("KeySettings", "autoSwap"			 , autoSwap);
	
	inireader->SetValueB("XBotStatus", "stealthMode"			, stealthMode);

	inireader->DeleteKey("XAddr");
	for(int i = 0; i<MAX_PLAYERS; i++)
	{
		if(playerlist[i].name != 0 )
			inireader->SetValueI("XAddr", playerlist[i].name, playerlist[i].codedIp);
		else
			break;
	}

	inireader->WriteFile();
}

//da introdurre
void XConfig::saveStatus(bool autoAim, bool radar, int imodeType, 
						 bool headshot, int pingComp, int dodge)
{
	
	inireader->Erase();
	readSettings();


	inireader->SetValueB("XBotStatus", "autoAimEnabled"			, autoAim);
	inireader->SetValueB("XBotStatus", "radarEnabled"			, radar);
	inireader->SetValueI("XBotStatus", "imodeType"				, imodeType);
	inireader->SetValueB("XBotStatus", "headShotEnabled"		, headshot);
	inireader->SetValueI("XBotStatus", "pingCompValue"			, pingComp);
	inireader->SetValueI("XBotStatus", "dodgeEnabled"			, dodge);

	inireader->WriteFile();
}


bool XConfig::readSettings()
{
	if(inireader->ReadFile())
		return true;
	else
		return false;
}









