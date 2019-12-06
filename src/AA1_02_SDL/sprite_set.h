#pragma once

#include "utils.h"

class animatedSpriteSet
{
public:
	Vector2 p1;
	Vector2 p2;

	animatedSpriteSet()
	{

	}

	animatedSpriteSet(int x1, int y1, int x2, int y2)
	{
		p1.x = x1;
		p1.y = y1;
		p2.x = x2;
		p2.y = y2;
	}

	animatedSpriteSet(Vector2 vecP1, Vector2 vecP2)
	{
		p1 = vecP1;
		p2 = vecP2;
	}
private:
};