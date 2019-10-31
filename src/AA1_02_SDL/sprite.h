#pragma once
#include <time.h>
#include <string>
#include <SDL.h>
#include <SDL_image.h>
#include <windows.h>
#include <vector>
#include "const.h"
#include "utils.h"

class sprite
{
public:
	SDL_Renderer *renderer;
	SDL_Texture *pTexture;
	SDL_Rect textureRect, renderRect;
	int textWidth{ 0 }, textHeight{ 0 };
private:
	int frameTime = 0;
	int totFrames;
public:

	sprite()
	{

	}

	sprite(SDL_Renderer *m_renderer, std::string givTexturePath, int posX, int posY, int scale);

	void renderSprite();

	void setPos(int givX, int givY);
};