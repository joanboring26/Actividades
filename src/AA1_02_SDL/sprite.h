#pragma once
#include <time.h>
#include <string>
#include <SDL.h>
#include <SDL_image.h>
#include <windows.h>
#include <vector>
#include "const.h"
#include "utils.h"
#include "spriteData.h"

class sprite
{
public:
	int id;

	std::string textureName;

	spriteData textureRect, renderRect;
	int textWidth{ 0 }, textHeight{ 0 };
public:

	sprite();

	sprite( std::string givTexturePath, int posX, int posY, int scale);

	void setPos(int givX, int givY);
};