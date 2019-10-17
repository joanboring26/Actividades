#pragma once
#include "utils.h"
#include "const.h"
#include "Collisions.h"

struct player
{
	animatedSprite *playerSprite;



	int posX, posY;
	int velX{ 0 }, velY{ 0 };
	int speed = 0;

	player(animatedSprite *givPlayerSprite, int givPosX, int givPosY, int givSpeed);

	void updatePlayerSprite();

	void movePlayer(int addX, int addY);

	void checkPlayerInputs(bool *givKeys, int playerNum);

	void updatePlayer(bool *givKeys, int playerNum);

	void renderPlayer();
};