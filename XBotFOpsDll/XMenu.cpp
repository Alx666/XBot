#include "XMenu.h"
#include "XBot.h"

XMenu::XMenu(char* launcherPath, const D3DVIEWPORT8* viewport)
{
	d3dDevice = 0;

	path = launcherPath;

	//Calcolo delle dimensioni dei vari componenti del menu
	showingArea = MENU_VISIBLEAREA;
	hiddenArea  = MENU_SIZEX - showingArea;
	altitude	= MENU_ALT;

	//altitude = (viewport->Height * altitude) / 1024; //to determinate the correct altitude if resolution is different from 1024

	xPos = (float)1024 - showingArea;
	yPos = (float)768 - altitude;

	offX		= 0;
	slidingOut	= false;
	slidingIn	= false;
	isOut		= false;
	time		= 0;
	deltaTime	= 0;

	selectIndex = 0;

	for(int i = 0; i<MENU_VOICES; i++)
	{
		pointerArray[i] = 0;
		typeArray[i] = TYPE_UINT;
		limitArray[i].upper = 0;
		limitArray[i].lower = 0;

	}

	memset(string, 0, 128);
	

	menuFontColor = D3DCOLOR_RGBA( 4, 230, 55, 255);


	//Inizializazione della colonna dei display
	displayValues.left	= MENU_DISPLAY_POSX + MENU_DISPLAY_XTAB + xPos;
	displayValues.top	= MENU_DISPLAY_POSY + MENU_DISPLAY_YTAB + yPos;
	displayValues.right	= MENU_DISPLAY_POSX + MENU_DISPLAYSIZEX + xPos;
	displayValues.bottom= MENU_DISPLAY_POSY + MENU_DISPLAYSIZEY + yPos;
}

XMenu::~XMenu()									//TODO: (PRIORITA' ALTA) Completare il distruttore
{
	/*
	menuFont->OnLostDevice();
	timeFont->OnLostDevice();
	spriteDrawer->OnLostDevice();

	d3dDevice = 0;
	menuFont = 0;
	timeFont = 0;
	spriteDrawer = 0;
	hud = 0;
	selector = 0;

	delete[] pointerArray;
	delete[] typeArray;
	delete[] string;
	delete[] timers;

	delete bitmap;
	*/
}

