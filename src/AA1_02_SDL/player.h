#pragma once
#include "utils.h"

struct player
{
	animatedSprite *playerSprite;

	int posX, posY;
	int velX{ 0 }, velY{ 0 };
	int speed = 0;

	player(animatedSprite *givPlayerSprite, int givPosX, int givPosY, int givSpeed)
	{
		playerSprite = givPlayerSprite;
		posX = givPosX;
		posY = givPosY;
		speed = givSpeed;
	}

	void updatePlayerSprite()
	{
		playerSprite->updateSprite();
	}

	void movePlayer(int addX, int addY)
	{
		posX += addX;
		posY += addY;
		updatePlayerSprite();
		playerSprite->setSpritePos(posX, posY);
	}

	void updatePlayer()
	{
		posX += (velX * speed);
		posY += (velX * speed);
		updatePlayerSprite();
		playerSprite->setSpritePos(posX, posY);
	}

	void renderPlayer()
	{
		playerSprite->renderSprite();
	}
};