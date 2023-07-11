#pragma once


#include <D3dx8core.h>
#include <vector>
#include <winable.h>
#include "FAKE_IDirect3DTexture8.h"
#include "Crc32.h"
#include "DrawingFunc.h"
#include "CrcTable.h"
#include "UTarget.h"
#include "XMenu.h"
#include "XAim.h"
#include "XD3DAnalyzer.h"
#include "XInputHandler.h"
#include "XFileFormat.h"
#include "..\\XBotLauncher\\XConfig.h"

#define PLAYER_SPEED    5.0f
#define DEFAULT_UNLOCK_STR  20
#define DEFAULT_AIM_SPEED	40
#define DEFAULT_XHAIR_SIZE  50

class XBot
{
public:

	XBot(); 
	~XBot();

	enum {TEAM_NONE,TEAM_SWAT,TEAM_TERROR};
	enum {IMODE_NONE = 0, IMODE_AUTO = 1, IMODE_FIXER = 2};

	/////STATIC MEMBERS///////////////
	static XBot* xbot;
	static XBot* getXBot();



	////D3D8Device Pointer
	LPDIRECT3DDEVICE8 d3dDevice;

	////XOBJECTS
	XMenu*				menu;
	XConfig*			xconfig;
	XAim*				aimAssistant;
	XD3DAnalyzer*		d3dAnalyzer;
	XInputHandler*		inputHandler;
	CXFileFormat*		xffReader;
	
	////FONT MANAGMENT
	ID3DXFont*	radarFont;
	RECT fontPosition;
    
	////SPRITES MANAGMENT
	IDirect3DTexture8*	logoSprite;
	IDirect3DTexture8*	credtisSprite;
	IDirect3DTexture8*	targetRadius;
	IDirect3DTexture8*	radarPixCurrent;
	IDirect3DTexture8*	radarPixGranade[5];
	IDirect3DTexture8*	radarPixHostile;
	IDirect3DTexture8*	radarPixFriendly;
	ID3DXSprite*		spriteDrawer;

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

	////XBOT FEATURES STATS
	BOOL masterSwitch;
	BOOL autoAimSwitch;
	BOOL radarSwitch;
	BOOL headshotSwitch;
	BOOL imodeSwitch;
	UINT crosshairRadius;
	UINT unlockStr;
	UINT pingCorrection;
	UINT aimSpeed;
	UINT playerTeam;
	BOOL wallHack;
	UINT mouseSensibility;

	
	////XBOT CONTROLS KEYS
	DWORD keyEnableAim;
	DWORD keyMenuUp;
	DWORD keyMenuDown;
	DWORD keyMenuPlus;
	DWORD keyMenuMinus;
	DWORD keyPrimFire;
	DWORD keyAltFire;
	DWORD keyMasterSwitch;
	DWORD keyResetCounterShield;
	DWORD keyResetCounterDDamage;
	DWORD keyResetCounterRedeem;
	DWORD keyHeadShot;
	DWORD keyWallHack;
	
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
	std::vector<UTarget>	radarGranadeList;
	std::vector<UObject>	radarWeaponList;
	char*					launcherPath;
	INPUT					InputUp;
	INPUT					InputDown;
	char					lastPlayerSkinDrawnFlag;			

	/////OBJECTS
	UTarget *tPrimary;
	UTarget *tSecondary;
	
	//FUNCTIONS
	void EndScene();
	void BeginScene();
	
	
	void setSecondaryTarget(D3DMATRIX* matrix);
	void setPrimaryTarget(D3DMATRIX* matrix,D3DVECTOR *mPoint);
	
	void addToRadar(D3DMATRIX* matrix,D3DVECTOR *mPoint,bool hostile=true, bool head = false);
	
	void setDevice(LPDIRECT3DDEVICE8 d3dDeviceRef);
	
	void setAutoAim(BOOL active);
	void setAutoFireMode(UINT type);
	void swapAutoAimOnOff();

	void startFire();
	void stopFire();

private:	
	
	void AutofireRoutine();
	void BeginSceneReset();
	void EndSceneReset();
	void CurrentWeaponRoutines();
	void Aim();	
	void SetPlayerWorldPosition();
	void SetFps();

};
