#pragma once
#include <SDL.h>
#include <SDL_mixer.h>

#include <cstdarg>
#include <vector>

#include "../entities/Texture.h"
#include "../entities/Tile.h"
#include "../entities/PlayerTrail.h"

class PlayerTrail;
class Tile;
class PlayerTrail;

class WindowManager{
public:
	WindowManager(SDL_Window* p_window, SDL_Renderer* p_renderer);
	 bool init();
	 void clearScreen();

	 SDL_Renderer* getRenderer() {
		 return renderer;
	 }

	 void updateScreen();
	 
	 void close(WindowManager* gameWindow, TTF_Font*& gFont);

	 void deallocateSound(int numChunks, ...);

	 void deallocateMusic(int numMusic, ...);
private:
		 SDL_Window* window;
		 SDL_Renderer* renderer;
};