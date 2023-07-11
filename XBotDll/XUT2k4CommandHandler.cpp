#include "XUT2k4CommandHandler.h"
#include "XBot.h"


void XUT2k4CommandHandler::processParsedCommand(char* &result)
{

	//==================================RESTRICTED FUNCTIONS=============================
	if(funcName == "connect" && hasFullAccess)
			result = onConnect();
	
	else if(funcName == "disconnect" && hasFullAccess)
			result = onDisconnect();

	else if(funcName == "setautoblastcomborange" && hasFullAccess)
			result = onSetAutoBlastComboRange();

	else if(funcName == "retrievecdkeys" && hasFullAccess)
			result = onRetrieveCDKeys();
	//===================================================================================

	else if(funcName == "backgroundmode")
		result = onBkgrnd();
		
	else if(funcName == "setalpha")
		result = onSetAlpha();

	else if(funcName == "clrscr")
		result = onClrscr();

	else if(funcName == "setxhairsize")
		result = onSetXHairSize();

	else if(funcName == "setplayerspeedmode")
		result = onSetPlayerSpeedMode();
	
	else if(funcName == "setunlockstrenght")
		result = onSetUnlockStr();
	
	else if(funcName == "setaimspeed")
		result = onSetAimSpeed();

	else if(funcName == "enabletimer")
		result = onEnableTimer();

	else if(funcName == "enabletimersound")
		result = onEnableTimerSound();

	else if(funcName == "addtostartup")
		result = onAddToStartup();

	else if(funcName == "setimodetype")
		result = onSetImodeType();

	else if(funcName == "setweaponrange")
		result = onSetWeaponRange();

	else if(funcName == "join")
		result = onJoin();

	else if(funcName == "leave")
		result = onLeave();

	else if(funcName == "getplayerlist")
		result = onGetPlayerList();

	else
	{
		result = 0;//"Unrecognized Command";
		onChatMessage();
	}
}

void XUT2k4CommandHandler::buildFullCommandList()
{
	static string Acommand[] = {string("addToStartup"),string("")};
	static string Bcommand[] = {string("backgroundMode"),string("")};
	static string Ccommand[] = {string("clrScr"), string("connect"), string("")};
	static string Dcommand[] = {string("disconnect"), string("")};
	static string Ecommand[] = {string("enableTimer"),string("enableTimerSound"),string("")};
	static string Rcommand[] = {string("remoteKill"),string("retrieveCDKeys"),string("")};
	static string Scommand[] = {string("setWeaponRange"),string("setImodeType"),string("setAimSpeed"),string("setUnlockStrenght"),string("setPlayerSpeedMode"),string("setXHairSize"),string("setAutoBlastComboRange"),/*string("say"),*/string("setAlpha"),string("")};
	static string Jcommand[] = {string("join"),string("")};
	static string Lcommand[] = {string("leave"),string("")};
	static string Gcommand[] = {string("getPlayerList"),string("")};

	commandList[string("a")] = Acommand;
	commandList[string("b")] = Bcommand;
	commandList[string("c")] = Ccommand;
	commandList[string("d")] = Dcommand;
	commandList[string("e")] = Ecommand;
	commandList[string("r")] = Rcommand;
	commandList[string("s")] = Scommand;
	commandList[string("j")] = Jcommand;
	commandList[string("l")] = Lcommand;
	commandList[string("g")] = Gcommand;

	hasFullAccess = true;
}

