#pragma once
#include "XAimMode.h"
#include "XIMode.h"


class XWeapon  
{
public:
	XWeapon(char* wname);
	~XWeapon();

	//Initialization methods
	void setAimModePrimary(XAimMode* fPrimary);
	void setAimModeSecondary(XAimMode* fSecondary);
	void setIModePrimary(XIMode* imode);
	void setIModeSecondary(XIMode* imode);

	//Weapon controls
	void onPushPrimaryFire();
	void onReleasePrimaryFire();
	void onPushSecondaryFire();
	void onReleaseSecondaryFire();

	void enableAutoAim();
	void disableAutoAim();
	void setCrosshairSize(unsigned int crossSize);

private:

	bool isAutoAiming;	
	unsigned int crossHairSize;
	int weaponTextureCrc;
	char* name;

	XIMode*	iModePrimary;
	XIMode*	iModeSecondary;
	XAimMode *primary;
	XAimMode *secondary;
};
