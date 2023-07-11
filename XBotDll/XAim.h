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
	void parabolicAim(UTarget* target, float bulletSpeed, float V0);
	void linkGunAim(UTarget* target);
	void ballisticAim(UTarget* target, UINT bulletSpeed);
	void rocketAim(UTarget* target, UINT bulletSpeed);
	void compensatePing(UTarget* target);

	//TEST CODE
	void compensateRay(UTarget* target);
	int rayOffset;
	int lastRayOffset;
	bool rayCompensationSet;

private:

	UINT ignoreFactor;
	UINT smoothFactor;
	D3DXVECTOR2 shiftVector;
	D3DXVECTOR2 originVector;

};