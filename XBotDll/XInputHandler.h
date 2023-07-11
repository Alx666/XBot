#pragma once

#define DIRECTINPUT_VERSION 0x0800
#include <dinput.h>




class XInputHandler
{
	public:
		
		XInputHandler() {
							releaseAltFireShock			= false;
							releaseAltFireShockDelay	= 0;
							rocket2ndFireRelease		= false;
							release2ndRocketFireDelay	= 0;
							HideAltFirePress			= false;

						};

		bool HideAltFirePress;
		bool releaseAltFireShock;
		bool rocket2ndFireRelease;
		UINT releaseAltFireShockDelay;
		UINT release2ndRocketFireDelay;


		void onMousePrimDown(LPDWORD pdwInOut);
		void onMousePrimUp(LPDWORD pdwInOut);
		void onMouseSecDown(LPDWORD pdwInOut);
		void onSecFireKeyDown(WPARAM* wParam);
		void onSecDown(UINT* out);
		void onSecFireUp(UINT* wParam);
		void onJumpDown(UINT* wParam);
};