#pragma once

#define DIRECTINPUT_VERSION 0x0800
#include <dinput.h>




class XInputHandler
{
	public:
		
		XInputHandler() {};

		void onMousePrimDown(LPDWORD dwData, LPDWORD pdwInOut);
		void onMousePrimUp(LPDWORD dwData, LPDWORD pdwInOut);
		void onSecFireKeyDown();
		void onSecFireKeyUp();

		void mouseSecOps(LPDWORD dwData, LPDWORD pdwInOut);
};