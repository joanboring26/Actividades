#include <SDL.h>		// Always needs to be included for an SDL app
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>

#include <time.h>

#include <exception>
#include <iostream>
#include <string>
#include "Button.h"
#include "const.h"
#include "utils.h"
#include "player.h"



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
#pragma region
		//Background
	SDL_Texture* bgTexture{ IMG_LoadTexture(m_renderer, "../../res/img/bg.jpg") };
	if (bgTexture == nullptr) throw "Error: bgTexture init";

	SDL_Rect bgRect{ 0, 0,SCREEN_WIDTH, SCREEN_HEIGHT };

		// Player
	SDL_Texture* playerTexture{ IMG_LoadTexture(m_renderer, "../../res/img/kintoun.png") };
	if (bgTexture == nullptr) throw "Error: plTexture init";
	SDL_Rect plRect{ 0,0, 100, 100 };

#pragma endregion

	//-->Animated Sprite ---
#pragma region 

	animatedSprite playerAnim1( m_renderer, "../../res/img/sp01.png", 6, 6, 1);
	animatedSprite playerAnim2( m_renderer, "../../res/img/sp01.png", 6, 6, 1);

#pragma endregion

	// --- PLAYERS ---

	player player1( &playerAnim1, 200, 200, 10);
	player player2( &playerAnim2, 500, 500, 10);

	// --- TEXT ---
#pragma region 
	SDL_Surface *textSurface{ TTF_RenderText_Blended(TTF_OpenFont("../../res/ttf/doubledecker.ttf", 40), "test", SDL_Color{255,255,255,255}) };

	Button exitButton(m_renderer, textSurface, SDL_Color{ 255, 0, 0, 255 }, SDL_Color{ 0, 0, 0, 255 },"../../res/ttf/doubledecker.ttf", "Exit", 500, 370, 40);

	Button musicButton(m_renderer, textSurface, SDL_Color{ 49, 55, 181, 255 }, SDL_Color{ 0, 0, 0, 255 },"../../res/ttf/doubledecker.ttf", "Music", 300, 370, 40);

	Button playButton(m_renderer, textSurface, SDL_Color{ 0, 255, 0, 255 }, SDL_Color{ 0, 0, 0, 255 }, "../../res/ttf/doubledecker.ttf", "Play", 100, 370, 40);

	bool mouseClicked = false;
	bool playToggle = false;
#pragma endregion

	// --- AUDIO ---
#pragma region
	if (Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 2, 1024) == -1)
	{
		throw "Unable to initialize SDL_mixer audio systems";
	}
	Mix_Music *soundtrack{ Mix_LoadMUS("../../res/au/mainTheme.mp3") };
	if (!soundtrack) throw "Unable to load the Mix_Music soundtrack";
	Mix_VolumeMusic(MIX_MAX_VOLUME / 2);
	Mix_PlayMusic(soundtrack, -1);
#pragma endregion

	// --- TIME  ---
	timer testTimer(5);

	// --- GAME LOOP ---
	bool releaseMouse = true;
	SDL_Event event;
	bool isRunning = true;
	bool yes = true;

	// --- INPUTS ---
	inputs gInp;

	while (isRunning) 
	{
		std::cout << testTimer.updateTimer() << std::endl;
		if (!yes)
		{
			// HANDLE EVENTS
			while (SDL_PollEvent(&event)) {
				switch (event.type) {
				case SDL_QUIT:
					isRunning = false;
					break;
				case SDL_MOUSEMOTION:
					mousePos.x = event.motion.x;
					mousePos.y = event.motion.y;
					break;
				case SDL_MOUSEBUTTONDOWN:
					mouseClicked = true;
					break;
				case SDL_MOUSEBUTTONUP:
					mouseClicked = false;
					releaseMouse = false;
					break;
				default:;
				}
			}

			// --- UPDATE


			// - ANIMATED SPRITES -



			// - TIME -

			//if(testTimer.updateTimer())

			// - OTHER -


			plRect.x += ((mousePos.x - (plRect.w / 2)) - plRect.x) / 10;
			plRect.y += ((mousePos.y - (plRect.h / 2)) - plRect.y) / 10;

			if (exitButton.CheckMouseHover(mousePos.x, mousePos.y, m_renderer) && mouseClicked)
			{
				isRunning = false;
			}

			if (musicButton.CheckMouseHover(mousePos.x, mousePos.y, m_renderer) && mouseClicked)
			{
				if (releaseMouse == false)
				{
					releaseMouse = true;
					std::cout << Mix_PlayingMusic();
					if (Mix_PlayingMusic() != 0)
					{
						Mix_HaltMusic();
					}
					else
					{
						Mix_PlayMusic(soundtrack, -1);
					}
				}
			}

			if (playButton.CheckMouseHover(mousePos.x, mousePos.y, m_renderer) && mouseClicked)
			{
				if (releaseMouse == false)
				{
					releaseMouse = true;
					if (playButton.clicked == false && !playToggle) {
						playButton.normalColor = SDL_Color{ 255, 0, 0, 255 };
						playButton.permanentChangeColor(m_renderer, SDL_Color{ 255, 0, 0, 255 });
						playToggle = true;
					}
					else
					{
						playButton.normalColor = SDL_Color{ 0, 255, 0, 255 };
						playButton.permanentChangeColor(m_renderer, SDL_Color{ 0, 255, 0, 255 });
						playToggle = false;
					}
				}

			}

			//SDL_GetMouseState(&mouseX, &mouseY);

			// --- RENDER STUFF

			SDL_RenderClear(m_renderer);

			// - Background - 
			SDL_RenderCopy(m_renderer, bgTexture, nullptr, &bgRect);

			// - Text -
			exitButton.RenderText(m_renderer);
			playButton.RenderText(m_renderer);
			musicButton.RenderText(m_renderer);

			// - Player - 
			SDL_RenderCopy(m_renderer, playerTexture, nullptr, &plRect);

			// - Animated sprites -


			SDL_RenderPresent(m_renderer);
		}
		else
		{
		// --- INPUT ---
		gInp.getKeyboardInputs();

		// --- UPDATE ---


		player1.updatePlayer( gInp.keyboard, 0);

		player2.updatePlayer(gInp.keyboard, 1);

		// --- RENDER ---

		player1.renderPlayer();
		player2.renderPlayer();

		SDL_RenderPresent(m_renderer);

		}


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
