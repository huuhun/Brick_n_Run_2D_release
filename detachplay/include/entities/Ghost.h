#pragma once

#include <SDL.h>

#include "../entities/Texture.h"
#include "../entities/HorizontalZombie.h"
#include <ctime> 
#include <cstdlib>
#include <random>
#include <array>

class Texture;
class HorizontalZombie;

class Ghost : public HorizontalZombie
{
public:
	const int GHOST_VEL = 1;
	Ghost(const int& TEXTURE_WIDTH, const int& TEXTURE_HEIGHT);

	void destroySelf(Ghost*& ghost);

	void move(const SDL_Rect& playerCollisionBox);
};