
#include "Xbot.h"
#include "XDodger.h"	

#ifdef TEST
	#include <stdio.h>
	extern FILE* logfile;
#endif


XDodger::XDodger()
{
	memset(&InputDown,     0, sizeof(INPUT));
	memset(&InputUp,       0, sizeof(INPUT));
	memset(&InputOriginalDown,  0, sizeof(INPUT));
	memset(&InputJumpDown,     0, sizeof(INPUT));
	memset(&InputJumpUp,       0, sizeof(INPUT));


	InputUp.type			 = INPUT_KEYBOARD;
	InputUp.ki.dwFlags		 = KEYEVENTF_KEYUP;
	
	InputDown.type			 = INPUT_KEYBOARD;

	InputJumpUp.type		 = INPUT_KEYBOARD;
	InputJumpUp.ki.dwFlags	 = KEYEVENTF_KEYUP;
	InputJumpDown.type		 = INPUT_KEYBOARD;
	
	InputOriginalDown.type		 = INPUT_KEYBOARD;

	dodgePhase				= 0;
	dodgeDelay				= 0;
	dodgeTime				= 0;
	
	dodgeStarted			= false;
	hideKeyPress 			= false;

}   


void XDodger::startDodge()
{
	if(XBot::getXBot()->easyDodgeSwitch == XBot::DODGEMODE_MANUAL)
	{
		if(GetKeyState(0x41) & 0x80)
			setKey(0x41, VK_LEFT ); 

		else if(GetKeyState(VK_LEFT) & 0x80)
			setKey(VK_LEFT,	 0x41); 

		else if(GetKeyState(0x44) & 0x80)
			setKey(0x44, VK_RIGHT ); 

		else if(GetKeyState(VK_RIGHT) & 0x80)
			setKey(VK_RIGHT,	 0x44);

		else if(GetKeyState(0x57) & 0x80)
			setKey(0x57, VK_UP ); 

		else if(GetKeyState(VK_UP) & 0x80)
			setKey(VK_UP,	 0x57); 

		else if(GetKeyState(0x53) & 0x80)
			setKey(0x53, VK_DOWN ); 

		else if(GetKeyState(VK_DOWN) & 0x80)
			setKey(VK_DOWN,	 0x53); 

	
	}
	else
	{
		if(GetKeyState(0x57) & 0x80)
			setKey(0x57, VK_UP ); 

		else if(GetKeyState(VK_UP) & 0x80)
			setKey(VK_UP,	 0x57); 

		else if(GetKeyState(0x53) & 0x80)
			setKey(0x53, VK_DOWN ); 

		else if(GetKeyState(VK_DOWN) & 0x80)
			setKey(VK_DOWN,	 0x53); 
	}



	if(InputOriginalDown.ki.wVk == NULL)
		return;

	dodgePhase		= 1;
	dodgeDelay		= -DODGE_SPEED;
	dodgeTime		= GetTickCount();
	dodgeStarted	= true;
	hideKeyPress    = true;
}

void XDodger::executeDodge()
{
	
	if(!dodgeStarted)
		return;
	
	if( (GetTickCount() - dodgeTime) > DODGE_SPEED + dodgeDelay)
	{

		switch(dodgePhase)
		{
				
			case 1: SendInput(1, &InputDown,sizeof(INPUT));
					dodgeDelay = 0;	
					break;
			
			case 2: SendInput(1, &InputUp,	sizeof(INPUT));	
					break;
			
			case 3: SendInput(1, &InputDown,sizeof(INPUT));
					break;
			
			case 4: SendInput(1, &InputUp,	sizeof(INPUT));
					dodgeDelay = 220;
					hideKeyPress = false;

					if(XBot::getXBot()->easyDodgeSwitch != XBot::DODGEMODE_MANUAL)
					{
						dodgeDelay = 300;
						dodgePhase = 6;
					}

					break;
			
			case 5: SendInput(1, &InputJumpDown,sizeof(INPUT));
					break;
			
			case 6: SendInput(1, &InputJumpUp,sizeof(INPUT));
					break;
			
			case 7: if(GetKeyState(InputOriginalDown.ki.wVk) & 0x80)
						SendInput(1, &InputOriginalDown,sizeof(INPUT));
					dodgeDelay = 0;	
					break;
			
			case 8:	dodgeStarted = false;	
					clear();
					break;
		}

		dodgeTime = GetTickCount();

		dodgePhase++;
	}

}

void XDodger::setKey(UINT keyToRelease, UINT keyDodge)
{
	if(!dodgeStarted)
	{
		InputDown.ki.wVk			= keyDodge;
		InputUp.ki.wVk				= keyDodge;
		InputOriginalDown.ki.wVk	= keyToRelease;
	}
}

void XDodger::clear()
{	
	if(!dodgeStarted)
	{
		InputDown.ki.wVk			= NULL;
		InputUp.ki.wVk				= NULL;
		InputOriginalDown.ki.wVk	= NULL;
		dodgePhase					= 1;
		hideKeyPress				= false;
	}	
}

		
void XDodger::setJumpKey(UINT key)
{
	InputJumpUp.ki.wVk		 = key;
	InputJumpDown.ki.wVk	 = key;
}