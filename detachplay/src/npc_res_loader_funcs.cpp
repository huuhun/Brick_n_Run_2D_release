#include "../include/CommonFuncs/npc_res_loader_funcs.h"

bool loadHorizontalZombieMedia(Texture& horizontalZombieSpriteSheetTexture, std::array<SDL_Rect, WALKING_ANIMATION_FRAMES>& gZombieWalkingRightSpriteClips, Texture& deadZombieSpriteSheetTexture, SDL_Rect& gDeadZombieClip){
//Loading success flag
	bool isSuccess = true;

	//Load sprite sheet texture
	if( !horizontalZombieSpriteSheetTexture.loadFromFile("resources/npc-sprites/horizontal-zombie.png") )
	{
		std::cerr << "Failed to load walking horizontal zombie texture!\n";
		isSuccess = false;
	}
	else
	{
		gZombieWalkingRightSpriteClips[ 0 ].x = 0;
		gZombieWalkingRightSpriteClips[ 0 ].y = 11;
		gZombieWalkingRightSpriteClips[ 0 ].w = 70;
		gZombieWalkingRightSpriteClips[ 0 ].h = 109;

		gZombieWalkingRightSpriteClips[ 1 ].x = 70;
		gZombieWalkingRightSpriteClips[ 1 ].y = 11;
		gZombieWalkingRightSpriteClips[ 1 ].w = 70;
		gZombieWalkingRightSpriteClips[ 1 ].h = 109;

		gZombieWalkingRightSpriteClips[ 2 ].x = 140;
		gZombieWalkingRightSpriteClips[ 2 ].y = 11;
		gZombieWalkingRightSpriteClips[ 2 ].w = 70;
		gZombieWalkingRightSpriteClips[ 2 ].h = 109;

		gZombieWalkingRightSpriteClips[ 3 ].x = 214;
		gZombieWalkingRightSpriteClips[ 3 ].y = 11;
		gZombieWalkingRightSpriteClips[ 3 ].w = 70;
		gZombieWalkingRightSpriteClips[ 3 ].h = 109;
	}

	if( !deadZombieSpriteSheetTexture.loadFromFile("resources/npc-sprites/dead-zombie.png") )
	{
		std::cerr << "Failed to load dead zombie texture!\n";
		isSuccess = false;
	}
	else
	{
		gDeadZombieClip.x = 0;
		gDeadZombieClip.y = 0;
		gDeadZombieClip.w = 143;
		gDeadZombieClip.h = 99;
	}

	return isSuccess;
}

bool loadVerticalZombieMedia(Texture& verticalZombieSpriteSheetTexture, std::array<SDL_Rect, WALKING_ANIMATION_FRAMES>& gZombieWalkingDownSpriteClips) {
	//Loading success flag
	bool isSuccess = true;

	//Load sprite sheet texture
	if( !verticalZombieSpriteSheetTexture.loadFromFile("resources/npc-sprites/vertical-zombie.png") )
	{
		std::cerr << "Failed to load walking vertical zombie texture!\n";
		isSuccess = false;
	}
	else
	{
		gZombieWalkingDownSpriteClips[ 0 ].x = 0;
		gZombieWalkingDownSpriteClips[ 0 ].y = 0;
		gZombieWalkingDownSpriteClips[ 0 ].w = 70;
		gZombieWalkingDownSpriteClips[ 0 ].h = 109;

		gZombieWalkingDownSpriteClips[ 1 ].x = 70;
		gZombieWalkingDownSpriteClips[ 1 ].y = 0;
		gZombieWalkingDownSpriteClips[ 1 ].w = 70;
		gZombieWalkingDownSpriteClips[ 1 ].h = 109;

		gZombieWalkingDownSpriteClips[ 2 ].x = 140;
		gZombieWalkingDownSpriteClips[ 2 ].y = 0;
		gZombieWalkingDownSpriteClips[ 2 ].w = 70;
		gZombieWalkingDownSpriteClips[ 2 ].h = 109;

		gZombieWalkingDownSpriteClips[ 3 ].x = 214;
		gZombieWalkingDownSpriteClips[ 3 ].y = 0;
		gZombieWalkingDownSpriteClips[ 3 ].w = 70;
		gZombieWalkingDownSpriteClips[ 3 ].h = 109;
	}

	return isSuccess;
}

bool loadGhostMedia(Texture& ghostSpriteSheetTexture, std::array<SDL_Rect, WALKING_ANIMATION_FRAMES>& ghostSpriteClips) {
	//Loading success flag
	bool isSuccess = true;

	//Load sprite sheet texture
	if( !ghostSpriteSheetTexture.loadFromFile("resources/npc-sprites/ghost.png") )
	{
		std::cerr << "Failed to load walking vertical zombie texture!\n";
		isSuccess = false;
	}
	else
	{
		ghostSpriteClips[ 0 ].x = 0;
		ghostSpriteClips[ 0 ].y = 0;
		ghostSpriteClips[ 0 ].w = 70;
		ghostSpriteClips[ 0 ].h = 109;

		ghostSpriteClips[ 1 ].x = 70;
		ghostSpriteClips[ 1 ].y = 0;
		ghostSpriteClips[ 1 ].w = 70;
		ghostSpriteClips[ 1 ].h = 109;

		ghostSpriteClips[ 2 ].x = 140;
		ghostSpriteClips[ 2 ].y = 0;
		ghostSpriteClips[ 2 ].w = 70;
		ghostSpriteClips[ 2 ].h = 109;

		ghostSpriteClips[ 3 ].x = 214;
		ghostSpriteClips[ 3 ].y = 0;
		ghostSpriteClips[ 3 ].w = 70;
		ghostSpriteClips[ 3 ].h = 109;
	}

	return isSuccess;
}