
#include <time.h>
#include <string>
#include <SDL.h>
#include <SDL_image.h>
#include <windows.h>
#include <vector>
#include "const.h"
#include "utils.h"
#include "sprite.h"
#include "animated_sprite.h"
#include "sprite_set.h"

animatedSprite::animatedSprite( std::string givTexturePath, int givposX, int givposY, int givTotFrames, int givHorFrames, int givVerFrames) : sprite( givTexturePath, givposX, givposY, 1)
{
	textureName = givTexturePath;
	frameWidth = textWidth / givHorFrames;
	frameHeight = textHeight / givVerFrames;
	renderRect.x = renderRect.y = 0;
	textureRect.x = textureRect.y = 0;
	renderRect.h = textureRect.h = frameHeight;
	renderRect.w = textureRect.w = frameWidth;

}

animatedSprite::animatedSprite( std::string givTexturePath, int givX, int givY, Vector2 animP1, Vector2 animP2, int givTotFrames, int givHorFrames, int givVerFrames): sprite( givTexturePath, givX, givY, 1)
{
	frameWidth = textWidth / givHorFrames;
	frameHeight = textHeight / givVerFrames;
	renderRect.x = animP1.x;
	renderRect.y = animP1.y;
	textureRect.x = textureRect.y = 0;
	renderRect.h = textureRect.h = frameHeight;
	renderRect.w = textureRect.w = frameWidth;
	currAnim.p1 = animP1;
	currAnim.p2 = animP2;
}

void animatedSprite::setNewAnim(animatedSpriteSet givCurrAnim)
{
	currAnim.p1 = givCurrAnim.p1;
	currAnim.p2 = givCurrAnim.p2;
	textureRect.x = currAnim.p1.x;
	textureRect.y = currAnim.p1.y;
}

void animatedSprite::updateSprite()
{
	frameTime++;
	if (FPS / frameTime <= 10)
	{
		frameTime = 0;
		textureRect.x += frameWidth;
		if (textureRect.x >= textWidth)
		{
			textureRect.x = 0;
		}
	}
}

void animatedSprite::updateSpriteTest()
{
	frameTime++;
	if (FPS / frameTime <= 10)
	{
		frameTime = 0;
		textureRect.x = (textureRect.x + frameWidth) % currAnim.p2.x;
	}
}

void animatedSprite::setPos(int givX, int givY)
{
	renderRect.x = givX;
	renderRect.y = givY;
}