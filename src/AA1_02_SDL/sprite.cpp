#include <time.h>
#include <string>
#include <SDL.h>
#include <SDL_image.h>
#include <windows.h>
#include <vector>
#include "const.h"
#include "utils.h"
#include "sprite.h"

#pragma region Sprite set

animatedSpriteSet::animatedSpriteSet(int x1, int y1, int x2, int y2)
{
	p1.x = x1;
	p1.y = y1;
	p2.x = x2;
	p2.y = y2;
}

animatedSpriteSet::animatedSpriteSet(Vector2 vecP1, Vector2 vecP2)
{
	p1 = vecP1;
	p2 = vecP2;
}

#pragma endregion

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

#pragma region Animated sprite

animatedSprite::animatedSprite(SDL_Renderer *m_renderer, std::string givTexturePath, int givposX, int givposY, int givTotFrames, int givHorFrames, int givVerFrames)
{
	animSprite = new sprite(m_renderer, givTexturePath, givposX, givposY, 1);
	SDL_QueryTexture(animSprite->pTexture, NULL, NULL, &textWidth, &textHeight); //Al fer &textWidth i &frameHeight aquestes s'omplen amb els valors de tamany de la textura
	frameWidth = textWidth / givHorFrames;
	frameHeight = textHeight / givVerFrames;
	animSprite->renderRect.x = animSprite->renderRect.y = 0;
	animSprite->textureRect.x = animSprite->textureRect.y = 0;
	animSprite->renderRect.h = animSprite->textureRect.h = frameHeight;
	animSprite->renderRect.w = animSprite->textureRect.w = frameWidth;

}

animatedSprite::animatedSprite(SDL_Renderer *m_renderer, std::string givTexturePath, int givX, int givY, Vector2 animP1, Vector2 animP2, int givTotFrames, int givHorFrames, int givVerFrames)
{
	animSprite = new sprite(m_renderer, givTexturePath, givX, givY, 1);
	SDL_QueryTexture(animSprite->pTexture, NULL, NULL, &textWidth, &textHeight); //Al fer &textWidth i &frameHeight aquestes s'omplen amb els valors de tamany de la textura
	frameWidth = textWidth / givHorFrames;
	frameHeight = textHeight / givVerFrames;
	animSprite->renderRect.x = animP1.x;
	animSprite->renderRect.y = animP1.y;
	animSprite->textureRect.x = animSprite->textureRect.y = 0;
	animSprite->renderRect.h = animSprite->textureRect.h = frameHeight;
	animSprite->renderRect.w = animSprite->textureRect.w = frameWidth;
	currAnim.p1 = animP1;
	currAnim.p2 = animP2;
}

animatedSprite::animatedSprite(sprite *givAnimSprite, animatedSpriteSet givCurrAnim, int givTotFrames, int givHorFrames, int givVerFrames)
{
	animSprite = givAnimSprite;
	SDL_QueryTexture(animSprite->pTexture, NULL, NULL, &textWidth, &textHeight); //Al fer &textWidth i &frameHeight aquestes s'omplen amb els valors de tamany de la textura
	frameWidth = textWidth / givHorFrames;
	frameHeight = textHeight / givVerFrames;
	animSprite->renderRect.x = animSprite->renderRect.y = 0;
	animSprite->textureRect.x = animSprite->textureRect.y = 0;
	animSprite->renderRect.h = animSprite->textureRect.h = frameHeight;
	animSprite->renderRect.w = animSprite->textureRect.w = frameWidth;
}

void animatedSprite::setNewAnim(animatedSpriteSet givCurrAnim)
{
	currAnim.p1 = givCurrAnim.p1;
	currAnim.p2 = givCurrAnim.p2;
	animSprite->textureRect.x = currAnim.p1.x;
	animSprite->textureRect.y = currAnim.p1.y;
}

void animatedSprite::updateSprite()
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

void animatedSprite::updateSpriteTest()
{
	frameTime++;
	if (FPS / frameTime <= 10)
	{
		frameTime = 0;
		animSprite->textureRect.x = (animSprite->textureRect.x + frameWidth) % currAnim.p2.x;
	}
}

void animatedSprite::renderSprite()
{
	animSprite->renderSprite();
}

void animatedSprite::setPos(int givX, int givY)
{
	animSprite->renderRect.x = givX;
	animSprite->renderRect.y = givY;
}

#pragma endregion
