#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <SDL_mixer.h>

#include "../include/window/WindowManager.h"
#include "../include/Constants/common_constants.h"
#include "../include/entities/Texture.h"

WindowManager::WindowManager(SDL_Window* p_window, SDL_Renderer* p_renderer) {
	window = p_window;
	renderer = p_renderer;
}

bool WindowManager::init() {
	//Init flag
	bool checkSuccess = true;

	if( SDL_Init(SDL_INIT_VIDEO) < 0 )
	{
		std::cout << "SDL could not init! SDL Error: " << SDL_GetError() << "\n";
		checkSuccess = false;
	}
	else
	{
		//Set texture filtering to linear
		if( !SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1") )
		{
			std::cout << "Warning: Linear texture filtering not enabled!\n";
		}
		//Create window
		window = SDL_CreateWindow("SDL Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN/* SDL_WINDOW_FULLSCREEN*/);
		if( window == nullptr )
		{
			std::cout << "Window could not be created! SDL_Error: " << SDL_GetError() << "\n";
			checkSuccess = false;
		}
		else {
			//Create renderer for window
			renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED /*| SDL_RENDERER_PRESENTVSYNC*/);
			if( renderer == nullptr )
			{
				std::cout << "Renderer could not be created! SDL Error: " << SDL_GetError() << "\n";
				checkSuccess = false;
			}
			else
			{
				//Init Renerer color
				SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0XFF, 0XFF);

				//Init PNG loading
				int imgFlags = IMG_INIT_PNG;
				if( !IMG_Init(imgFlags) )
				{
					std::cout << "SDL image could not be initialize! SDL_image Error: " << IMG_GetError() << "\n";
					checkSuccess = false;
				}

				//Initialize SDL_ttf
				if( TTF_Init() == -1 )
				{
					std::cout << "SDL_ttf could not initialize! SDL_ttf Error: " << TTF_GetError() << "\n";
					checkSuccess = false;
				}

				//Initialize SDL_mixer
				if( Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0 )
				{
					std::cout << "SDL_mixer could not initialize! SDL_mixer Error: " << Mix_GetError() << "\n";
					checkSuccess = false;
				}
			}
		}
	}
	return checkSuccess;
}


void WindowManager::clearScreen() {
	SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0XFF, 0XFF);
	SDL_RenderClear(renderer);
}

void WindowManager::updateScreen() {
	//Update screen
	SDL_RenderPresent(renderer);
}

void WindowManager::close(WindowManager* gameWindow, TTF_Font*& gFont) {

	TTF_CloseFont(gFont);
	gFont = nullptr;

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	renderer = nullptr;
	window = nullptr;
	std::cout << "Window and renderer destroyed \n";

	//Quit SDL subsystems
	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
	std::cout << "SDL subsystems quitted \n";

	if( gameWindow != nullptr )
	{
		delete gameWindow;
		gameWindow = nullptr;
		std::cout << "Object gameWindow pointer deallocated \n";
	}
}

void WindowManager::deallocateSound(int numChunks, ...) {
	va_list args;
	va_start(args, numChunks);

	for( int i = 0; i < numChunks; i++ )
	{
		Mix_Chunk* chunk = va_arg(args, Mix_Chunk*);
		Mix_FreeChunk(chunk);
	}
	
	va_end(args);
	Mix_Quit();
}

void WindowManager::deallocateMusic(int numMusic, ...) {
	va_list args;
	va_start(args, numMusic);

	for( int i = 0; i < numMusic; i++ )
	{
		Mix_Music* music = va_arg(args, Mix_Music*);
		Mix_FreeMusic(music);
	}

	va_end(args);
}