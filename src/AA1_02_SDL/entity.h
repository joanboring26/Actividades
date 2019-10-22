#pragma once

#include "Collisions.h"
#include "utils.h"

struct entity
{

	sprite *entitySprite;
	boxCollision *entityCollider;

	Vector2 spritePrevPos;
	Vector2 colliderPrevPos;

	entity()
	{

	}

	entity(sprite *givSprite)
	{
		entitySprite = givSprite;
		entityCollider = new boxCollision(entitySprite->textureRect.x, entitySprite->textureRect.y, entitySprite->textureRect.w, entitySprite->textureRect.h);
	}

	entity(sprite *givSprite, int givX, int givY)
	{
		entitySprite = givSprite;
		entityCollider = new boxCollision(givX, givY, entitySprite->textureRect.w, entitySprite->textureRect.h);
	}

	entity(sprite *givSprite, int givX, int givY, int givW, int givH)
	{
		entitySprite = givSprite;
		entityCollider = new boxCollision(givX, givY, givW, givH);
	}

	bool entityCollision(entity givEnt)
	{
		return entityCollider->boxColliding(givEnt.entityCollider);
	}

	void moveToGivenPos(int givPosX, int givPosY)
	{
		entitySprite->setPos(givPosX, givPosY);
		entityCollider->setPos(givPosX, givPosY);
	}

	void moveToPreviousPos()
	{
		
	}

};