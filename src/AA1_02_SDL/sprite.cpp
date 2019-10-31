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

sprite::sprite(SDL_Renderer *m_renderer, std::string givTexturePath, int posX, int posY, int scale)
{
	renderer = m_renderer;
	pTexture = IMG_LoadTexture(renderer, givTexturePath.c_str());
	SDL_QueryTexture(pTexture, NULL, NULL, &textWidth, &textHeight);
	textWidth /= scale;
	textHeight /= scale;
	textureRect = SDL_Rect{ posX, posY, textWidth, textHeight };
}

void sprite::renderSprite()
{
	SDL_RenderCopy(renderer, pTexture, &textureRect, &renderRect);
}

void sprite::setPos(int givX, int givY)
{
	textureRect.x = givX;
	textureRect.y = givY;
}

#pragma endregion