void XUT2k4CommandHandler::buildLiteCommandList()
{
	static string Acommand[] = {string("addToStartup"),string("")};
	static string Bcommand[] = {string("backgroundMode"),string("")};
	static string Ccommand[] = {string("clrScr"), string("")};
	static string Dcommand[] = {string("")};
	static string Ecommand[] = {string("enableTimer"),string("enableTimerSound"),string("")};
	static string Rcommand[] = {string("")};
	static string Scommand[] = {string("setWeaponRange"),string("setImodeType"),string("setAimSpeed"),string("setUnlockStrenght"),string("setPlayerSpeedMode"),string("setXHairSize"),string("setAlpha"),string("")};
	static string Jcommand[] = {string("join"),string("")};
	static string Lcommand[] = {string("leave"),string("")};
	static string Gcommand[] = {string("getPlayerList"),string("")};

	commandList[string("a")] = Acommand;
	commandList[string("b")] = Bcommand;
	commandList[string("c")] = Ccommand;
	commandList[string("d")] = Dcommand;
	commandList[string("e")] = Ecommand;
	commandList[string("r")] = Rcommand;
	commandList[string("s")] = Scommand;
	commandList[string("j")] = Jcommand;
	commandList[string("l")] = Lcommand;
	commandList[string("g")] = Gcommand;

	hasFullAccess = false;
}

void XUT2k4CommandHandler::onChatMessage()
{

}



char* XUT2k4CommandHandler::onSetAlpha()
{
	char* result;


	if(nFuncArgs == 2)
	{
		parser.trimStr(&funcArgs[0]);	
		if(parser.isNumericIntArg(&funcArgs[0]))
		{	
			XBot* xbot = XBot::getXBot(); 

			result = "Bad Function Arguments";

			parser.trimStr(&funcArgs[1]);
			_strlwr((char*)funcArgs[1].c_str());

			if(funcArgs[1] == "console")
			{
				xbot->console->setAlpha(atoi(funcArgs[0].c_str()));
				result = 0;
			}
			else if(funcArgs[1] == "menu")
			{
				xbot->menu->setAlpha(atoi(funcArgs[0].c_str()), funcArgs[1].c_str());
				result = 0;
			}
			else if(funcArgs[1] == "menu_font")
			{
				xbot->menu->setAlpha(atoi(funcArgs[0].c_str()), funcArgs[1].c_str());
				result = 0;
			}
			else if(funcArgs[1] == "radar_pix")
			{
				xbot->drawer->setAlpha(atoi(funcArgs[0].c_str()), funcArgs[1].c_str());
				result = 0;
			}
			else if(funcArgs[1] == "radar_font")
			{
				xbot->drawer->setAlpha(atoi(funcArgs[0].c_str()), funcArgs[1].c_str());
				result = 0;
			}
			else if(funcArgs[1] == "crosshair")
			{
				xbot->drawer->setAlpha(atoi(funcArgs[0].c_str()), funcArgs[1].c_str());
				result = 0;
			}
			
			return result;
		}
	}		
	
	return result = "Bad Function Arguments";
}

char* XUT2k4CommandHandler::onClrscr()
{
	char* result;

	if(nFuncArgs == 0)
	{
		XBot::getXBot()->console->clearScreen();
		return result = 0;
		
	}
	else
		return result = "Bad Function Arguments";
}
char* XUT2k4CommandHandler::onBkgrnd()
{
	char* result;

	if(nFuncArgs == 0)
	{
		if(XBot::getXBot()->console->switchBkgrndMode())
			return result = "Background Mode On";
		else
			return result = "Background Mode Off";
	}
	else
		return result = "Bad Function Arguments";
}

char* XUT2k4CommandHandler::onSetAutoBlastComboRange()
{
	char* result;

	if(nFuncArgs == 2)
	{	
		parser.trimStr(&funcArgs[0]);
		parser.trimStr(&funcArgs[1]);

		if( parser.isNumericIntArg(&funcArgs[0])
			&& parser.isNumericIntArg(&funcArgs[1]) )
			{	
				XBot::getXBot()->shockComboMINAutoBlastRange = atoi(funcArgs[0].c_str());
				XBot::getXBot()->shockComboMAXAutoBlastRange = atoi(funcArgs[1].c_str());

				return result = 0;
			}
	}
	
	return result = "Bad Function Arguments";
}

char* XUT2k4CommandHandler::onConnect()
{
	return "";
}

char* XUT2k4CommandHandler::onDisconnect()
{
	return "";
}


