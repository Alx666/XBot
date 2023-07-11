#include "UTarget.h"




UTarget::UTarget() : UObject()
{
	
	type = -1;
	shkCoreRsvrdFlag = -1; //TEST
	isValid = false;
	isInRange = false;
	distance = 0;
	distance2D = 0;
	speed = 0; // VALORE IN TEST
	directionAngle = 0;
	directionContinuity = 0.000001f;;
	direction.x = 0;
	direction.y = 0;
	direction.z = 0;
	aimAdjust.x = 0;
	aimAdjust.y = 0;
	aimAdjust.z = 0;
	bodyVector.x = 0;
	bodyVector.y = 0;
	bodyVector.z = 0;
	lastWorldPosition.x = 0;
	lastWorldPosition.y = 0;
	lastWorldPosition.z = 0;
}

UTarget::UTarget(D3DXMATRIX* world) : UObject(world)
{
	
	type = -1;
	shkCoreRsvrdFlag = -1; //TEST
	isValid = false;
	distance = 0;
	distance2D = 0;
	speed = 0; // VALORE IN TEST
	directionAngle = 0;
	directionContinuity = 0.000001f;;
	direction.x = 0;
	direction.y = 0;
	direction.z = 0;
	aimAdjust.x = 0;
	aimAdjust.y = 0;
	aimAdjust.z = 0;
	bodyVector.x = 0;
	bodyVector.y = 0;
	bodyVector.z = 0;
	lastWorldPosition.x = 0;
	lastWorldPosition.y = 0;
	lastWorldPosition.z = 0;
}

UTarget::~UTarget()
{
}

void UTarget::setType(char TYPE)
{
	type=TYPE;
}

void UTarget::reset()
{
	type = -1;
	isValid = false;
	distance = 0;
	speed = 0; // VALORE IN TEST
	direction.x = 0;
	direction.y = 0;
	direction.z = 0;
	aimAdjust.x = 0;
	aimAdjust.y = 0;
	aimAdjust.z = 0;
	bodyVector.x = 0;
	bodyVector.y = 0;
	bodyVector.z = 0;
	lastWorldPosition.x = 0;
	lastWorldPosition.y = 0;
	lastWorldPosition.z = 0;
}

bool UTarget::isSameTarget(D3DMATRIX* matrix, float offset)
{

	D3DXVECTOR4 position;
	UTarget objToTest((D3DXMATRIX*)matrix);

	//objToTest.directionAngle = 57.2957795f * acos(tPrimary->direction.x);
	
	/*D3DXVECTOR3 myVec(0, 0, 0);
	D3DXVec3Transform(&objToTest.currentWorldPosition, &myVec, (D3DXMATRIX*)matrix);*/

	if(getDistanceFrom(&objToTest)<SAME_TARGET_MIN_DIST+offset /*&& abs(directionAngle - objToTest.directionAngle)< 20.0f*/)//valore da testare
		return true;
	else 
		return false;

}

