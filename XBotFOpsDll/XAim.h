#pragma once
#include <windows.h>
#include <D3dx8core.h>


#define AIM_SPEED 500 //pixel per milliseconds
#define SMOOT_FACTOR 10

class UTarget;
class XBot;

class XAim
{
public:
	XAim();
	~XAim();

	UINT fireMode;
	bool lineOfFire;
	bool process(long *shiftX, long *shiftY);
	void clear();
	void compensateMovement(UTarget* target);
	void addWeaponOffset(UTarget* target);
	void instantAim(UTarget* target);

private:

	UINT ignoreFactor;
	UINT smoothFactor;
	D3DXVECTOR2 shiftVector;
	D3DXVECTOR2 originVector;

};