#include "XIModeAuto.h"
#include "XWeapon.h"

XIModeAuto::XIModeAuto(XWeapon* owner) : XIMode(owner)
{

}

XIModeAuto::~XIModeAuto()
{

}

void XIModeAuto::onPush()
{
	parentWeapon->enableAutoAim();
}

void XIModeAuto::onRelease()
{
	parentWeapon->disableAutoAim();
}