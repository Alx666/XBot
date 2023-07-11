#include "XWeaponManager.h"
#include "XFireMode.h"
#include "XFireModeDirectInstantOnKeydown.h"


XWeaponManager::XWeaponManager()
{
	weapMap.clear();
	lastWeaponCrc = 0;
	currentWeapon = 0;
}

XWeaponManager::~XWeaponManager()
{
    XWeaponMap::iterator it;
    for (it = weapMap.begin(); it != weapMap.end(); ++it) 
	{
		currentWeapon = it->second;
		delete currentWeapon;
    }
}

void XWeaponManager::checkCurrentWeapon(int crc)
{
	if(lastWeaponCrc != crc)	//weapon has been changed
	{
		lastWeaponCrc = crc;
		setWeaponFromLastCrc();
	}

}

void XWeaponManager::setWeaponFromLastCrc()
{
	XWeaponMap::iterator it;
	it = weapMap.find(lastWeaponCrc);

	if(it == weapMap.end())
	{
		//Condizione di errore, CRC non trovato
	}
	else
		currentWeapon = it->second;
}

void XWeaponManager::loadWeaponDefinitions()
{
	currentWeapon	= new XWeapon("Shield");
	currentWeapon->setFireModePrimary(new XFireModeDirectInstantOnKeydown());
	currentWeapon->setFireModeSecondary(new XFireModeDirectInstantOnKeydown());
	weapMap[CRC_SHIELD_GUN]		= currentWeapon;

	currentWeapon				= new XWeapon("Rifle");
	currentWeapon->setFireModePrimary(new XFireModeDirectInstantOnKeydown());
	currentWeapon->setFireModeSecondary(new XFireModeDirectInstantOnKeydown());
	weapMap[CRC_ASSAULT_RIFLE]	= currentWeapon;

	currentWeapon				= new XWeapon("Ges");
	currentWeapon->setFireModePrimary(new XFireModeDirectInstantOnKeydown());
	currentWeapon->setFireModeSecondary(new XFireModeDirectInstantOnKeydown());
	weapMap[CRC_GES]			= currentWeapon;

	currentWeapon				= new XWeapon("Shock");
	currentWeapon->setFireModePrimary(new XFireModeDirectInstantOnKeydown());
	currentWeapon->setFireModeSecondary(new XFireModeDirectInstantOnKeydown());
	weapMap[CRC_SHOCKRIFLE]		= currentWeapon;

	currentWeapon				= new XWeapon("Minigun");
	currentWeapon->setFireModePrimary(new XFireModeDirectInstantOnKeydown());
	currentWeapon->setFireModeSecondary(new XFireModeDirectInstantOnKeydown());
	weapMap[CRC_MINIGUN]		= currentWeapon;

	currentWeapon				= new XWeapon("Link");
	currentWeapon->setFireModePrimary(new XFireModeDirectInstantOnKeydown());
	currentWeapon->setFireModeSecondary(new XFireModeDirectInstantOnKeydown());
	weapMap[CRC_LINK_GUN]		= currentWeapon;

	currentWeapon				= new XWeapon("Sniper");
	currentWeapon->setFireModePrimary(new XFireModeDirectInstantOnKeydown());
	currentWeapon->setFireModeSecondary(new XFireModeDirectInstantOnKeydown());
	weapMap[CRC_SNIPER]			= currentWeapon;

	currentWeapon				= new XWeapon("Rockets");
	currentWeapon->setFireModePrimary(new XFireModeDirectInstantOnKeydown());
	currentWeapon->setFireModeSecondary(new XFireModeDirectInstantOnKeydown());
	weapMap[CRC_ROCKET_LAUNCHER]= currentWeapon;

	currentWeapon				= new XWeapon("Lightning");
	currentWeapon->setFireModePrimary(new XFireModeDirectInstantOnKeydown());
	currentWeapon->setFireModeSecondary(new XFireModeDirectInstantOnKeydown());
	weapMap[CRC_LIGHT_GUN]		= currentWeapon;

	currentWeapon				= new XWeapon("Flak");
	currentWeapon->setFireModePrimary(new XFireModeDirectInstantOnKeydown());
	currentWeapon->setFireModeSecondary(new XFireModeDirectInstantOnKeydown());
	weapMap[CRC_FLAK_CANNON]	= currentWeapon;

	currentWeapon = 0;
}