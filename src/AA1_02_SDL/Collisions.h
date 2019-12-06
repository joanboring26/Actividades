#pragma once

struct boxCollision
{
	int posX;
	int posY;
	int widthX;
	int widthY;

	boxCollision(){}

	boxCollision(int givX, int givY, int givWX, int givWY)
	{
		posX = givX;
		posY = givY;
		widthX = givWX;
		widthY = givWY;
	}

	bool simpleColliding(int collX, int collY)
	{
		if ((collX > posX && collX < (posX + widthX)) && ((collY > posY) && (collY < (posY + widthY))))
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	bool boxCollisionCheck(int givX, int givY, int givWidthX, int givWidthY)
	{
		if (posX + widthX < givX || posX > givX + givWidthX) return false;
		if (posY + widthY < givY || posY > givY + givWidthY) return false;

		return true;
	}
};