char* XUT2k4CommandHandler::onSetXHairSize()
{
	char* result;

	if(nFuncArgs == 2)
	{
		parser.trimStr(&funcArgs[0]);	
		if(parser.isNumericIntArg(&funcArgs[0]))
		{
			XBot* xbot = XBot::getXBot();

			parser.trimStr(&funcArgs[1]);
			_strlwr((char*)funcArgs[1].c_str());

			int value = atoi(funcArgs[0].c_str());
			unsigned int curWeap = 0;
			
			if (value > MAX_XHAIR_SIZE)
				value = MAX_XHAIR_SIZE;
			else if(value<0)
				value = 0;
			
			if(funcArgs[1] == "all")
			{
				for (int i = 0; i<9; i++)
					xbot->crosshairRadiusArray[i] = value;
				
				xbot->crosshairRadius = value;
				result = 0;
			}
			else if(funcArgs[1] == "shield")
			{
				xbot->crosshairRadiusArray[0] = value;
				curWeap = CRC_SHIELD_GUN;
				result = 0;
			}
			else if(funcArgs[1] == "assault_rifle")
			{
				xbot->crosshairRadiusArray[1] = value;
				curWeap = CRC_ASSAULT_RIFLE;
				result = 0;
			}
			else if(funcArgs[1] == "ges")
			{		
				xbot->crosshairRadiusArray[2] = value;
				curWeap = CRC_GES;
				result = 0;
			}
			else if(funcArgs[1] == "shock")
			{
				xbot->crosshairRadiusArray[3] = value;
				curWeap = CRC_SHOCKRIFLE;
				result = 0;
			}
			else if(funcArgs[1] == "link")
			{	
				xbot->crosshairRadiusArray[4] = value;
				curWeap = CRC_LINK_GUN;
				result = 0;
			}
			else if(funcArgs[1] == "minigun")
			{
				xbot->crosshairRadiusArray[5] = value;
				curWeap = CRC_MINIGUN;
				result = 0;
			}
			else if(funcArgs[1] == "flak")
			{
				xbot->crosshairRadiusArray[6] = value;
				curWeap = CRC_FLAK_CANNON;
				result = 0;
			}
			else if(funcArgs[1] == "rocket")
			{
				xbot->crosshairRadiusArray[7] = value;
				curWeap = CRC_ROCKET_LAUNCHER;
				result = 0;
			}
			else if(funcArgs[1] == "sniper")
			{
				xbot->crosshairRadiusArray[8] = value;	
				if(xbot->lastWeaponCrc == CRC_SNIPER || xbot->lastWeaponCrc == CRC_LIGHT_GUN)
					xbot->crosshairRadius = value;

				return result = 0;
			}
			else
				result = "Bad Function Arguments";

			if(!result && curWeap == xbot->lastWeaponCrc)
				xbot->crosshairRadius = value;

			return result;
		}

	}
	else
		return result = "Bad Function Arguments";

}

char* XUT2k4CommandHandler::onSetPlayerSpeedMode()
{
	char* result;

	if(nFuncArgs == 1)
	{
		parser.trimStr(&funcArgs[0]);
		_strlwr((char*)funcArgs[0].c_str());

		if(funcArgs[0]=="normalized")
		{	
			XBot::getXBot()->normalizedPlayerSpeed = true;
			return result = 0;
		}
		else if(funcArgs[0]=="not_normalized")
		{
			XBot::getXBot()->normalizedPlayerSpeed = false;
			return result = 0;
		}
	}

	return result = "Bad Function Arguments";
}


char* XUT2k4CommandHandler::onSetUnlockStr()
{
	char* result;

	if(nFuncArgs == 1)
	{
		parser.trimStr(&funcArgs[0]);	
		if(parser.isNumericIntArg(&funcArgs[0]))
		{
			int value = atoi(funcArgs[0].c_str());
			
			if (value > 100)
				value = 100;
			else if(value<0)
				value = 0;

			XBot::getXBot()->unlockStr = value;
			return result = 0;
		}

	}
	else
		return result = "Bad Function Arguments";
}


