#pragma once
#include "utils.h"
#include "sprite.h"
#include "const.h"
#include "Collisions.h"

struct player
{
	animatedSprite *playerSprite;

	int posX, posY;
	int velX{ 0 }, velY{ 0 };
	int speed = 0;

	player(animatedSprite *givPlayerSprite, int givPosX, int givPosY, int givSpeed);

	void setNewAnim(animatedSpriteSet newAnim);

	void updatePlayerSprite();

	void updatePlayerSpriteTest();

	void movePlayer(int addX, int addY);

	void checkPlayerInputs(bool *givKeys, int playerNum);

	void updatePlayer(bool *givKeys, int playerNum);

	void updatePlayerTest(bool *givKeys, int playerNum);

	void renderPlayer();
};