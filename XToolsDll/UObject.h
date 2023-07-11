#pragma once

#include <d3d8.h>
#include <d3dx8math.h>

struct modelStreamData
{
	D3DVECTOR vec;
	FLOAT unknown[5];
};

class UObject
{
public:
	UObject();
	UObject(D3DXMATRIX* world);
	~UObject();

	D3DXVECTOR3 screenCoords;
	D3DXVECTOR4 currentWorldPosition;


	double getDistanceFrom(UObject* obj);
	int	   get2dDistanceFrom(UObject* obj);
	
	static void getMiddlePoint(D3DVECTOR *pVector, unsigned int MinIndex, unsigned int NumVertices, unsigned int StartIndex);
};