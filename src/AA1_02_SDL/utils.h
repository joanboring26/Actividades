#pragma once
#include <time.h>

struct timer
{
	clock_t lastTime;
	float timeDown;
	float deltaTime;

	timer()
	{
		timeDown = 0;
		deltaTime = 0;
	}

	timer(float givTime)
	{
		lastTime = givTime;
		deltaTime = 0;
	}

	bool updateTimer()
	{
		deltaTime = (clock() - lastTime);
		lastTime = clock();
		deltaTime /= CLOCKS_PER_SEC;
		timeDown -= deltaTime; // Update timer
		if (timeDown <= 0)
		{
			return true;
		}
		return false;
	}
};