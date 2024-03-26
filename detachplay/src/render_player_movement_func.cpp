#include "../include/CommonFuncs/render_player_movement_func.h"

//void connectLineAndRender(SDL_Rect& camera, SDL_Renderer* gRenderer, const SDL_Rect& currentPlayerTrailCollisionBox, const SDL_Rect& previousCollidedPlayerTrailCollisionBox, std::vector<KillArea*>& killLinesVector) {
//	SDL_Rect playerTrailCollisionBox = { currentPlayerTrailCollisionBox, }
//	KillArea * killLine = new KillArea(playerTrailCollisionBox);
//}

void spawnConnectLine(const SDL_Rect& mostRecentTrail, const SDL_Rect& prevTrail, std::vector<KillArea*>& killLinesVector) {

	KillArea* killLine = new KillArea(mostRecentTrail.x, mostRecentTrail.y, 0, 0);
	killLine->setPrevKillPointPosX(prevTrail.x + TILE_SIZE / 2);
	killLine->setPrevKillPointPosY(prevTrail.y + TILE_SIZE / 2);

	killLinesVector.push_back(killLine);
}

void renderPlayerMovingTextureAction(int& playerActionCheck, Player& player, SDL_Rect& camera, int& currentFrame, int& playerTimeStep, Texture& playerSpriteSheetTexture, std::array<SDL_Rect, WALKING_ANIMATION_FRAMES>& gPlayerWalkingDownSpriteClips, std::array<SDL_Rect, WALKING_ANIMATION_FRAMES>& gPlayerWalkingUpSpriteClips, std::array<SDL_Rect, WALKING_ANIMATION_FRAMES>& gPlayerWalkingLeftSpriteClips, std::array<SDL_Rect, WALKING_ANIMATION_FRAMES>& gPlayerWalkingRightSpriteClips, std::vector<PlayerTrail*>& playerTileTrailsVector, std::vector<KillArea*>& killLinesVector, Texture& wallBreakingTexture, std::array<SDL_Rect, BREAKING_WALL_ANIMATION_FRAMES>& gWallBreakingSpriteClips) {
	switch( playerActionCheck )
	{
	case STANDING_STILL_FACING_DOWN:
	{
		SDL_Rect* currentClip = &gPlayerWalkingDownSpriteClips[ 1 ];

		player.render(camera, playerSpriteSheetTexture, currentClip);
		break;
	}
	case STANDING_STILL_FACING_UP:
	{
		SDL_Rect* currentClip = &gPlayerWalkingUpSpriteClips[ 1 ];

		player.render(camera, playerSpriteSheetTexture, currentClip);
		break;
	}
	case STANDING_STILL_FACING_LEFT:
	{
		SDL_Rect* currentClip = &gPlayerWalkingLeftSpriteClips[ 1 ];

		player.render(camera, playerSpriteSheetTexture, currentClip);
		break;
	}
	case STANDING_STILL_FACING_RIGHT:
	{
		SDL_Rect* currentClip = &gPlayerWalkingRightSpriteClips[ 2 ];

		player.render(camera, playerSpriteSheetTexture, currentClip);
		break;
	}
	case WALKING_DOWN:
	{
		SDL_Rect* currentClip = &gPlayerWalkingDownSpriteClips[ currentFrame / 4 ];

		if( playerTimeStep > 7 )
		{
			int playerOldPosX = player.getPlayerCollisionBox().x;
			int playerOldPosY = player.getPlayerCollisionBox().y;

			PlayerTrail* playerTileTrail = new PlayerTrail(0, playerOldPosX, playerOldPosY);
			SDL_Rect playerTrailCollisionBox = playerTileTrail->getPlayerTileTrailCollisionBox();

			playerTileTrailsVector.push_back(playerTileTrail);

			KillArea* killLine = new KillArea(playerTrailCollisionBox.x, playerTrailCollisionBox.y, 0, 0);

			if( killLinesVector.size() > 0 )
			{
				killLine->setPrevKillPointPosX(killLinesVector[ killLinesVector.size() - 1 ]->getCurrentKillPointPosX());
				killLine->setPrevKillPointPosY(killLinesVector[ killLinesVector.size() - 1 ]->getCurrentKillPointPosY());
			}

			killLinesVector.push_back(killLine);

			playerTimeStep = 0;
		}
		playerTimeStep++;

		player.render(camera, playerSpriteSheetTexture, currentClip);

		//std::cout << "killLinesVector size:" << killLinesVector.size() << "\n";
		break;
	}
	case WALKING_UP:
	{

		SDL_Rect* currentClip = &gPlayerWalkingUpSpriteClips[ currentFrame / 4 ];

		if( playerTimeStep > 7 )
		{
			int playerOldPosX = player.getPlayerCollisionBox().x;
			int playerOldPosY = player.getPlayerCollisionBox().y;

			PlayerTrail* playerTileTrail = new PlayerTrail(0, playerOldPosX, playerOldPosY);
			SDL_Rect playerTrailCollisionBox = playerTileTrail->getPlayerTileTrailCollisionBox();

			playerTileTrailsVector.push_back(playerTileTrail);

			KillArea* killLine = new KillArea(playerTrailCollisionBox.x, playerTrailCollisionBox.y, 0, 0);

			if( killLinesVector.size() > 0 )
			{
				killLine->setPrevKillPointPosX(killLinesVector[ killLinesVector.size() - 1 ]->getCurrentKillPointPosX());
				killLine->setPrevKillPointPosY(killLinesVector[ killLinesVector.size() - 1 ]->getCurrentKillPointPosY());
			}

			killLinesVector.push_back(killLine);

			playerTimeStep = 0;
		}
		playerTimeStep++;

		player.render(camera, playerSpriteSheetTexture, currentClip);

		//std::cout << "killLinesVector size:" << killLinesVector.size() << "\n";

		break;
	}
	case WALKING_LEFT:
	{

		SDL_Rect* currentClip = &gPlayerWalkingLeftSpriteClips[ currentFrame / 4 ];

		if( playerTimeStep > 7 )
		{
			int playerOldPosX = player.getPlayerCollisionBox().x;
			int playerOldPosY = player.getPlayerCollisionBox().y;

			PlayerTrail* playerTileTrail = new PlayerTrail(0, playerOldPosX, playerOldPosY);
			SDL_Rect playerTrailCollisionBox = playerTileTrail->getPlayerTileTrailCollisionBox();

			playerTileTrailsVector.push_back(playerTileTrail);

			KillArea* killLine = new KillArea(playerTrailCollisionBox.x, playerTrailCollisionBox.y, 0, 0);

			if( killLinesVector.size() > 0 )
			{
				killLine->setPrevKillPointPosX(killLinesVector[ killLinesVector.size() - 1 ]->getCurrentKillPointPosX());
				killLine->setPrevKillPointPosY(killLinesVector[ killLinesVector.size() - 1 ]->getCurrentKillPointPosY());
			}

			killLinesVector.push_back(killLine);

			playerTimeStep = 0;
		}
		playerTimeStep++;

		player.render(camera, playerSpriteSheetTexture, currentClip);

		//std::cout << "killLinesVector size:" << killLinesVector.size() << "\n";
		break;
	}
	case WALKING_RIGHT:
	{

		SDL_Rect* currentClip = &gPlayerWalkingRightSpriteClips[ currentFrame / 4 ];

		if( playerTimeStep > 7 )
		{
			int playerOldPosX = player.getPlayerCollisionBox().x;
			int playerOldPosY = player.getPlayerCollisionBox().y;

			PlayerTrail* playerTileTrail = new PlayerTrail(0, playerOldPosX, playerOldPosY);
			SDL_Rect playerTrailCollisionBox = playerTileTrail->getPlayerTileTrailCollisionBox();

			playerTileTrailsVector.push_back(playerTileTrail);

			KillArea* killLine = new KillArea(playerTrailCollisionBox.x, playerTrailCollisionBox.y, 0, 0);

			if( killLinesVector.size() > 0 )
			{
				killLine->setPrevKillPointPosX(killLinesVector[ killLinesVector.size() - 1 ]->getCurrentKillPointPosX());
				killLine->setPrevKillPointPosY(killLinesVector[ killLinesVector.size() - 1 ]->getCurrentKillPointPosY());
			}

			killLinesVector.push_back(killLine);


			playerTimeStep = 0;
		}
		playerTimeStep++;

		player.render(camera, playerSpriteSheetTexture, currentClip);

		//std::cout << "killLinesVector size:" << killLinesVector.size() << "\n";

		break;
	}

	

	}
}
