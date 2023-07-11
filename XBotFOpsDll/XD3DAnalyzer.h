#pragma once
#include <d3d8.h>
#include "FAKE_IDirect3DTexture8.h"


class XD3DAnalyzer
{
	public:
		
		XD3DAnalyzer() {currentRenderedObjectType=0;};

		enum {TYPE_OTHER, TYPE_PLAYERSKIN, TYPE_PLAYERHEAD, TYPE_WEAPON, TYPE_GRANADE, TYPE_FOPS_LOGO, TYPE_WEAPON_HELD, TYPE_TERROR_GLOVES, TYPE_SWAT_GLOVES};

		char currentRenderedObjectType;

		void ProcessDrawPrimitive(D3DPRIMITIVETYPE PrimitiveType, UINT StartVertex, UINT PrimitiveCount);
		bool ProcessDrawIndexedPrimitive(D3DPRIMITIVETYPE Type, UINT MinIndex, UINT NumVertices, UINT StartIndex, UINT PrimitiveCount);
		bool isPlayerSkin(unsigned int crc);
		bool isTeamSkin(unsigned int crc);
		bool isGranadeTexture(unsigned int crc);
		void getWeaponName(unsigned int crc,char* string);
		bool isWeaponHeldTexture(unsigned int crc);
		bool IsInTextureList(FAKE_IDirect3DTexture8* tex);
		bool isWeaponTexture(unsigned int crc);
		void AnalyzeTexture(unsigned int crc);
};