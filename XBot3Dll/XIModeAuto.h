#pragma once
#include "XIMode.h"

class XIModeAuto  : public XIMode
{
public:
	XIModeAuto(XWeapon* owner);
	virtual ~XIModeAuto();
	void onPush();
	void onRelease();
};

