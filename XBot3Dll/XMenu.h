#pragma once

#include <d3dx8core.h>
#include <d3d8types.h>
#include <stdio.h>
#include "Timer.h"

//Parametri del bitmap principale (l'hud)
#define MENU_SIZEX			251//238		//dimensione X in pixel
#define MENU_SIZEY			230		//dimensione Y in pixel
#define MENU_VISIBLEAREA	90		//l'area sempre visibile del bitmap in pixel
#define MENU_ALT			450		//altezza alla quale collocare il menu (a 1024*768)
#define MENU_ANIMTIME		150.0f	//velocita' uscita/entrata del menu
#define MENU_TIMEOUT		2500.0f	//massimo tempo di intattivita' quando menu e' aperto
#define MENU_FONTSIZE		15		//dimensione dei caratteri
#define MENU_VOICES			8		//Numero delle voci che deve gestire
#define MENU_TIMERS			3		//Numero dei timer

//Parametri per lo spostamento della bitmap che evidenzia la selezione
#define MENU_SELECTSIZEX	131		//Size X del bitmap
#define MENU_SELECTSIZEY	23		//Size Y del bitmap
#define MENU_SELECT_POSX	109
#define MENU_SELECT_POSY	17
#define MENU_SELECT_YDIS	2		//Includere i 2 pixel del bordo

//Parametri per la colonnina dei display
#define MENU_DISPLAYSIZEX	41		//Larghezza di un display
#define MENU_DISPLAYSIZEY	22		//Altezza di un display
#define MENU_DISPLAY_POSX	115		//posizione x del primo display all'interno del menu
#define MENU_DISPLAY_POSY	19		//posizione y del primo display all'interno del menu
#define MENU_DISPLAY_YDIST	3		//distanza tra un display e quello sottostante (escludere pixel di bordo)
#define MENU_DISPLAY_YTAB	2		//centratura y del testo
#define MENU_DISPLAY_XTAB	1		//centratura x del testo




struct Limit
{
	int upper;
	int lower;
};


class XMenu
{
	public:
		XMenu(char* launcherPath, const D3DVIEWPORT8* viewport);
		~XMenu();
		enum {TYPE_BOOL  = 0,  TYPE_UINT = 1, TYPE_COLOR = 2, TYPE_CUSTOM = 3};
		enum {COLOR_NONE = 0, COLOR_BLUE = 1, COLOR_RED  = 2};

		bool isOut;

		void draw();
		void setDevice(LPDIRECT3DDEVICE8 d3dDeviceRef);
		void setInxRef(UINT *address, int Index, int enumType, int upperLimit = 100, int lowerLimit = 0);
		void switchValue(UINT index);
		void setTimerValue(int indexTimer, UINT value);
		void restartTimer(UINT indexTimer);
		void reinitializeTimer(UINT indexTimer);
		bool getBoolValue(UINT index);
		int  getIntValue(UINT index);
		UINT getIndex();
		void setViewport(int width, int height);
		void OnResetDevice();
		void playTimerSound();


		void moveUp();
		void moveDown();
		int add();
		int subtract();
		void setAlpha(char alpha, const char* args);


		void switchBool(UINT index);
		UINT getSelectionIndex();


	private:
		void switchBool();
		void switchColor();
		void incrementInt();
		void decrementInt();
		void calcXoffset();
		void formatCustomValue(UINT index);
		void slideIn();
		void slideOut();
		void loadTexture();

		LPDIRECT3DDEVICE8 d3dDevice;
		ID3DXSprite* spriteDrawer;
		IDirect3DTexture8* hud;
		IDirect3DTexture8* selector;

		//Grafica aggiuntaq per UT
		IDirect3DTexture8* dodgeman;
		IDirect3DTexture8* head;
		IDirect3DTexture8* cross;

		D3DXVECTOR2 vScaling;				//Vettore per preservare l'aspect ratio della BMP
		D3DXVECTOR2 vScaleSelector;

		ID3DXFont*	menuFont;
		ID3DXFont*	timeFont;
		ID3DXFont*	timeFont2;

		D3DCOLOR timeFontColor;
		D3DCOLOR timeFont2Color;
		D3DCOLOR menuFontColor;
		D3DCOLOR menuColor;

		RECT display1Pos;
		RECT displayTimer1;
		RECT display2Pos;
		RECT displayTimer2;
		RECT display3Pos;
		RECT displayTimer3;
		RECT displayValues;

		Timer timers[MENU_TIMERS];

		char *path;
		float xPos, yPos;					//Unslided coords
		float offX;							//Offset per lo spostamento orizzontale

		int showingArea;
		int hiddenArea;
		int altitude;
		UINT selectIndex;
		UINT *pointerArray[MENU_VOICES];	//used for booleans and integer
		UINT typeArray[MENU_VOICES];
		Limit limitArray[MENU_VOICES];
		char string[128];

		unsigned int time;
		unsigned int deltaTime;
		bool slidingOut;
	    bool slidingIn;

		void* timerSound;
		bool playingTimerSound;
		bool isReset;
};