#pragma once

#include <d3d8.h>
#include "Timer.h"

struct D3DVERTEX
{
	float	x,
			y,
			z;
	DWORD	dwColor;
};





struct modelStreamData
{
	D3DVECTOR vec;
	FLOAT unknown[5];
};