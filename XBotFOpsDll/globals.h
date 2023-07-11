#pragma once

//#define TEXTURE_LOGGER

#include <d3d8.h>
#include "FAKE_IDirect3D8.h"
#include "FAKE_IDirect3DDevice8.h"
#include "FAKE_IDirectInput8.h"
#include "FAKE_IDirectInputDevice8.h"

#ifdef TEXTURE_LOGGER
	#include "XTextureLogger.h"
#endif


//GLOBALS
FAKE_IDirect3D8 FAKE_D3D8;
FAKE_IDirect3D8 *pFAKE_D3D8 = NULL;						
IDirect3D8 *pD3D8 = NULL;						

FAKE_IDirect3DDevice8 FAKE_D3DDevice8;
FAKE_IDirect3DDevice8 *pFAKE_D3DDevice8 = NULL;		
IDirect3DDevice8 *pD3DDevice8 = NULL;				


IDirectInput8 *pDInput8 = NULL;						//Original Device pointer
FAKE_IDirectInput8 *pFAKE_DInput8 = NULL;				//Wrapped Device pointer
FAKE_IDirectInput8 FAKE_DInput8;							//Wrapped Device

IDirectInputDevice8 *pDInputDevice8 = NULL;			//Original Device pointer
FAKE_IDirectInputDevice8 *pFAKE_DInputDevice8 = NULL;	//Wrapped Device pointer


#ifdef TEXTURE_LOGGER
	XTextureLogger *texturelogger;
#endif