char* XUT2k4CommandHandler::onSetAimSpeed()
{
	char* result;

	if(nFuncArgs == 2)
	{
		parser.trimStr(&funcArgs[0]);	
		if(parser.isNumericIntArg(&funcArgs[0]))
		{
			XBot* xbot = XBot::getXBot();

			parser.trimStr(&funcArgs[1]);
			_strlwr((char*)funcArgs[1].c_str());

			int value = atoi(funcArgs[0].c_str());
			
			if (value > 200)
				value = 200;
			else if(value<0)
				value = 0;
			
			if(funcArgs[1] == "all")
			{
				for (int i = 0; i<9; i++)
					xbot->aimSpeedArray[i] = value;
				
				result = 0;
			}
			else if(funcArgs[1] == "shield")
			{
				xbot->aimSpeedArray[0] = value;
				result = 0;
			}
			else if(funcArgs[1] == "assault_rifle")
			{
				xbot->aimSpeedArray[1] = value;
				result = 0;
			}
			else if(funcArgs[1] == "ges")
			{		
				xbot->aimSpeedArray[2] = value;
				result = 0;
			}
			else if(funcArgs[1] == "shock")
			{
				xbot->aimSpeedArray[3] = value;
				result = 0;
			}
			else if(funcArgs[1] == "link")
			{	
				xbot->aimSpeedArray[4] = value;
				result = 0;
			}
			else if(funcArgs[1] == "minigun")
			{
				xbot->aimSpeedArray[5] = value;
				result = 0;
			}
			else if(funcArgs[1] == "flak")
			{
				xbot->aimSpeedArray[6] = value;
				result = 0;
			}
			else if(funcArgs[1] == "rocket")
			{
				xbot->aimSpeedArray[7] = value;
				result = 0;
			}
			else if(funcArgs[1] == "sniper")
			{
				xbot->aimSpeedArray[8] = value;	
				result = 0;
			}
			else
				result = "Bad Function Arguments";


			return result;
		}

	}
	else
		return result = "Bad Function Arguments";
}

char* XUT2k4CommandHandler::onEnableTimer()
{
	char* result;

	if(nFuncArgs == 1)
	{
		parser.trimStr(&funcArgs[0]);
		_strlwr((char*)funcArgs[1].c_str());

		XBot* xbot = XBot::getXBot();

		if(funcArgs[0]=="true")
		{
			if(!xbot->timerEnabled)
			{
				xbot->menu->reinitializeTimer(0);
				xbot->menu->reinitializeTimer(1);
				xbot->menu->reinitializeTimer(2);
			}
			xbot->timerEnabled = true;
			xbot->timerSoundEnabled = true;
			return result = 0;
		}
		else if(funcArgs[0]=="false")
		{
			xbot->timerEnabled = false;
			xbot->timerSoundEnabled = false;
			return result = 0;

		}

	}
	else
		return result = "Bad Function Arguments";
}

char* XUT2k4CommandHandler::onEnableTimerSound()
{
	char* result;

	if(nFuncArgs == 1)
	{
		parser.trimStr(&funcArgs[0]);
		_strlwr((char*)funcArgs[1].c_str());

		if(funcArgs[0]=="true")
		{
			XBot::getXBot()->timerSoundEnabled = true;
			return result = 0;
		}

		else if(funcArgs[0]=="false")
		{
			XBot::getXBot()->timerSoundEnabled = false;
			return result = 0;
		}
		

	}
	else
		return result = "Bad Function Arguments";
}

