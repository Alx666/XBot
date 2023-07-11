#include "XWeaponManager.h"
#include "XAimModeInstantRay.h"
#include "XIModeAuto.h"


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
	currentWeapon->setAimModePrimary(new XAimModeInstantRay());
	currentWeapon->setAimModeSecondary(new XAimModeInstantRay());
	currentWeapon->setIModePrimary(new XIModeAuto(currentWeapon));
	currentWeapon->setIModeSecondary(new XIModeAuto(currentWeapon));
	weapMap[CRC_SHIELD_GUN]		= currentWeapon;

	currentWeapon				= new XWeapon("Rifle");
	currentWeapon->setAimModePrimary(new XAimModeInstantRay());
	currentWeapon->setAimModeSecondary(new XAimModeInstantRay());
	currentWeapon->setIModePrimary(new XIModeAuto(currentWeapon));
	currentWeapon->setIModeSecondary(new XIModeAuto(currentWeapon));
	weapMap[CRC_ASSAULT_RIFLE]	= currentWeapon;

	currentWeapon				= new XWeapon("Ges");
	currentWeapon->setAimModePrimary(new XAimModeInstantRay());
	currentWeapon->setAimModeSecondary(new XAimModeInstantRay());
	currentWeapon->setIModePrimary(new XIModeAuto(currentWeapon));
	currentWeapon->setIModeSecondary(new XIModeAuto(currentWeapon));
	weapMap[CRC_GES]			= currentWeapon;

	currentWeapon				= new XWeapon("Shock");
	currentWeapon->setAimModePrimary(new XAimModeInstantRay());
	currentWeapon->setAimModeSecondary(new XAimModeInstantRay());
	currentWeapon->setIModePrimary(new XIModeAuto(currentWeapon));
	currentWeapon->setIModeSecondary(new XIModeAuto(currentWeapon));
	weapMap[CRC_SHOCKRIFLE]		= currentWeapon;

	currentWeapon				= new XWeapon("Minigun");
	currentWeapon->setAimModePrimary(new XAimModeInstantRay());
	currentWeapon->setAimModeSecondary(new XAimModeInstantRay());
	currentWeapon->setIModePrimary(new XIModeAuto(currentWeapon));
	currentWeapon->setIModeSecondary(new XIModeAuto(currentWeapon));
	weapMap[CRC_MINIGUN]		= currentWeapon;

	currentWeapon				= new XWeapon("Link");
	currentWeapon->setAimModePrimary(new XAimModeInstantRay());
	currentWeapon->setAimModeSecondary(new XAimModeInstantRay());
	currentWeapon->setIModePrimary(new XIModeAuto(currentWeapon));
	currentWeapon->setIModeSecondary(new XIModeAuto(currentWeapon));
	weapMap[CRC_LINK_GUN]		= currentWeapon;

	currentWeapon				= new XWeapon("Sniper");
	currentWeapon->setAimModePrimary(	new XAimModeInstantRay());
	currentWeapon->setAimModeSecondary(new XAimModeInstantRay());
	currentWeapon->setIModePrimary(new XIModeAuto(currentWeapon));
	currentWeapon->setIModeSecondary(new XIModeAuto(currentWeapon));
	weapMap[CRC_SNIPER]			= currentWeapon;

	currentWeapon				= new XWeapon("Rockets");
	currentWeapon->setAimModePrimary(new XAimModeInstantRay());
	currentWeapon->setAimModeSecondary(new XAimModeInstantRay());
	currentWeapon->setIModePrimary(new XIModeAuto(currentWeapon));
	currentWeapon->setIModeSecondary(new XIModeAuto(currentWeapon));
	weapMap[CRC_ROCKET_LAUNCHER]= currentWeapon;

	currentWeapon				= new XWeapon("Lightning");
	currentWeapon->setAimModePrimary(new XAimModeInstantRay());
	currentWeapon->setAimModeSecondary(new XAimModeInstantRay());
	currentWeapon->setIModePrimary(new XIModeAuto(currentWeapon));
	currentWeapon->setIModeSecondary(new XIModeAuto(currentWeapon));
	weapMap[CRC_LIGHT_GUN]		= currentWeapon;

	currentWeapon				= new XWeapon("Flak");
	currentWeapon->setAimModePrimary(new XAimModeInstantRay());
	currentWeapon->setAimModeSecondary(new XAimModeInstantRay());
	currentWeapon->setIModePrimary(new XIModeAuto(currentWeapon));
	currentWeapon->setIModeSecondary(new XIModeAuto(currentWeapon));
	weapMap[CRC_FLAK_CANNON]	= currentWeapon;

	currentWeapon = 0;
}

void XWeaponManager::onPushPrimaryFire()
{
	currentWeapon->onPushPrimaryFire();
}

void XWeaponManager::onReleasePrimaryFire()
{
	currentWeapon->onReleasePrimaryFire();
}

void XWeaponManager::onPushSecondaryFire()
{
	currentWeapon->onReleasePrimaryFire();
}

void XWeaponManager::onReleaseSecondaryFire()
{
	currentWeapon->onReleaseSecondaryFire();
}