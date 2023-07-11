#pragma once

#include "UObject.h"
#include <d3d8.h>


#define TARGET_HEAD 0
#define TARGET_CHEST 1
#define TARGET_LEGS 2
#define TARGET_MISS 3
#define TARGET_SHOCK_CORE 4

#define SAME_TARGET_MIN_DIST 100.0f


class UTarget : public UObject
{
public:
	UTarget();
	UTarget(D3DXMATRIX* world);
	~UTarget();

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