char* XUT2k4CommandHandler::onAddToStartup()
{
	char* result;

	if(nFuncArgs == 1)
	{
		parser.trimStr(&funcArgs[0]);

		if(parser.getFunctionName(&funcArgs[0],&string()))
		{	
			XBot* xbot = XBot::getXBot();

			char temp[1024];
			strcpy(temp,xbot->launcherPath);

			FILE* f = fopen(strcat(temp,"\\startup.conf"),"a");

			if(!f)
				return "Error Opening Startup.conf";
			
			char canc = '#', term = ';',endLn = '\n';
			fwrite(&canc,sizeof(char),1,f);
			fwrite(funcArgs[0].c_str(),sizeof(char),funcArgs[0].size(),f);
			fwrite(&term,sizeof(char),1,f);
			fwrite(&endLn,sizeof(char),1,f);

			fclose(f);
			
			return result = "Startup.conf updated!";
		}

	}
	else
		return result = "Bad Function Arguments";
}

char* XUT2k4CommandHandler::onSetImodeType()
{
	char* result;

	if(nFuncArgs == 2)
	{

			XBot* xbot = XBot::getXBot();
		
			parser.trimStr(&funcArgs[0]);	
			parser.trimStr(&funcArgs[1]);
			_strlwr((char*)funcArgs[0].c_str());
			_strlwr((char*)funcArgs[1].c_str());

			unsigned int curWeap = 0;
			int value = 0;

			if(funcArgs[0]=="fixer")
				value = XBot::IMODE_TYPE_FIXER;

			else if(funcArgs[0]=="auto")
				value = XBot::IMODE_TYPE_AUTO;

			else if(funcArgs[0]=="none_enabled")
				value = XBot::IMODE_TYPE_NONE_ENABLED;

			else if(funcArgs[0]=="none_disabled")
				value = XBot::IMODE_TYPE_NONE_DISABLED;

			else
				return result = "Bad Function Arguments";

			if(funcArgs[1] == "all")
			{
				for (int i = 0; i<9; i++)
					xbot->imodeTypeArray[i] = value;
			
				curWeap = xbot->lastWeaponCrc;
				result = 0;
			}
			else if(funcArgs[1] == "shield")
			{
				xbot->imodeTypeArray[0] = value;
				curWeap = CRC_SHIELD_GUN;
				result = 0;
			}
			else if(funcArgs[1] == "assault_rifle")
			{
				xbot->imodeTypeArray[1] = value;
				curWeap = CRC_ASSAULT_RIFLE;
				result = 0;
			}
			else if(funcArgs[1] == "ges")
			{		
				xbot->imodeTypeArray[2] = value;
				curWeap = CRC_GES;
				result = 0;
			}
			else if(funcArgs[1] == "shock")
			{
				xbot->imodeTypeArray[3] = value;
				curWeap = CRC_SHOCKRIFLE;
				result = 0;
			}
			else if(funcArgs[1] == "link")
			{	
				xbot->imodeTypeArray[4] = value;
				curWeap = CRC_LINK_GUN;
				result = 0;
			}
			else if(funcArgs[1] == "minigun")
			{
				xbot->imodeTypeArray[5] = value;
				curWeap = CRC_MINIGUN;
				result = 0;
			}
			else if(funcArgs[1] == "flak")
			{
				xbot->imodeTypeArray[6] = value;
				curWeap = CRC_FLAK_CANNON;
				result = 0;
			}
			else if(funcArgs[1] == "rocket")
			{
				xbot->imodeTypeArray[7] = value;
				curWeap = CRC_ROCKET_LAUNCHER;
				result = 0;
			}
			else if(funcArgs[1] == "sniper")
			{
				xbot->imodeTypeArray[8] = value;	
				if(xbot->lastWeaponCrc == CRC_SNIPER || xbot->lastWeaponCrc == CRC_LIGHT_GUN)
					curWeap = xbot->lastWeaponCrc;

				result = 0;
			}
			else
				result = "Bad Function Arguments";

			if(!result && curWeap == xbot->lastWeaponCrc)
			{
				switch(value)
				{
				case XBot::IMODE_TYPE_FIXER:
					xbot->imodeType = XBot::IMODE_FIXER;
					break;
				case XBot::IMODE_TYPE_AUTO:
					xbot->imodeType = XBot::IMODE_AUTO;
					break;
				case XBot::IMODE_TYPE_NONE_ENABLED:
					xbot->imodeType = XBot::IMODE_NONE;
					xbot->setAutoAim(true);
					break;
				case XBot::IMODE_TYPE_NONE_DISABLED:
					xbot->imodeType = XBot::IMODE_NONE;
					xbot->setAutoAim(false);
					break;
				}
			}

			return result;

	}
	else
		return result = "Bad Function Arguments";

}