void XMenu::setDevice(LPDIRECT3DDEVICE8 d3dDeviceRef)
{
	XBot* xbot = XBot::getXBot();
	
	d3dDevice = d3dDeviceRef;
	D3DXCreateSprite(d3dDevice, &spriteDrawer);
	

	//Creazione dell'HUD
	D3DXIMAGE_INFO info;
	info.Width = MENU_SIZEX;
	info.Height = MENU_SIZEY;
	info.Depth = 24;
	info.MipLevels = 0;
	info.Format = D3DFMT_R8G8B8;
	info.ResourceType = D3DRTYPE_TEXTURE;
	info.ImageFileFormat = D3DXIFF_BMP;

	void* data;
	unsigned int fsize;
	
	fsize = xbot->xffReader->GetFile("FOps_menu","bmp",&data);
	D3DXCreateTextureFromFileInMemoryEx(d3dDevice,data,fsize, MENU_SIZEX, MENU_SIZEY, 0, 0, D3DFMT_A8R8G8B8, D3DPOOL_DEFAULT, D3DX_FILTER_LINEAR, D3DX_FILTER_LINEAR, 0xFF000000, &info, NULL, &hud);
	delete[] data;

	fsize = xbot->xffReader->GetFile("FOps_wall","bmp",&data);
	D3DXCreateTextureFromFileInMemoryEx(d3dDevice,data,fsize, 32, 32, 0, 0, D3DFMT_A8R8G8B8, D3DPOOL_DEFAULT, D3DX_FILTER_LINEAR, D3DX_FILTER_LINEAR, 0xFF000000, NULL, NULL, &wall);
	delete[] data;

	fsize = xbot->xffReader->GetFile("XBot_head","bmp",&data);
	D3DXCreateTextureFromFileInMemoryEx(d3dDevice,data,fsize, 32, 32, 0, 0, D3DFMT_A8R8G8B8, D3DPOOL_DEFAULT, D3DX_FILTER_LINEAR, D3DX_FILTER_LINEAR, 0xFF000000, NULL, NULL, &head);
	delete[] data;

	fsize = xbot->xffReader->GetFile("XBot_aimenable","bmp",&data);
	D3DXCreateTextureFromFileInMemoryEx(d3dDevice,data,fsize, 32, 32, 0, 0, D3DFMT_A8R8G8B8, D3DPOOL_DEFAULT, D3DX_FILTER_LINEAR, D3DX_FILTER_LINEAR, 0xFF000000, NULL, NULL, &cross);
	delete[] data;


	

	D3DSURFACE_DESC desc;
	hud->GetLevelDesc(0, &desc);

	float tmp1, tmp2;

	tmp1 = info.Width;
	tmp2 = desc.Width;
	vScaling.x = tmp1/tmp2;

	tmp1 = info.Height;
	tmp2 = desc.Height;
	vScaling.y = tmp1/tmp2;

	//Creazione del selector
	info.Width = MENU_SELECTSIZEX;
	info.Height = MENU_SELECTSIZEY;	
	
	fsize = xbot->xffReader->GetFile("FOps_menuSelector","bmp",&data);
	D3DXCreateTextureFromFileInMemoryEx(d3dDevice,data,fsize, MENU_SELECTSIZEX, MENU_SELECTSIZEY, 0, 0, D3DFMT_A8R8G8B8, D3DPOOL_DEFAULT, D3DX_FILTER_LINEAR, D3DX_FILTER_LINEAR, 0xFF000000, &info, NULL, &selector);
	delete[] data;	
	
	selector->GetLevelDesc(0, &desc);
	
	tmp1 = info.Width;
	tmp2 = desc.Width;
	vScaleSelector.x = tmp1/tmp2;
	tmp1 = info.Height;
	tmp2 = desc.Height;
	vScaleSelector.y = tmp1/tmp2;

	//Creazione dei font
	LOGFONT LogFont = {MENU_FONTSIZE, 0, 0, 0, FW_NORMAL, false, false, false, DEFAULT_CHARSET, OUT_TT_PRECIS, CLIP_DEFAULT_PRECIS, PROOF_QUALITY, DEFAULT_PITCH, "Arial"};
	D3DXCreateFontIndirect(d3dDevice, &LogFont, &menuFont);	

}

