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

	bool boxColliding( int givX, int givY, int givWidth, int givHeight)
	{
		if (posX + givWidth < givX || posX > givX + givWidth) return false;
		if (posY + givHeight < givY || posY > givY + givHeight) return false;

		return true;
	}

	bool boxColliding(boxCollision *givBox)
	{
		if (posX + widthX < givBox->posX || posX > givBox->posX + givBox->widthX) return false;
		if (posY + widthY < givBox->posY || posY > givBox->posY + givBox->widthY) return false;

		return true;
	}

};