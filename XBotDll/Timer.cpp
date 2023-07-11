#include "Timer.h"
#include <windows.h>

Timer::Timer()
{
	maxTime   = 0;
	tickCount = 0;
}

void Timer::restart()
{
	tickCount = GetTickCount();

}

int Timer::getTime(int* millis)
{
	if(tickCount == 0)
		return maxTime;
	
	unsigned int currentTime	= GetTickCount();
	int time					= maxTime - ((currentTime-tickCount)/1000);

	if (millis != NULL)
	{
		int intTime	= (currentTime-tickCount)/1000;
		*millis		= intTime - (currentTime-tickCount);
	}
	
	if(time>0)
		return  time;
	else return 0;
}

void Timer::setCount(UINT nValue)
{
	maxTime = nValue;
}

