#pragma once

#define DODGE_DELAY		10
#define DODGE_SPEED		10

#include <windows.h>
#include <winuser.h>


class XDodger
{
	public:

		XDodger();
	

		void executeDodge();
		void startDodge();
		void setKey(UINT keyToRelease, UINT keyDodge);
		void clear();
		void setJumpKey(UINT key);

		int getReleaseKey()		 { return InputOriginalDown.ki.wVk;};
		bool isDodgeStarted()	 { return dodgeStarted;};
		BOOL hideKeyPress;	

	private:

		UINT dodgeDelay;
		UINT dodgeTime;
	
		INPUT InputUp;
		INPUT InputDown;
		INPUT InputJumpUp;
		INPUT InputJumpDown;
		INPUT InputOriginalDown;
	

		BOOL dodgeStarted;
		BOOL dodgePhase;

};