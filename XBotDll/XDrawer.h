#pragma once
#include <d3d8.h>
#include <D3dx8core.h>

class XDrawer
{
	public:
		
		XDrawer();
		~XDrawer();

		void setDevice(LPDIRECT3DDEVICE8 d3dDeviceRef);
		void OnResetDevice();
		void DrawOnEndScene();
		void DrawTargetsRadarPix();
		void DrawBotLogos();
		void setAlpha(char alpha, const char* args);

	private:
		
		void loadTextures();
		
		LPDIRECT3DDEVICE8 d3dDevice;

		////FONT MANAGMENT
		ID3DXFont*	radarFont;
		RECT fontPosition;
    
		////SPRITES MANAGMENT
		IDirect3DTexture8* logoSprite;
		IDirect3DTexture8* credtisSprite;
		IDirect3DTexture8* targetRadius;
		IDirect3DTexture8* radarPixCurrent;
		IDirect3DTexture8* radarPixCombo;
		IDirect3DTexture8* radarPixComboBlast;
		IDirect3DTexture8* radarPixHostile;
		IDirect3DTexture8* radarPixFriendly;
		ID3DXSprite*	   spriteDrawer;

		bool isReset;

		D3DCOLOR	targetRadiusColor;
		D3DCOLOR	radarPixColor;
		D3DCOLOR	radarTextColor;

};