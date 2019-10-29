#pragma once
#include <time.h>
#include <string>
#include <SDL.h>
#include <SDL_image.h>
#include <windows.h>
#include <vector>
#include "const.h"
#include "utils.h"

class animatedSpriteSet
{
public:
	Vector2 p1;
	Vector2 p2;

	animatedSpriteSet()
	{

	}

	animatedSpriteSet(int x1, int y1, int x2, int y2);

	animatedSpriteSet(Vector2 vecP1, Vector2 vecP2);
private:
};

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

struct animatedSprite
{
	sprite *animSprite;

	animatedSpriteSet currAnim;
	int textWidth{ 0 }, textHeight{ 0 }, frameWidth{ 0 }, frameHeight{ 0 };
	int frameTime = 0;
	int totFrames;

	animatedSprite()
	{

	}

	animatedSprite(SDL_Renderer *m_renderer, std::string givTexturePath, int givposX, int givposY, int givTotFrames, int givHorFrames, int givVerFrames);

	animatedSprite(SDL_Renderer *m_renderer, std::string givTexturePath, int givX, int givY, Vector2 animP1, Vector2 animP2, int givTotFrames, int givHorFrames, int givVerFrames);

	animatedSprite(sprite *givAnimSprite, animatedSpriteSet givCurrAnim, int givTotFrames, int givHorFrames, int givVerFrames);

	void setNewAnim(animatedSpriteSet givCurrAnim);

	void updateSprite();

	void updateSpriteTest();

	void renderSprite();

	void setPos(int givX, int givY);

	animatedSprite& operator =(const animatedSprite &otherSprite)
	{
		animSprite->renderer = otherSprite.animSprite->renderer;
		animSprite->pTexture = otherSprite.animSprite->pTexture;
		textWidth = otherSprite.textWidth;
		textHeight = otherSprite.textHeight;
		frameWidth = otherSprite.frameWidth;
		frameHeight = otherSprite.frameHeight;
		frameTime = otherSprite.frameTime;
		totFrames = otherSprite.totFrames;

		return *this;
	}

};