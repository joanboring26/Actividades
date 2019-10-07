#pragma once
#include <SDL.h>
#include <SDL_ttf.h>
#include <string>

struct Button
{
	TTF_Font * font;
	SDL_Surface *tmpSurf;
	SDL_Texture *textTexture;
	SDL_Rect *textRect;
	SDL_Color normalColor;
	SDL_Color hoverColor;

	std::string path;
	std::string text;

	int posX, posY, sizX, sizY, fontSize;

	bool mouseHovering;

	Button(SDL_Renderer *m_renderer, SDL_Color givColor, SDL_Color givHoverColor,std::string givPath, std::string givText, int x, int y, int givFontSize)
	{
		normalColor = givColor;
		hoverColor = givHoverColor;
		path = givPath;
		text = givText;

		font = TTF_OpenFont( path.c_str(), givFontSize);
		tmpSurf = TTF_RenderText_Blended(font, text.c_str(), givColor);
		textTexture = SDL_CreateTextureFromSurface(m_renderer, tmpSurf);
		textRect = new SDL_Rect{ x, y, tmpSurf->w, tmpSurf->h};
		posX = x;
		posY = y;
		sizX = textRect->w;
		sizY = textRect->h;
	}



	bool CheckMouseHover(int mouseX, int mouseY, SDL_Renderer *m_renderer)
	{
		if ((mouseX > posX && mouseX < (posX + sizX)) && ((mouseY > posY) && (mouseY < (posY + sizY))))
		{
			tmpSurf = TTF_RenderText_Blended(font, text.c_str(), hoverColor);
			textTexture = SDL_CreateTextureFromSurface(m_renderer, tmpSurf);
			mouseHovering = true;
			return true;
		}
		else
		{
			tmpSurf = TTF_RenderText_Blended(font, text.c_str(), normalColor);
			textTexture = SDL_CreateTextureFromSurface(m_renderer, tmpSurf);
			mouseHovering = false;
			return false;
		}
	}

	void RenderText(SDL_Renderer *m_renderer)
	{
		SDL_RenderCopy( m_renderer, textTexture, nullptr, textRect);
	}

	void updateSettings(SDL_Renderer *m_renderer)
	{
		font = TTF_OpenFont(path.c_str(), fontSize);
		tmpSurf = TTF_RenderText_Blended(font, text.c_str(), normalColor);
		textTexture = SDL_CreateTextureFromSurface(m_renderer, tmpSurf);
		textRect = new SDL_Rect{ posX, posY, tmpSurf->w, tmpSurf->h };
	}
};