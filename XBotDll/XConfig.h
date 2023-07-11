#pragma once

#include <windows.h> //maybe use only QT one day...
#include "CIniFile.h"


#define CURRENT_VERSION		0x1602
#define MAX_PLAYERS	32

struct XPlayer
{
	char *name;
	UINT codedIp;
};

class XConfig
{
public:
	XConfig();
	~XConfig();

	CIniFile *inireader;

	char  *cfgFile;
	char  *pathToUT;
	char  *exeParam;
	char  launchPath[1024];
	bool  stealthMode;

	//Bindable Keys
	DWORD enableAim;
	DWORD menuUp;
	DWORD menuDown;
	DWORD menuPlus;
	DWORD menuMinus;
	DWORD priFire;
	DWORD altFire;
	DWORD jump;
	DWORD enableDodge;
	DWORD enableHeadShot;
	DWORD masterSwitch;
	DWORD resetCounterShield;
	DWORD resetCounterDDamage;
	DWORD resetCounterRedeem;
	DWORD autoSwap;


	//Xbot values ONLY EDITABLE VIA UNREAL
	bool autoAimEnabled;
	bool radarEnabled;
	int  imodeType;
	bool headShotEnabled;
	int  dodgeEnabled;
	int  pingCompValue;
	double  mouseSpeed;

	XPlayer playerlist[32];
	DWORD threadID;

	bool readSettings();
	void writeSettings();
	void saveStatus(bool autoAim,  bool radar,    int imodeType, 
					bool headshot,  int pingComp,int dodge = NULL);

	void buildDefault();
};
