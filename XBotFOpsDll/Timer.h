#pragma once

class Timer
{
	
	public:
		Timer();
		~Timer() {};

		unsigned int maxTime;
		unsigned int tickCount;
	
		int getTime(int* millis = 0);
		void setCount(unsigned int nValue);
		void restart();
};