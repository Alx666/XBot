#include <d3dx9math.h>
#include <stdio.h>
#include <windows.h>


D3DXVECTOR4 compute(const D3DXVECTOR4 player, const D3DXVECTOR4 aimingAt);
bool verify(D3DXVECTOR4 player, D3DXVECTOR4 target, D3DXVECTOR4 fixedTarget, float* res);
void build(D3DXVECTOR4* playerAbsolute, D3DXVECTOR4* targetAbsolute);
void printVector(D3DXVECTOR4 vector, char* name);
float getAngle(const D3DXVECTOR4 v1, const D3DXVECTOR4 v2);



//funziona bene per x e y risolvere la z

D3DXVECTOR4 compute(const D3DXVECTOR4 player, const D3DXVECTOR4 aimingAt)
{

	D3DXVECTOR4 playerPosition = player;						//the absolute player location
	D3DXVECTOR4 targetRelative = -(aimingAt - playerPosition);	//the player position relative to the target location
	targetRelative.w = 1;

	D3DXVECTOR4 pre;	//DEBUG
	D3DXVECTOR4 post;	//DEBUG


	D3DXMATRIX rotateMatrix;
	D3DXMatrixRotationZ(&rotateMatrix, (90*0.0174532925));				//Creates a matrix that rotate a vector of 90 degrees
	D3DXVec4Transform(&targetRelative, &targetRelative, &rotateMatrix);	//Rotates the original vector, to take another orthogonal
	D3DXVec4Normalize(&targetRelative, &targetRelative);

	targetRelative *= 20;


	return targetRelative + aimingAt;
}

void build(D3DXVECTOR4* playerAbsolute, D3DXVECTOR4* targetAbsolute)
{
	targetAbsolute->x = ((float)(rand()%1500)) + ((float)(rand()%10000)) / 10000;
	targetAbsolute->y = ((float)(rand()%1500)) + ((float)(rand()%10000)) / 10000;
	targetAbsolute->z = ((float)(rand()%1500)) + ((float)(rand()%10000)) / 10000;
	targetAbsolute->w = 1;

	playerAbsolute->x = ((float)(rand()%1500)) + ((float)(rand()%10000)) / 10000;
	playerAbsolute->y = ((float)(rand()%1500)) + ((float)(rand()%10000)) / 10000;
	playerAbsolute->z = ((float)(rand()%1500)) + ((float)(rand()%10000)) / 10000;
	playerAbsolute->w = 1;
}

bool verify(D3DXVECTOR4 player, D3DXVECTOR4 target, D3DXVECTOR4 fixedTarget, float* res)
{
	D3DXVECTOR4 playerRelative = -(target - player);
	D3DXVECTOR4 fixedTargetRelative = -(target - fixedTarget);
	
	*res = D3DXVec4Dot(&playerRelative, &fixedTargetRelative);

	if(*res < 1 && *res > -1)
		return true;
	else
		return false;	
}

void printVector(D3DXVECTOR4 vector, char* name)
{
	printf("%s.x:%f\n%s.y:%f\n%s.z:%f\n\n", name, vector.x, name, vector.y, name, vector.z);
}


float getAngle(const D3DXVECTOR4 v1, const D3DXVECTOR4 v2)
{
	float beta  = acos(D3DXVec4Dot(&v1, &v2) / (D3DXVec4Length(&v1)*D3DXVec4Length(&v2)));
	float degrees = beta*57.2957795;

	return degrees;
}


void main()
{
	
	D3DXVECTOR4 fireLocation;
	D3DXVECTOR4 aimingLocation;
	D3DXVECTOR4 playerLocation;
	float result = 0;

	srand(666);
	for(int i = 0; i<500; i++)
	{
		build(&playerLocation, &aimingLocation);

		fireLocation = compute(playerLocation, aimingLocation);

		if(verify(playerLocation, aimingLocation, fireLocation, &result))
		{
			printf("---------------------------\n");
			printVector(playerLocation, "player");
			printVector(aimingLocation, "target");
			printVector(fireLocation, "result");
			printf("test = %f, Success!\n", result);
			printf("---------------------------\n");

		}
		else
		{
			printf("---------------------------\n");
			printVector(playerLocation, "player");
			printVector(aimingLocation, "target");
			printVector(fireLocation, "result");
			printf("test = %f, Error!\n", result);
			printf("---------------------------\n");
			break;
		}

		//Sleep(50);
	}	
	
}