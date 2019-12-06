#pragma once

#include "sprite.h"
#include "sprite_set.h"

struct animatedSprite : public sprite
{
public:
	animatedSpriteSet currAnim;
	int textWidth{ 0 }, textHeight{ 0 }, frameWidth{ 0 }, frameHeight{ 0 };
private:
	int frameTime = 0;
	int totFrames = 0;

	animatedSprite() : sprite() {};

public:
	animatedSprite( std::string givTexturePath, int givposX, int givposY, int givTotFrames, int givHorFrames, int givVerFrames);

	animatedSprite( std::string givTexturePath, int givX, int givY, Vector2 animP1, Vector2 animP2, int givTotFrames, int givHorFrames, int givVerFrames);

	animatedSprite( animatedSpriteSet givCurrAnim, int givTotFrames, int givHorFrames, int givVerFrames);

	void setNewAnim( animatedSpriteSet givCurrAnim);

	void updateSprite();

	void updateSpriteTest();

	void setPos(int givX, int givY);

	animatedSprite& operator =(const animatedSprite &otherSprite)
	{
		textureName = otherSprite.textureName;
		textWidth = otherSprite.textWidth;
		textHeight = otherSprite.textHeight;
		frameWidth = otherSprite.frameWidth;
		frameHeight = otherSprite.frameHeight;
		frameTime = otherSprite.frameTime;
		totFrames = otherSprite.totFrames;

		return *this;
	}

};