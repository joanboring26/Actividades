#pragma once
#include <time.h>
#include <SDL.h>
#include <SDL_image.h>
#include <windows.h>
#include "const.h"

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

struct animatedSprite
{
	SDL_Renderer *renderer;
	SDL_Texture *pTexture;
	SDL_Rect playerRect, playerPosition;
	int textWidth{ 0 }, textHeight{ 0 }, frameWidth{ 0 }, frameHeight{ 0 };
	int frameTime = 0;
	int totFrames;

	animatedSprite()
	{

	}

	animatedSprite(SDL_Renderer *m_renderer, std::string givTexturePath,int givTotFrames, int givHorFrames, int givVerFrames)
	{
		renderer = m_renderer;
		pTexture = IMG_LoadTexture(renderer, givTexturePath.c_str());
		SDL_QueryTexture(pTexture, NULL, NULL, &textWidth, &textHeight); //Al fer &textWidth i &frameHeight aquestes s'omplen amb els valors de tamany de la textura
		frameWidth = textWidth / givHorFrames;
		frameHeight = textHeight / givVerFrames;
		playerPosition.x = playerPosition.y = 0;
		playerRect.x = playerRect.y = 0;
		playerPosition.h = playerRect.h = frameHeight;
		playerPosition.w = playerRect.w = frameWidth;
	}

	void updateSprite()
	{
		frameTime++;
		if (FPS / frameTime <= 9)
		{
			frameTime = 0;
			playerRect.x += frameWidth;
			if (playerRect.x >= textWidth)
			{
				playerRect.x = 0;
			}
		}
	}

	void renderSprite()
	{
		SDL_RenderCopy(renderer, pTexture, &playerRect, &playerPosition);
	}

	void setSpritePos(int givX, int givY)
	{
		playerPosition.x = givX;
		playerPosition.y = givY;
	}


	animatedSprite& operator =(const animatedSprite &otherSprite)
	{
		renderer = otherSprite.renderer;
		pTexture = otherSprite.pTexture;
		playerRect = otherSprite.playerRect;
		playerPosition = otherSprite.playerPosition;
		textWidth = otherSprite.textWidth;
		textHeight = otherSprite.textHeight;
		frameWidth = otherSprite.frameWidth;
		frameHeight = otherSprite.frameHeight;
		frameTime = otherSprite.frameTime;
		totFrames = otherSprite.totFrames;

		return *this;
	}

};

struct sprite
{
	SDL_Renderer *renderer;
	SDL_Texture *pTexture;
	SDL_Rect textureRect;
	int textWidth{ 0 }, textHeight{ 0 };
	int frameTime = 0;
	int totFrames;

	sprite()
	{

	}

	sprite(SDL_Renderer *m_renderer, std::string givTexturePath, int posX, int posY,int scale)
	{
		renderer = m_renderer;
		pTexture = IMG_LoadTexture(renderer, givTexturePath.c_str());
		SDL_QueryTexture(pTexture, NULL, NULL, &textWidth, &textHeight);
		textWidth /= scale;
		textHeight /= scale;
		textureRect = SDL_Rect{posX, posY, textWidth, textHeight};
	}

	void renderSprite()
	{
		SDL_RenderCopy(renderer, pTexture, nullptr, &textureRect);
	}

	void setSpritePos(int givX, int givY)
	{
		textureRect.x = givX;
		textureRect.y = givY;
	}
};