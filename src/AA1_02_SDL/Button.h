#pragma once
#include <SDL.h>
#include <SDL_ttf.h>
#include <string>

#include "Collisions.h"

struct Button
{
	TTF_Font * font;
	SDL_Texture *textTexture;
	SDL_Rect *textRect;
	SDL_Color normalColor;
	SDL_Color hoverColor;
	boxCollision buttonCollider;

	std::string path;
	std::string text;

	int posX, posY, sizX, sizY, fontSize;

	bool mouseHovering;
	bool clicked = false;

	Button(SDL_Renderer *m_renderer, SDL_Surface *givSurface, SDL_Color givColor, SDL_Color givHoverColor,std::string givPath, std::string givText, int x, int y, int givFontSize)
	{
		normalColor = givColor;
		hoverColor = givHoverColor;
		path = givPath;
		text = givText;
		font = TTF_OpenFont(path.c_str(), givFontSize);
		givSurface = TTF_RenderText_Blended(font, givText.c_str(), givColor);
		textTexture = SDL_CreateTextureFromSurface(m_renderer, givSurface);
		textRect = new SDL_Rect{ x, y, givSurface->w, givSurface->h};
		SDL_SetTextureColorMod(textTexture, givColor.r, givColor.g, givColor.b);
		posX = x;
		posY = y;
		sizX = textRect->w;
		sizY = textRect->h;
		buttonCollider = boxCollision(x, y, sizX, sizY);
	}



	bool CheckMouseHover(int mouseX, int mouseY, SDL_Renderer *m_renderer)
	{
		if (buttonCollider.simpleColliding(mouseX, mouseY))
		{
			changeColor(m_renderer, hoverColor);
			mouseHovering = true;
			return true;
		}
		else
		{
			changeColor(m_renderer, normalColor);
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
		SDL_RenderCopy(m_renderer, textTexture, nullptr, textRect);
	}

	void changeColor(SDL_Renderer *m_renderer, SDL_Color givColor)
	{
		SDL_SetTextureColorMod(textTexture, givColor.r, givColor.g, givColor.b);
	}

	void permanentChangeColor(SDL_Renderer *m_renderer, SDL_Color givColor)
	{
		SDL_DestroyTexture(textTexture);
		SDL_Surface *tempSurf = TTF_RenderText_Blended(font, text.c_str(), givColor);
		//normalColor = givColor;
		textTexture = SDL_CreateTextureFromSurface(m_renderer, tempSurf);
		SDL_FreeSurface(tempSurf);
	}
};