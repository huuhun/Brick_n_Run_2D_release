#pragma once
#include <fstream>
#include <SDL.h>

#include "../Constants/common_constants.h"
#include "../CommonFuncs/collision_funcs.h"
#include "Texture.h"
#include "Player.h"

class Texture;
class Player;

class Tile
{

public:
	Tile(const int& tilePosX, const int& tilePosY, const int& tileType);

	//Shows the tile
	void render(SDL_Rect& camera, Texture& gTileTexture, std::array<SDL_Rect, TOTAL_TILE_SPRITES>& gTileClips);

	int getTileType() {
		return tileType;
	}

	SDL_Rect getCollisionBox() {
		return tileCollisionBox;
	}
private:
	SDL_Rect tileCollisionBox;

	//The tile type
	int tileType;
};