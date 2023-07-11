#pragma once
#include <d3d8.h>
#include "FAKE_IDirect3DTexture8.h"


class XD3DAnalyzer
{
	public:
		
		XD3DAnalyzer() {currentRenderedObjectType=0;};

		enum {TYPE_OTHER, TYPE_PLAYERSKIN, TYPE_PLAYERHEAD, TYPE_WEAPON, TYPE_PICKUP, TYPE_NVIDIALOGO, TYPE_SHOCKCORE};

		char currentRenderedObjectType;

		void ProcessDrawPrimitive(D3DPRIMITIVETYPE PrimitiveType, UINT StartVertex, UINT PrimitiveCount);
		bool ProcessDrawIndexedPrimitive(D3DPRIMITIVETYPE Type, UINT MinIndex, UINT NumVertices, UINT StartIndex, UINT PrimitiveCount);
		bool isPlayerSkin(unsigned int crc);
		bool isTeamSkin(unsigned int crc);
		bool isDMSkin(unsigned int crc);
		bool isRedSkin(unsigned int crc);
		bool isBlueSkin(unsigned int crc);
		bool IsInTextureList(FAKE_IDirect3DTexture8* tex);
		bool isWeaponTexture(unsigned int crc);
		bool isPickupTexture(unsigned int crc);
		void AnalyzeTexture(FAKE_IDirect3DTexture8* pTexture);
};