// setDevice must be called before this!
void XMenu::draw()
{
	calcXoffset();

	spriteDrawer->Begin();

		spriteDrawer->Draw(hud, NULL, &vScaling, NULL, 0, &D3DXVECTOR2(xPos - offX, yPos), 0xBBFFFFFF);

		if(isOut)
		{
			spriteDrawer->Draw(selector	, NULL, &vScaleSelector	, NULL, 0, &D3DXVECTOR2(xPos + MENU_SELECT_POSX - offX, yPos + MENU_SELECT_POSY + (selectIndex * MENU_SELECTSIZEY + selectIndex * MENU_SELECT_YDIS)), 0x33FFFFFF);

			//Scritte all'Interno del Menu

			menuFont->Begin();

				for(int i = 0; i < MENU_VOICES; i++)
				{
					if(typeArray[i] == TYPE_BOOL)
					{
						if(*pointerArray[i] != 0)
						{
							menuFontColor = D3DCOLOR_RGBA( 4, 230, 55, 255);
							sprintf(string, "true");
						}
						else
						{
							menuFontColor = D3DCOLOR_RGBA( 255, 0, 0, 255);
							sprintf(string, "false");
						}

						menuFont->DrawText(string, -1, &displayValues, DT_CENTER, menuFontColor);
					}
					else if(typeArray[i] == TYPE_COLOR)
					{
						switch(*pointerArray[i])
						{
						case COLOR_NONE: sprintf(string, "none"); menuFontColor = D3DCOLOR_RGBA(255, 255, 255, 255);break;
						case COLOR_BLUE: sprintf(string, "Swat"); menuFontColor = D3DCOLOR_RGBA(  0,   0, 255, 255);break;
						case COLOR_RED:  sprintf(string, "Mercs");  menuFontColor = D3DCOLOR_RGBA( 255, 0,   0, 255);	break;						
						default:		 sprintf(string, "ERROR");	break;
						}

						menuFont->DrawText(string, -1, &displayValues, DT_CENTER, menuFontColor);
						menuFontColor = D3DCOLOR_RGBA( 4, 230, 55, 255);
					}
					else if(typeArray[i] == TYPE_CUSTOM)
					{
						formatCustomValue(i);

						menuFont->DrawText(string, -1, &displayValues, DT_CENTER, menuFontColor);
						menuFontColor = D3DCOLOR_RGBA( 4, 230, 55, 255);
					}
					else
					{
						menuFontColor = D3DCOLOR_RGBA( 4, 230, 55, 255);
						sprintf(string, "%i", *pointerArray[i]);
						menuFont->DrawText(string, -1, &displayValues, DT_CENTER, menuFontColor);
					}

					displayValues.top += MENU_DISPLAYSIZEY + MENU_DISPLAY_YDIST;
				}

			menuFont->End();

			displayValues.top = MENU_DISPLAY_POSY + MENU_DISPLAY_YTAB + yPos;
		}

	spriteDrawer->End();
	

//OPERAZIONI NON PARAMETRICHE CAMBIANO DA VERSIONE A VERSIONE 
//**************************************************************************************************************

	if(!isOut)
	{
		spriteDrawer->Begin();

		if(XBot::getXBot()->imodeSwitch || XBot::getXBot()->autoAimSwitch)
			spriteDrawer->Draw(cross, NULL, NULL, NULL, 0, &D3DXVECTOR2(xPos - 60 , yPos+145), 0xBBFFFFFF);

		if(*pointerArray[6])
			spriteDrawer->Draw(wall, NULL, NULL, NULL, 0, &D3DXVECTOR2(xPos - 60, yPos+195), 0xBBFFFFFF);

		if(*pointerArray[3])
			spriteDrawer->Draw(head, NULL, NULL, NULL, 0, &D3DXVECTOR2(xPos - 60, yPos+235), 0xBBFFFFFF);
		spriteDrawer->End();
	}


}


void XMenu::formatCustomValue(UINT index)
{
	switch(*pointerArray[index])
	{
	case XBot::IMODE_FIXER:	sprintf(string, "fixer"); menuFontColor = D3DCOLOR_RGBA(150, 255,   0, 255);	break;
	case XBot::IMODE_AUTO:	sprintf(string, "auto");  menuFontColor = D3DCOLOR_RGBA(  0, 255, 100, 255);	break;
	case XBot::IMODE_NONE:	sprintf(string, "none");  menuFontColor = D3DCOLOR_RGBA(255,   0,   0, 255);	break;
	default:				sprintf(string, "ERROR");	break;
	}
}

//**************************************************************************************************************

void XMenu::setInxRef(UINT *address, int Index, int enumType, int upperLimit, int lowerLimit)
{
	pointerArray[Index] = address;
	typeArray[Index] = enumType;

	if(enumType == TYPE_UINT || enumType == TYPE_CUSTOM)
	{
		limitArray[Index].upper = upperLimit;
		limitArray[Index].lower = lowerLimit;
	}
}

void XMenu::switchValue(UINT index)
{
	if((typeArray[index] != TYPE_BOOL) || (index >= MENU_VOICES))
		return;

	selectIndex = index;
	switchBool();
}

int XMenu::add()
{
	if(slidingIn || slidingOut)
		return -1;

	time = GetTickCount();

	if(!isOut)
	{
		slideOut();
		return -1;
	}

	switch(typeArray[selectIndex])
	{
	case TYPE_BOOL:		switchBool();	break;
	case TYPE_CUSTOM:	incrementInt(); break;
	case TYPE_UINT:		incrementInt(); break;
	case TYPE_COLOR:	switchColor();	break;
	}

	return selectIndex;
}

