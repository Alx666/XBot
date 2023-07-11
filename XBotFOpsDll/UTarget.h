#pragma once

#include "UObject.h"
#include <d3d8.h>


#define SAME_TARGET_MIN_DIST 100.0f


class UTarget : public UObject
{
public:
	UTarget();
	UTarget(D3DXMATRIX* world);
	~UTarget();

	enum {TARGET_GRANADE_HE,TARGET_GRANADE_FLASH,TARGET_GRANADE_NAPALM,TARGET_GRANADE_RSMOKE,TARGET_GRANADE_YSMOKE,
		  TARGET_HEAD,TARGET_CHEST,TARGET_LEGS,TARGET_MISS};


	char		shkCoreRsvrdFlag; //TEST
	char		type;
	bool		isValid;
	bool		isInRange;
	double		distance;
	int			distance2D;
	double		speed;
	float		directionAngle;
	float		directionContinuity;
	D3DXVECTOR3	adjustedScreenCoords;
	D3DXVECTOR3	direction;
	D3DXVECTOR3 aimAdjust;
	D3DXVECTOR4 bodyVector;
	D3DXVECTOR4 lastWorldPosition;

	void setType(char TYPE);
	bool isSameTarget(D3DMATRIX* matrix, float offset=0);
	void reset();
};