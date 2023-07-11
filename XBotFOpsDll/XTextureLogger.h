#pragma once

#include <D3dx8core.h>
#include <d3d8types.h>
#include <vector>
#include <stdio.h>
#include "FAKE_IDirect3DTexture8.h"
#include <windows.h>

class XTextureLogger
{
public:
	XTextureLogger();
	~XTextureLogger();

	void draw();
	void setDevice(LPDIRECT3DDEVICE8 d3dDeviceRef);
	void ZPression();
	void XPression();
	void CPression();
	void logTexture(FAKE_IDirect3DTexture8 *pTexture);

private:
	void setText();
	void logToFile();
	void startLogging();
	void stopLogging();
	bool IsInBackgroundTextureList(FAKE_IDirect3DTexture8* tex);
	void compareTextures();
	void clear();
	bool IsInLogTextureList(FAKE_IDirect3DTexture8* tex);


	LPDIRECT3DDEVICE8 d3dDevice;
	ID3DXFont*	loggerFont;
	D3DCOLOR loggerFontColor;
	RECT textRect;
	RECT textRectStart;
	FILE* texLogOut;
	UINT phase;
	UINT nBackground;
	UINT nLogTextures;
	UINT nLog;
	UINT logtime;
	BOOL logInProgres;

	char str1[256];
	char str2[256];
	char str3[256];
	char outStr[256];

	std::vector<FAKE_IDirect3DTexture8*> backgroundTextures;
	std::vector<FAKE_IDirect3DTexture8*> logTextures;
};