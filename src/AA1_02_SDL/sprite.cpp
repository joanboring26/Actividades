#include <time.h>
#include <string>
#include <SDL.h>
#include <SDL_image.h>
#include <windows.h>
#include <vector>
#include "const.h"
#include "utils.h"
#include "sprite.h"

#pragma region Sprite

sprite::sprite( std::string givTexturePath, int posX, int posY, int scale) 
{
	textureRect.x = posX;
	textureRect.y = posY;
	textureRect.w /= scale;
	textureRect.h /= posY;
	textWidth /= scale;
	textHeight /= scale;
}

void sprite::setPos(int givX, int givY)
{
	textureRect.x = givX;
	textureRect.y = givY;
}

#pragma endregion