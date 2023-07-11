#include "XWeapon.h"

XWeapon::XWeapon(char* wname)
{
	name = wname;
	primary = 0;
	secondary = 0;
}

XWeapon::~XWeapon()
{
	if(primary)
		delete primary;

	if(secondary)
		delete secondary;
}

void XWeapon::setFireModePrimary(XFireMode* fPrimary)
{
	if(primary)
		delete primary;

	primary = fPrimary;
}

void XWeapon::setFireModeSecondary(XFireMode* fSecondary)
{
	if(secondary)
		delete secondary;

	secondary = fSecondary;
}