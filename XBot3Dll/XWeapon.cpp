#include "XWeapon.h"

XWeapon::XWeapon(char* wname)
{
	name = wname;
	primary = 0;
	secondary = 0;
	crossHairSize = 40;		//caricare da script
	weaponTextureCrc = 0;	//caricare da script
	isAutoAiming = false;	//caricare da script
}

XWeapon::~XWeapon()
{
	if(primary)
		delete primary;

	if(secondary)
		delete secondary;
}

void XWeapon::setAimModePrimary(XAimMode* fPrimary)
{
	if(primary)
		delete primary;

	primary = fPrimary;
}

void XWeapon::setAimModeSecondary(XAimMode* fSecondary)
{
	if(secondary)
		delete secondary;

	secondary = fSecondary;
}

void XWeapon::onPushPrimaryFire()
{
	iModePrimary->onPush();
}

void XWeapon::onReleasePrimaryFire()
{
	iModePrimary->onRelease();
}

void XWeapon::onPushSecondaryFire()
{
	iModeSecondary->onPush();
}

void XWeapon::onReleaseSecondaryFire()
{
	iModeSecondary->onRelease();
}

void XWeapon::setIModePrimary(XIMode* imode)
{
	if(iModePrimary)
		delete iModePrimary;

	iModePrimary = imode;
}

void XWeapon::setIModeSecondary(XIMode* imode)
{
	if(iModeSecondary)
		delete iModeSecondary;

	iModeSecondary = imode;
}
//Todo: aggiungere controllo
void XWeapon::enableAutoAim()
{
	isAutoAiming = true;
}

void XWeapon::disableAutoAim()
{
	isAutoAiming = false;
}

void XWeapon::setCrosshairSize(unsigned int crossSize)
{
	crossHairSize = crossSize;
}