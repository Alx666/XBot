#include "XBot.h"
#include "UPickup.h"




UPickup::UPickup(LPDIRECT3DDEVICE8 pD3DDevice8Ref, UTarget* currentplayer, int pk_type) : UObject()
{
	pD3DDevice8 = pD3DDevice8Ref;
	currentPlayer = currentplayer;
	gotPosition = false;
	type = pk_type;
}

UPickup::~UPickup()
{
}

void UPickup::setCoords()
{


	D3DMATRIX matrix;
	pD3DDevice8->GetTransform(D3DTS_WORLD,&matrix);

	D3DXVECTOR3 myVec(0, 0, 0);
	D3DXVec3Transform(&currentWorldPosition, &myVec, (D3DXMATRIX*)&matrix);

	gotPosition = true;
}

void UPickup::tryToTake()
{

	if(!gotPosition)
		return;

	if(currentPlayer->getDistanceFrom(this) < MAX_TAKE_DISTANCE)
	{
		XBot* xbot = XBot::getXBot();

		switch(type)
		{
		case PK_SHIELD:  xbot->resetShield100Timer(true);break;
		case PK_DDAMAGE: xbot->resetDDamageTimer(true);  break;
		case PK_REDEEM:  xbot->resetRedeemTimer(true);   break;
		}

		gotPosition = false;
	}
}



