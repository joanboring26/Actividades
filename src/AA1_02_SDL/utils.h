#pragma once
#include <time.h>

struct gameTime
{
	clock_t lastTime;
	float timeDown;
	float deltaTime;

	gameTime()
	{
		lastTime = clock();
		deltaTime = 0;
	}

	void startTimer(float totalTime)
	{
		deltaTime = (clock() - lastTime);
		lastTime = clock();
		deltaTime /= CLOCKS_PER_SEC;
		timeDown -= deltaTime; // Update timer
	}
};