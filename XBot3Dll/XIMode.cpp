#include "XIMode.h"
#include "XWeapon.h"

XIMode::XIMode(XWeapon* owner)
{
	parentWeapon = owner;
}

XIMode::~XIMode()
{

}
