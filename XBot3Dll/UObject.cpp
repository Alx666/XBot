#include <math.h>
#include "UObject.h"
#include "FAKE_IDirect3DDevice8.h"
#include "structs.h"

extern IDirect3DDevice8 *pD3DDevice8 ;

UObject::UObject()
{
	screenCoords.x = 0;
	screenCoords.y = 0;
	screenCoords.z = 0;

	currentWorldPosition.x = 0;
	currentWorldPosition.y = 0;
	currentWorldPosition.z = 0;
}

UObject::UObject(D3DXMATRIX* world)
{
	D3DXVECTOR3 myVec(0, 0, 0);
	D3DXVec3Transform(&currentWorldPosition, &myVec, world);

}


UObject::~UObject()
{
}

double UObject::getDistanceFrom(UObject* obj)
{
	return fabs(sqrt( ((obj->currentWorldPosition.x - currentWorldPosition.x)*(obj->currentWorldPosition.x - currentWorldPosition.x)) 
				+ ((obj->currentWorldPosition.y - currentWorldPosition.y)*(obj->currentWorldPosition.y - currentWorldPosition.y)) 
				+ ((obj->currentWorldPosition.z - currentWorldPosition.z)*(obj->currentWorldPosition.z - currentWorldPosition.z)))); 

}

int	UObject::get2dDistanceFrom(UObject* obj)
{
return fabs(sqrt( ((obj->screenCoords.x - screenCoords.x)*(obj->screenCoords.x - screenCoords.x)) 
				+ ((obj->screenCoords.y - screenCoords.y)*(obj->screenCoords.y - screenCoords.y)))); 


}


void UObject::getMiddlePoint(D3DVECTOR *pVector, unsigned int MinIndex, unsigned int NumVertices, unsigned int StartIndex)
{
	HRESULT Result;
	IDirect3DVertexBuffer8 *pStreamData = NULL;
	UINT Stride;
	pD3DDevice8->GetStreamSource(0, &pStreamData, &Stride);
	IDirect3DIndexBuffer8 *pIndexBuffer = NULL;
	UINT BaseVertexIndex = 0;
	pD3DDevice8->GetIndices(&pIndexBuffer, &BaseVertexIndex);
	BYTE *pIndexData = NULL;
	Result = pIndexBuffer->Lock(StartIndex * sizeof(WORD), sizeof(WORD) * NumVertices, &pIndexData, D3DLOCK_READONLY);
	WORD *pIndexBuf = (WORD*)pIndexData;
	unsigned int MaxVertex = 0;

	for (unsigned int iVertex = 0; iVertex < NumVertices; iVertex++)
	{
		if (*pIndexBuf > MaxVertex)
			MaxVertex = *pIndexBuf;
		pIndexBuf++;
	}

	pIndexBuffer->Unlock();
	pIndexBuffer->Release();
	BYTE *pData = NULL;
	Result = pStreamData->Lock((BaseVertexIndex + MinIndex) * Stride, (MaxVertex - MinIndex) * Stride, &pData, D3DLOCK_READONLY);
	D3DVECTOR high, low;
	modelStreamData *pTemp = (modelStreamData*)pData;
	high.x = ((D3DVECTOR*)(pTemp))->x;
	high.y = ((D3DVECTOR*)(pTemp))->y;
	high.z = ((D3DVECTOR*)(pTemp))->z;
	low = high;

	for (unsigned int iVector = 1; iVector < NumVertices; iVector++)
	{
		D3DVECTOR *pVector = (D3DVECTOR*)pTemp;
		if (pVector->x < low.x)
			low.x = pVector->x;
		if (pVector->x > high.x)
			high.x = pVector->x;
		if (pVector->y < low.y)
			low.y = pVector->y;
		if (pVector->y > high.y)
			high.y = pVector->y;
		if (pVector->z < low.z)
			low.z = pVector->z;
		if (pVector->z > high.z)
			high.z = pVector->z;
		pTemp++;
	}

	pVector->x = (low.x + high.x) / 2;
	pVector->y = (low.y + high.y) / 2;
	pVector->z = (low.z + high.z) / 2;
	pStreamData->Unlock();
	pStreamData->Release();
}