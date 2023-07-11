#pragma once
#include "XFireMode.h"
//#include <stdio.h> DELME

class XWeapon  
{
public:
	XWeapon(char* wname);
	~XWeapon();

	void setFireModePrimary(XFireMode* fPrimary);
	void setFireModeSecondary(XFireMode* fSecondary);

private:
	int crc;
	char* name;
	XFireMode *primary;
	XFireMode *secondary;

};
