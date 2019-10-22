
#include "utils.h"
#include "const.h"
#include "Collisions.h"
#include "player.h"

player::player(animatedSprite *givPlayerSprite, int givPosX, int givPosY, int givSpeed)
{
	playerSprite = givPlayerSprite;
	posX = givPosX;
	posY = givPosY;
	speed = givSpeed;
}

void player::updatePlayerSprite()
{
	playerSprite->updateSprite();
}

void player::movePlayer(int addX, int addY)
{
	posX += addX;
	posY += addY;
	updatePlayerSprite();
	playerSprite->setPos(posX, posY);
}

void player::checkPlayerInputs(bool *givKeys, int playerNum)
{
	switch (playerNum)
	{
	case 0:
		if (givKeys[(int)keyPressed::UP])
		{
			velY = -1;
		}
		else if (givKeys[(int)keyPressed::DOWN])
		{
			velY = 1;
		}
		else
		{
			velY = 0;
		}
		if (givKeys[(int)keyPressed::LEFT])
		{
			velX = -1;
		}
		else if (givKeys[(int)keyPressed::RIGHT])
		{
			velX = 1;
		}
		else
		{
			velX = 0;
		}
		break;
	case 1:
		if (givKeys[(int)keyPressed::W])
		{
			velY = -1;
		}
		else if (givKeys[(int)keyPressed::S])
		{
			velY = 1;
		}
		else
		{
			velY = 0;
		}
		if (givKeys[(int)keyPressed::A])
		{
			velX = -1;
		}
		else if (givKeys[(int)keyPressed::D])
		{
			velX = 1;
		}
		else
		{
			velX = 0;
		}
		break;
	default:

		break;
	}
}

void player::updatePlayer(bool *givKeys, int playerNum)
{
	checkPlayerInputs(givKeys, playerNum);

	if (velX != 0 || velY != 0)
	{
		updatePlayerSprite();
		posX += (velX * speed);
		posY += (velY * speed);
		playerSprite->setPos(posX, posY);
	}
}

void player::renderPlayer()
{
	playerSprite->renderSprite();
}