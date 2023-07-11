#pragma once
//#define TEST
#include "defines.h"
#include <D3dx8core.h>
#include <vector>
#include "FAKE_IDirect3DTexture8.h"
#include "Crc32.h"
#include "CrcTable.h"
#include "UPickup.h"
#include "UTarget.h"
#include "XMenu.h"
#include "XConsole.h"
#include "XAim.h"
#include "XDodger.h"
#include "XD3DAnalyzer.h"
#include "XInputHandler.h"
#include "XFileFormat.h"
#include "XDrawer.h"
#include "XConfig.h"



class XBot
{
	friend class XCommmandHandler;

public:

	XBot(); 
	~XBot();

	enum {TEAM_RED, TEAM_BLUE, TEAM_DM};
	enum {IMODE_NONE = 0, IMODE_AUTO = 1, IMODE_FIXER = 2, DODGEMODE_NONE = 3, DODGEMODE_MANUAL = 4, DODGEMODE_AUTO = 5, IMODE_AUTOCOMBO = 6};
	enum {IMODE_TYPE_NONE_ENABLED,IMODE_TYPE_NONE_DISABLED,IMODE_TYPE_FIXER,IMODE_TYPE_AUTO};
	/////STATIC MEMBERS///////////////
	static XBot* xbot;
	static XBot* getXBot();



	////D3D8Device Pointer
	LPDIRECT3DDEVICE8 d3dDevice;

	////XOBJECTS
	XMenu*				menu;
	XConfig*			xconfig;
	XAim*				aimAssistant;
	XDodger*			dodger;
	XD3DAnalyzer*		d3dAnalyzer;
	XInputHandler*		inputHandler;
	CXFileFormat*		xffReader;
	XConsole*			console;
	XDrawer*			drawer;
	//XWeaponSwapper*		weaponSwapper;

	////TEXTURE MANAGMENT
	std::vector<FAKE_IDirect3DTexture8*> texturesList;
	FAKE_IDirect3DTexture8*				 currentTexture;

	////PLAYER VALUES
	UTarget*	currentPlayer;
	D3DMATRIX	lastPlayerWorldPosition;
	UINT		currentWeaponCrc;
	UINT		lastWeaponCrc;

	////XBOT STATUS FLAGS
	BOOL stealthMode;
	BOOL gameStarted;
	BOOL lastGameStarted;
	BOOL targetLocked;
	BOOL isAutoFiring;
	BOOL isAltFireDown; //TEMP inutilizzata per ora
	BOOL primFireDown;
	BOOL secFireDown;
	BOOL primFireModeSwitch;
	UINT imodeType;
	UINT mouseSensibility;
	bool normalizedPlayerSpeed;
	bool timerEnabled;
	bool timerSoundEnabled;
	UINT startFireTime;
	UINT nOfDrawnWeapon;

	////XBOT FEATURES STATS
	BOOL masterSwitch;
	BOOL autoAimSwitch;
	BOOL radarSwitch;
	BOOL headshotSwitch;
	BOOL imodeSwitch;			//aka, autoaimenabled (red circle in menu)
	BOOL easyDodgeSwitch;
	BOOL counterShockEnabled;
	int  weaponRangeArray[9];
	UINT imodeTypeArray[9];
	UINT crosshairRadiusArray[9];
	UINT aimSpeedArray[9];
	UINT crosshairRadius;
	UINT unlockStr;
	UINT pingCorrection;
	//UINT aimSpeed;
	UINT playerTeam;
	float shockComboMINAutoBlastRange;
	float shockComboMAXAutoBlastRange;
	float oldComboDist;
	
	////XBOT CONTROLS KEYS
	DWORD keyEnableAim;
	DWORD keyMenuUp;
	DWORD keyMenuDown;
	DWORD keyMenuPlus;
	DWORD keyMenuMinus;
	DWORD keyPrimFire;
	DWORD keyAltFire;
	DWORD keyAltFireDInput;
	DWORD keyMasterSwitch;
	DWORD keyResetCounterShield;
	DWORD keyResetCounterDDamage;
	DWORD keyResetCounterRedeem;
	DWORD keyEnableCounterShock;
	DWORD keyHeadShot;
	DWORD keyDodge;
	DWORD keyJump;
	DWORD keyJumpDInput;
	
	/////MOUSE-AIM
	long int moveMouseX;
	long int moveMouseY;

	/////FPS CALCULATOR
	LARGE_INTEGER freq;
	float frameTime;
	float currentTime;
	float lastTime;
	
	/////MISC. VARIABLES
	CCrc32*					Crc32Calculator;
	DWORD					AIMBOT_D3D_STATE;
	unsigned int			stride;
	D3DVIEWPORT8			currentViewport;
	std::vector<UTarget>	radarListHostile;
	std::vector<UObject>	radarListFriendly;
	std::vector<UTarget>	shockCoreList;
	char*					launcherPath;
	bool					blastCombo;
	INPUT					InputUp;
	INPUT					InputDown;
	bool					firstBeginScene;

	/////OBJECTS
	UPickup *pkShield100;
	UPickup *pkDDamage;
	UPickup *pkRedeemer;

	UTarget *tPrimary;
	UTarget *tSecondary;
	
	//FUNCTIONS
	void EndScene();
	void BeginScene();
	void setSecondaryTarget(D3DMATRIX* matrix);
	void setPrimaryTarget(D3DMATRIX* matrix,D3DVECTOR *mPoint);
	void addToRadar(D3DMATRIX* matrix,D3DVECTOR *mPoint,bool hostile=true, bool head = false);
	void setDevice(LPDIRECT3DDEVICE8 d3dDeviceRef);
	void resetDDamageTimer(bool bcast = false);
	void resetShield100Timer(bool bcast = false);
	void resetRedeemTimer(bool bcast = false);
	void setAutoAim(BOOL active);
	void setAutoFireMode(UINT type);
	void swapAutoAimOnOff();
	void startFire();
	void stopFire();
	int  getXhairSize();
	UINT getAimSpeed();

	bool getIsInWeaponRange(UTarget* t);

	void onModifyImodeType();
	void onModifyCrosshairRadius();

private:	
	void modifyXHairSize();
	void AutofireRoutine();
	void BeginSceneReset();
	void EndSceneReset();
	void ShockComboRoutines();
	void TimerRoutines();
	void CurrentWeaponRoutines();
	void comboNearestTarget();
	void Aim();	
	void SetPlayerWorldPosition();
	void SetFps();
	void setStartupConf();
	bool checkHeldWeapon(bool b = false);
	void GESStartFire();
	void rocketStartFire();
	void modifyImodeType();
	void setImodeType();

};
