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

struct animatedSpriteSet
{
	Vector2 p1;
	Vector2 p2;

	animatedSpriteSet(int x1, int y1, int x2, int y2)
	{
		p1.x = x1;
		p1.y = y1;
		p2.x = x2;
		p2.y = y2;
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

struct sprite
{
	SDL_Renderer *renderer;
	SDL_Texture *pTexture;
	SDL_Rect textureRect, renderRect;
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
		SDL_RenderCopy(renderer, pTexture, &textureRect, &renderRect);
	}

	void setPos(int givX, int givY)
	{
		textureRect.x = givX;
		textureRect.y = givY;
	}

};

struct animatedSprite
{
	SDL_Rect frameRect, playerPosition;
	sprite *animSprite;
	int textWidth{ 0 }, textHeight{ 0 }, frameWidth{ 0 }, frameHeight{ 0 };
	int frameTime = 0;
	int totFrames;

	animatedSprite()
	{

	}

	animatedSprite(SDL_Renderer *m_renderer, std::string givTexturePath, int givX, int givY,int givTotFrames, int givHorFrames, int givVerFrames)
	{
		animSprite = new sprite(m_renderer, givTexturePath, givX, givY, 1);
		SDL_QueryTexture(animSprite->pTexture, NULL, NULL, &textWidth, &textHeight); //Al fer &textWidth i &frameHeight aquestes s'omplen amb els valors de tamany de la textura
		frameWidth = textWidth / givHorFrames;
		frameHeight = textHeight / givVerFrames;
		animSprite->renderRect.x = animSprite->renderRect.y = 0;
		animSprite->textureRect.x = animSprite->textureRect.y = 0;
		animSprite->renderRect.h = animSprite->textureRect.h = frameHeight;
		animSprite->renderRect.w = animSprite->textureRect.w = frameWidth;
	}

	animatedSprite(sprite *givAnimSprite, int givTotFrames, int givHorFrames, int givVerFrames)
	{
		animSprite = givAnimSprite;
		SDL_QueryTexture( animSprite->pTexture, NULL, NULL, &textWidth, &textHeight); //Al fer &textWidth i &frameHeight aquestes s'omplen amb els valors de tamany de la textura
		frameWidth = textWidth / givHorFrames;
		frameHeight = textHeight / givVerFrames;
		animSprite->renderRect.x = animSprite->renderRect.y = 0;
		animSprite->textureRect.x = animSprite->textureRect.y = 0;
		animSprite->renderRect.h = animSprite->textureRect.h = frameHeight;
		animSprite->renderRect.w = animSprite->textureRect.w = frameWidth;
	}

	void updateSprite()
	{
		frameTime++;
		if (FPS / frameTime <= 10)
		{
			frameTime = 0;
			animSprite->textureRect.x += frameWidth;
			if (animSprite->textureRect.x >= textWidth)
			{
				animSprite->textureRect.x = 0;
			}
		}
	}

	void renderSprite()
	{
		animSprite->renderSprite();
	}

	void setPos(int givX, int givY)
	{
		animSprite->renderRect.x = givX;
		animSprite->renderRect.y = givY;
	}


	animatedSprite& operator =(const animatedSprite &otherSprite)
	{
		animSprite->renderer = otherSprite.animSprite->renderer;
		animSprite->pTexture = otherSprite.animSprite->pTexture;
		animSprite->textureRect = otherSprite.frameRect;
		animSprite->renderRect = otherSprite.playerPosition;
		textWidth = otherSprite.textWidth;
		textHeight = otherSprite.textHeight;
		frameWidth = otherSprite.frameWidth;
		frameHeight = otherSprite.frameHeight;
		frameTime = otherSprite.frameTime;
		totFrames = otherSprite.totFrames;

		return *this;
	}

};