#pragma once
#include "utils.h"

struct player
{
	animatedSprite playerSprite;

	int posX, posY;
	int velX, velY;

	player(animatedSprite givPlayerSprite, int givPosX, int givPosY)
	{
		playerSprite = givPlayerSprite;
		posX = givPosX;
		posY = givPosY;
	}

	void updatePlayerSprite()
	{
		playerSprite.updateSprite();
	}

	void movePlayer(int addX, int addY)
	{
		posX += addX;
		posY += addY;
		updatePlayerSprite();
		playerSprite.setSpritePos(posX, posY);
	}

	void updatePlayer()
	{
		posX += velX;
		posY += velX;
		updatePlayer();
		playerSprite.setSpritePos(posX, posY);
	}

};