#pragma once

struct spriteData
{
	int x;
	int y;

	int w;
	int h;
	
	spriteData()
	{
		x = 0;
		y = 0;
		w = 0;
		h = 0;
	}

	spriteData(int givx, int givy, int givw, int givh)
	{
		x = givx;
		y = givy;
		w = givw;
		h = givh;
	}

};