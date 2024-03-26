#pragma once
#include "SDL.h"
#include "../Constants/common_constants.h"
#include "../CommonFuncs/collision_funcs.h"
#include "Texture.h"
#include <fstream>
#include <array>

class Texture;

class PlayerTrail
{
public:
	PlayerTrail(const int& tileType, const int& playerTileTraitPosX, const int& playerTileTraitPosY);

	void renderPlayerTrail(SDL_Rect& camera, Texture& tileTexture, std::array<SDL_Rect, TOTAL_TILE_SPRITES>& gTileClips);

	void renderBreakingWall(SDL_Rect& camera, Texture& tileTexture, SDL_Rect* clip = nullptr);

	int getTileType() {
		return tileType;
	}

	void destroySelf(PlayerTrail* playerTrail);

	SDL_Rect getPlayerTileTrailCollisionBox() const {
		return playerTileTrailCollisionBox;
	}

	int getLifeTime() {
		return lifetime;
	}

	void decreaseLifeTime() {
		lifetime--;
	}

	bool checkIfExpired() {
		if( lifetime <= 0 )
			return true;
		return false;
	}

	int getCurrentBreakingWallFrame() {
		return currentBreakingWallFrame;
	}

	void increaseCurrentBreakingWallFrame() {
		currentBreakingWallFrame++;
		//std::cout << "Increased currentBreakingWallFrame to " << currentBreakingWallFrame << "\n";
	}

	void setCurrentBreakingWallFrame(int& currentBreakingWallFrame) {
		this->currentBreakingWallFrame = currentBreakingWallFrame;
	}

private:
	int tileType;
	SDL_Rect playerTileTrailCollisionBox;
	int lifetime;
	int currentBreakingWallFrame;

};

