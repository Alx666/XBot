#pragma once

class XWeapon;
class XIMode  
{
public:
	XIMode(XWeapon* owner);
	virtual ~XIMode();

	virtual void onPush()		= 0;
	virtual void onRelease()	= 0;

protected:
	XWeapon* parentWeapon;
};