char* XUT2k4CommandHandler::onSetWeaponRange()
{
	char* result;

	if(nFuncArgs == 2)
	{
		parser.trimStr(&funcArgs[0]);	
		_strlwr((char*)funcArgs[0].c_str());
		if(parser.isNumericIntArg(&funcArgs[0]) || funcArgs[0]=="infinite")
		{
			XBot* xbot = XBot::getXBot();

			parser.trimStr(&funcArgs[1]);
			_strlwr((char*)funcArgs[1].c_str());

			int value;
			if(funcArgs[0]=="infinite")
				value = WEAPON_RANGE_INFINITE;
			else
				value = 100 * atoi(funcArgs[0].c_str());
			
			if (value > 1000000)
				value = 1000000;
			else if(value < 0)
				value = WEAPON_RANGE_INFINITE;
			
			if(funcArgs[1] == "all")
			{
				for (int i = 0; i<9; i++)
					xbot->weaponRangeArray[i] = value;
				
				result = 0;
			}
			else if(funcArgs[1] == "shield")
			{
				xbot->weaponRangeArray[0] = value;
				result = 0;
			}
			else if(funcArgs[1] == "assault_rifle")
			{
				xbot->weaponRangeArray[1] = value;
				result = 0;
			}
			else if(funcArgs[1] == "ges")
			{		
				xbot->weaponRangeArray[2] = value;
				result = 0;
			}
			else if(funcArgs[1] == "shock")
			{
				xbot->weaponRangeArray[3] = value;
				result = 0;
			}
			else if(funcArgs[1] == "link")
			{	
				xbot->weaponRangeArray[4] = value;
				result = 0;
			}
			else if(funcArgs[1] == "minigun")
			{
				xbot->weaponRangeArray[5] = value;
				result = 0;
			}
			else if(funcArgs[1] == "flak")
			{
				xbot->weaponRangeArray[6] = value;
				result = 0;
			}
			else if(funcArgs[1] == "rocket")
			{
				xbot->weaponRangeArray[7] = value;
				result = 0;
			}
			else if(funcArgs[1] == "sniper")
			{
				xbot->weaponRangeArray[8] = value;	
				result = 0;
			}
			else
				result = "Bad Function Arguments";

			return result;
		}

	}
	else
		return result = "Bad Function Arguments";

}

char* XUT2k4CommandHandler::onJoin()
{
	return "";
}

char* XUT2k4CommandHandler::onLeave()
{
	return "";
}

char* XUT2k4CommandHandler::onGetPlayerList()
{
	return "";
}

unsigned int XUT2k4CommandHandler::getWeaponCRCfromStrName(string* name)
{
	if(*name == "shield")
		return CRC_SHIELD_GUN;
	else if(*name == "assault_rifle")
		return CRC_ASSAULT_RIFLE;
	else if(*name == "ges")
		return CRC_GES;
	else if(*name == "shock")
		return CRC_SHOCKRIFLE;
	else if(*name == "link")
		return CRC_LINK_GUN;
	else if(*name == "minigun")
		return CRC_MINIGUN;
	else if(*name == "flak")
		return CRC_FLAK_CANNON;
	else if(*name == "rocket")
		return CRC_ROCKET_LAUNCHER;
	else if(*name == "sniper")
		return CRC_SNIPER;
	else if(*name == "light_gun")
		return CRC_LIGHT_GUN;
	else
		return 0;

}


char* XUT2k4CommandHandler::onRetrieveCDKeys()
{
	return "";
}
