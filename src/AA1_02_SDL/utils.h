#pragma once
#include <time.h>
#include <string>
#include <SDL.h>
#include <SDL_image.h>
#include <windows.h>
#include <vector>
#include "const.h"

struct Vector2
{
	int x;
	int y;
	Vector2()
	{
		x = 0;
		y = 0;
	}
	Vector2(int valX, int valY)
	{
		x = valX;
		y = valY;
	}
};

struct Transform
{
	Vector2 position;
	Vector2 scale;

	Transform()
	{

	}

	Transform(int posX, int posY, int scaleX, int scaleY)
	{
		position.x = posX;
		position.y = posY;
		scale.x = scaleX;
		scale.y = scaleY;
	}
};

struct inputs
{
	bool *keyboard = new bool[(int)keyPressed::COUNT];

	int getKeyboardInputs()
	{
		int inputs = 0;
		inputs += keyboard[(int)keyPressed::ESC] = GetAsyncKeyState(VK_ESCAPE);
		inputs += keyboard[(int)keyPressed::SPACE] = GetAsyncKeyState(VK_SPACE);
		inputs += keyboard[(int)keyPressed::UP] = GetAsyncKeyState(VK_UP);
		inputs += keyboard[(int)keyPressed::DOWN] = GetAsyncKeyState(VK_DOWN);
		inputs += keyboard[(int)keyPressed::LEFT] = GetAsyncKeyState(VK_LEFT);
		inputs += keyboard[(int)keyPressed::RIGHT] = GetAsyncKeyState(VK_RIGHT);
		inputs += keyboard[(int)keyPressed::W] = GetAsyncKeyState(0x57);
		inputs += keyboard[(int)keyPressed::A] = GetAsyncKeyState(0x41);
		inputs += keyboard[(int)keyPressed::S] = GetAsyncKeyState(0x53);
		inputs += keyboard[(int)keyPressed::D] = GetAsyncKeyState(0x44);
		return inputs;
	}
};

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
		timeDown = givTime * 1000;
		deltaTime = 0;
	}

	bool updateTimer()
	{
		deltaTime = (clock() - lastTime);
		//std::cout << "Delta time" << std::endl << deltaTime << std::endl;
		lastTime = clock();
		//std::cout << "Last time" << std::endl << lastTime << std::endl;
		deltaTime /= CLOCKS_PER_SEC;
		//std::cout << "Delta Time" << std::endl << deltaTime << std::endl;
		timeDown -= deltaTime; // Update timer
		//std::cout << "Time Down" << std::endl << timeDown <<std::endl;
		if (timeDown <= 0)
		{
			return true;
		}
		return false;
	}
};