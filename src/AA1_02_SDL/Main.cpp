#include <SDL.h>		// Always needs to be included for an SDL app
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>

#include <exception>
#include <iostream>
#include <string>
#include "types.h"

//Game general information
#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

Vector2 mousePos;

int main(int, char*[])
{
	// --- INIT SDL ---
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
		throw "No es pot inicialitzar SDL subsystems";
	// --- INIT TTF ---
	if (TTF_Init() != 0)
			throw "No es pot inicializtar TTF";

	

	// --- WINDOW ---
	SDL_Window *m_window{ SDL_CreateWindow("SDL...", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN) };
	if (m_window == nullptr)
		throw "No es pot inicialitzar SDL_Window";
	
	

	// --- RENDERER ---
	SDL_Renderer *m_renderer{ SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC) };
	if (m_renderer == nullptr)
		throw "No es pot inicialitzar SDL_Renderer";

	//-->SDL_Image 
	const Uint8 imgFlags{ IMG_INIT_PNG | IMG_INIT_JPG };
	if (!(IMG_Init(imgFlags) & imgFlags)) throw "Error: SDL_image init";

	//-->SDL_TTF

	//-->SDL_Mix

	const Uint8 mixFlags(MIX_INIT_MP3 | MIX_INIT_OGG);

	// --- SPRITES ---
		//Background
	SDL_Texture* bgTexture{ IMG_LoadTexture(m_renderer, "../../res/img/bg.jpg") };
	if (bgTexture == nullptr) throw "Error: bgTexture init";

	SDL_Rect bgRect{ 0, 0,SCREEN_WIDTH, SCREEN_HEIGHT };
	//-->Animated Sprite ---
	SDL_Texture* playerTexture{ IMG_LoadTexture(m_renderer, "../../res/img/pl.png") };
	if (bgTexture == nullptr) throw "Error: plTexture init";

	SDL_Rect plRect{ 0,0, 100, 100 };

	// --- TEXT ---

	TTF_Font * font{ TTF_OpenFont("../../res/ttf/thedelicate.ttf", 80) };
	if (font == nullptr) { throw "No se puede inicializar la fuente"; }
	SDL_Surface *tmpSurf{ TTF_RenderText_Blended(font, "My first SDL game", SDL_Color{216, 255, 202, 255}) };
	if (tmpSurf == nullptr) { throw "No se puede inicializar la fuente"; }
	SDL_Texture *textTexture(SDL_CreateTextureFromSurface(m_renderer, tmpSurf));
	SDL_Rect textRect{ 100, 50, tmpSurf->w, tmpSurf->h };

	//tmpSurf = { };

	// --- AUDIO ---

	if (Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 2, 1024) == -1)
	{
		throw "Unable to initialize SDL_mixer audio systems";
	}
	Mix_Music *soundtrack{ Mix_LoadMUS("../../res/au/mainTheme.mp3") };
	if (!soundtrack) throw "Unable to load the Mix_Music soundtrack";
	Mix_VolumeMusic(MIX_MAX_VOLUME / 2);
	Mix_PlayMusic(soundtrack, -1);


	// --- GAME LOOP ---
	SDL_Event event;
	bool isRunning = true;
	while (isRunning) {
		// HANDLE EVENTS
		while (SDL_PollEvent(&event)) {
			switch (event.type) {
			case SDL_QUIT:
				isRunning = false;
				break;
			case SDL_KEYDOWN:
				if (event.key.keysym.sym == SDLK_ESCAPE) isRunning = false;
				break;
			case SDL_MOUSEMOTION:
				mousePos.x = event.motion.x;
				mousePos.y = event.motion.y;
				break;
			default:;
			}
		}

		// UPDATE
		plRect.x += ((mousePos.x - (plRect.w / 2)) - plRect.x) / 10;
		plRect.y += ((mousePos.y - (plRect.h / 2)) - plRect.y) / 10;

		//SDL_GetMouseState(&mouseX, &mouseY);

		// DRAW
		SDL_RenderClear(m_renderer);


		//Background
		SDL_RenderCopy(m_renderer, bgTexture, nullptr, &bgRect);

		//Text
		SDL_RenderCopy(m_renderer, textTexture, nullptr, &textRect);

		//Player
		SDL_RenderCopy(m_renderer, playerTexture, nullptr, &plRect);

		SDL_RenderPresent(m_renderer);

	}

	// --- DESTROY ---
	SDL_DestroyTexture(bgTexture);
	IMG_Quit();
	SDL_DestroyRenderer(m_renderer);
	SDL_DestroyWindow(m_window);

	// --- QUIT AUDIO ---

	Mix_CloseAudio();

	Mix_Quit();

	// --- QUIT ---
	SDL_Quit();

	return 0;
}