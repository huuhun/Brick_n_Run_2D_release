#include "../include/entities/PlayerTrail.h"

PlayerTrail::PlayerTrail(const int& tileType, const int& playerTileTrailPosX, const int& playerTileTrailPosY)
{
	this->tileType = tileType;

	playerTileTrailCollisionBox.x = playerTileTrailPosX;
	playerTileTrailCollisionBox.y = playerTileTrailPosY;

	playerTileTrailCollisionBox.w = TILE_WIDTH;
	playerTileTrailCollisionBox.h = TILE_HEIGHT;

	lifetime = TRAILS_LIFETIME;
	currentBreakingWallFrame = 0;
}

void PlayerTrail::renderPlayerTrail(SDL_Rect& camera, Texture& tileTexture, std::array<SDL_Rect, TOTAL_TILE_SPRITES>& gTileClips)
{
	tileTexture.renderTexture(playerTileTrailCollisionBox.x - camera.x, playerTileTrailCollisionBox.y - camera.y, &gTileClips[ 1 ]);
}

void PlayerTrail::renderBreakingWall(SDL_Rect& camera, Texture& tileTexture, SDL_Rect* clip)
{
	tileTexture.renderTexture(playerTileTrailCollisionBox.x - camera.x, playerTileTrailCollisionBox.y - camera.y, clip);
}

void PlayerTrail::destroySelf(PlayerTrail* playerTrail) {
	if( playerTrail != nullptr )
	{
		delete playerTrail;
		playerTrail = nullptr;
		std::cout << "A trail has been destroyed after killing a NPC\n";
	}
}