int XMenu::subtract()
{
	if(slidingIn || slidingOut)
		return -1;

	time = GetTickCount();

	if(!isOut)
	{
		slideOut();
		return -1;
	}

	switch(typeArray[selectIndex])
	{
	case TYPE_BOOL:		switchBool();	break;
	case TYPE_CUSTOM:	decrementInt(); break;
	case TYPE_UINT:		decrementInt(); break;
	case TYPE_COLOR:	switchColor();	break;
	}

	return selectIndex;
}

void XMenu::moveUp()
{
	if(slidingIn || slidingOut)
		return;

	time = GetTickCount();

	if(!isOut)
	{
		slideOut();
		return;
	}

	if(selectIndex>0)
		selectIndex--;
	else
		selectIndex = MENU_VOICES - 1;
}

void XMenu::moveDown()
{
	if(slidingIn || slidingOut)
		return;

	time = GetTickCount();

	if(!isOut)
	{
		slideOut();
		return;
	}

	if(selectIndex < MENU_VOICES - 1)
		selectIndex++;
	else
		selectIndex = 0;
}


bool XMenu::getBoolValue(UINT index)
{
	return *pointerArray[index];
}
int XMenu::getIntValue(UINT index)
{
	return *pointerArray[index];
}

//Funzioni private
inline void XMenu::calcXoffset()
{
	if(!isOut)
		return;
	
	deltaTime = GetTickCount() - time;

	if(deltaTime > MENU_TIMEOUT)
	{
		slidingOut = false;
		slidingIn = true;
		time = GetTickCount();
		deltaTime = GetTickCount() - time;
	}

	if(slidingOut)
	{	

		if(deltaTime < MENU_ANIMTIME)
		{
			offX = hiddenArea * (deltaTime/MENU_ANIMTIME);
		}
		else
		{
			offX = (float)hiddenArea;
			slidingOut = false;
		}
	}
	else if(slidingIn)
	{

		if(deltaTime < MENU_ANIMTIME)
		{
			offX = hiddenArea -(hiddenArea * (deltaTime/MENU_ANIMTIME)); //causa del rimbalso (eliminare?)
		}
		else
		{
			offX = 0.0f;
			slidingIn = false;
			isOut = false;
		}
	}

	displayValues.left	= MENU_DISPLAY_POSX + MENU_DISPLAY_XTAB + xPos - offX;
	displayValues.right	= MENU_DISPLAY_POSX + MENU_DISPLAY_XTAB + xPos + MENU_DISPLAYSIZEX - offX;
}

void XMenu::slideOut()
{
	slidingOut = true;
	isOut = true;
}
void XMenu::slideIn()
{
	slidingIn = true;
}



void XMenu::switchColor()
{
	switch(*pointerArray[selectIndex])
	{
	case COLOR_NONE: *pointerArray[selectIndex] = COLOR_BLUE; break;
	case COLOR_BLUE: *pointerArray[selectIndex] = COLOR_RED;  break;
	case COLOR_RED:  *pointerArray[selectIndex] = COLOR_NONE; break;
	}
}

void XMenu::switchBool()
{
	if(*pointerArray[selectIndex] != 0)
	{
		*pointerArray[selectIndex] = 0;
	}
	else
	{
		*pointerArray[selectIndex] = 1;
	}
}

void XMenu::incrementInt()
{
	if(*pointerArray[selectIndex] >= limitArray[selectIndex].upper)
		return;
	else
		*pointerArray[selectIndex] += 1;
}

void XMenu::decrementInt()
{

	if(*pointerArray[selectIndex] <= limitArray[selectIndex].lower)
		return;
	else
		*pointerArray[selectIndex] -= 1;
}

void XMenu::switchBool(UINT index)
{
	if(*pointerArray[index] != 0)
	{
		*pointerArray[index] = 0;
	}
	else
	{
		*pointerArray[index] = 1;
	}
}

UINT XMenu::getSelectionIndex()
{
	return selectIndex;
}

UINT XMenu::getIndex()
{
	return selectIndex;
}
