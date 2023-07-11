#pragma once

#include <d3d8.h>
#include "UTarget.h"

#define MAX_TAKE_DISTANCE 100.0f

class UPickup : public UObject
{
public:
	enum {PK_SHIELD, PK_DDAMAGE, PK_REDEEM};

	UPickup(LPDIRECT3DDEVICE8 pD3DDevice8Ref, UTarget* currentplayer, int pk_type);
	~UPickup();

	void setCoords();
	void tryToTake();

private:
	LPDIRECT3DDEVICE8	pD3DDevice8;
	UTarget* currentPlayer;

	bool gotPosition;
	UINT index;
	int type;
};