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

class VerticalZombie : public HorizontalZombie
{
public:
	VerticalZombie(const int& TEXTURE_WIDTH, const int& TEXTURE_HEIGHT);

	void destroySelf(VerticalZombie*& verticalZombie);

	void moveZombie();
};

