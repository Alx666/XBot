#include "CrcTable.h"
#include "XFireMode.h"
#include "XFireModeDirectInstantOnKeydown.h"
#include "XWeapon.h"
#include "XWeaponManager.h"
#include <windows.h>

#define CRC_SHOCKRIFLE			0xF1F31535
#define CRC_FLAK_CANNON			0x7aa0355d 
#define CRC_MINIGUN				0xa7779c11 
#define CRC_LINK_GUN			0x7d519c3  
#define CRC_GES					0x1908d5c5 
#define CRC_ASSAULT_RIFLE		0xbecf629c   
#define CRC_SHIELD_GUN			0xd074c361 
#define CRC_LIGHT_GUN			0x6500d5da 
#define CRC_LIGHT_GUN_ZOOM		0x41a9cbc3
#define CRC_SNIPER_ZOOM			0x69d8834b
#define CRC_SNIPER				0x6cea6f5c
#define CRC_ROCKET_LAUNCHER		0xa1149ae2 


void main()
{
	XWeaponManager* wm = new XWeaponManager();
	wm->loadWeaponDefinitions();

	int counter = 0;

	while(counter < 50)
	{
		if(counter < 10)
			wm->checkCurrentWeapon(CRC_MINIGUN);
		else if(counter < 20)
			wm->checkCurrentWeapon(CRC_SHOCKRIFLE);
		else
			wm->checkCurrentWeapon(CRC_GES);

		counter++;

	}

	delete wm;
}