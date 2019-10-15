#pragma once

#include "Collisions.h"
#include "utils.h"

struct entity
{

	sprite *entitySprite;
	boxCollision *entityCollider;

	entity()
	{

	}

	entity(sprite *givSprite)
	{
		entitySprite = givSprite;
		entityCollider->posX = entitySprite->textureRect.x;
		entityCollider->posY = entitySprite->textureRect.y;
	}

	bool entityCollision(entity givEnt)
	{
		return entityCollider->boxColliding(givEnt.entityCollider);
	}


};