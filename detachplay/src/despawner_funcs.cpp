#include "../include/CommonFuncs/despawner_funcs.h"

void killThemAll(std::vector<HorizontalZombie*>& horizontalZombiesVector, std::vector<VerticalZombie*>& verticalZombiesVector) {
	for( int i = 0; i < horizontalZombiesVector.size(); i++ )
	{
		if( horizontalZombiesVector[ i ] != nullptr ) {
			delete horizontalZombiesVector[ i ];
			horizontalZombiesVector[ i ] = nullptr;

			horizontalZombiesVector.erase(horizontalZombiesVector.begin() + i);
		}
	}

	for( int i = 0; i < verticalZombiesVector.size(); i++ )
	{
		if( verticalZombiesVector[ i ] != nullptr ) {
			delete verticalZombiesVector[ i ];
			verticalZombiesVector[ i ] = nullptr;

			verticalZombiesVector.erase(verticalZombiesVector.begin() + i);
		}
	}

	std::cout << "KILLED THEM ALL\n";
}

void deallocatePlayerTrails(std::vector<PlayerTrail*>& playerTileTrailsVector) {
	for( int i = 0; i < playerTileTrailsVector.size(); i++ )
	{
		if( playerTileTrailsVector[ i ] != nullptr ) {
			delete playerTileTrailsVector[ i ];
			playerTileTrailsVector[ i ] = nullptr;
			playerTileTrailsVector.erase(playerTileTrailsVector.begin() + i);
			std::cout << "playerTileTrailsVector #" << i << " deallocated\n";
		}
	}
}

void deallocateTileSet(std::array<Tile*, TOTAL_TILES>& tileSet) {
	for( int i = 0; i < tileSet.size(); i++ )
	{
		if( tileSet[ i ] != nullptr ) {
			delete tileSet[ i ];
			tileSet[ i ] = nullptr;
			std::cout << "tileSet #" << i << " deallocated\n";
		}
	}
}

void deallocateKillLine(std::vector<KillArea*>& killLinesVector) {
	for( int i = 0; i < killLinesVector.size(); i++ )
	{
		if( killLinesVector[ i ] != nullptr ) {
			delete killLinesVector[ i ];
			killLinesVector[ i ] = nullptr;
			killLinesVector.erase(killLinesVector.begin() + i);
			std::cout << "killLinesVector #" << i << " deallocated\n";
		}
	}
}
void destroyExpiredTrails(std::vector<PlayerTrail*>& playerTileTrailsVector, std::array<SDL_Rect, BREAKING_WALL_ANIMATION_FRAMES>& gWallBreakingSpriteClips, Texture& wallBreakingTexture, std::vector<PlayerTrail*>& breakingWallAnimationVector) {
	for( int i = 0; i < playerTileTrailsVector.size(); i++ )
	{
		if( playerTileTrailsVector[ i ]->checkIfExpired() == true )
		{
			PlayerTrail* breakingWallAnimation = new PlayerTrail(0, playerTileTrailsVector[ i ]->getPlayerTileTrailCollisionBox().x - 50, playerTileTrailsVector[ i ]->getPlayerTileTrailCollisionBox().y - 20);

			delete playerTileTrailsVector[ i ];
			playerTileTrailsVector[ i ] = nullptr;
			playerTileTrailsVector.erase(playerTileTrailsVector.begin() + i);
			//std::cout << "A Trail deleted" << "\n";

			breakingWallAnimationVector.push_back(breakingWallAnimation);
		}
	}
}


void destroyExpiredKillLines(std::vector<KillArea*>& killLinesVector) {
	for( int i = 0; i < killLinesVector.size(); i++ )
	{
		if( killLinesVector[ i ]->checkIfExpired() == true )
		{
			delete killLinesVector[ i ];
			killLinesVector[ i ] = nullptr;
			killLinesVector.erase(killLinesVector.begin() + i);
			//std::cout << "A line deleted" << "\n";
		}
	}
}

void renderBreakingWallAnimation(std::vector<PlayerTrail*>& breakingWallAnimationVector, Texture& wallBreakingTexture, std::array<SDL_Rect, BREAKING_WALL_ANIMATION_FRAMES>& gWallBreakingSpriteClips, SDL_Rect& camera) {
	for( int i = 0; i < breakingWallAnimationVector.size(); i++ ) {
		if( breakingWallAnimationVector[i] != nullptr )
		{
			//std::cout << "Current breaking wall: " << breakingWallAnimationVector[ i ]->getCurrentBreakingWallFrame() << "\n";
			SDL_Rect* currentBreakingWallClip = &gWallBreakingSpriteClips[ breakingWallAnimationVector[ i ]->getCurrentBreakingWallFrame() / 4 ];

			breakingWallAnimationVector[ i ]->renderBreakingWall(camera, wallBreakingTexture, currentBreakingWallClip);
		}
	}
}

void destroyBreakingWallAnimation(std::vector<PlayerTrail*>& breakingWallAnimationVector) {
	// Increase the frame after rendering all objects
	for( int i = 0; i < breakingWallAnimationVector.size(); i++ ) {
		if( breakingWallAnimationVector[ i ] != nullptr )
		{
			breakingWallAnimationVector[ i ]->increaseCurrentBreakingWallFrame();
		}
	}

	for( int i = 0; i < breakingWallAnimationVector.size(); i++ ) {
		if( breakingWallAnimationVector[ i ] != nullptr )
		{
			if( breakingWallAnimationVector[ i ]->getCurrentBreakingWallFrame() / 4 >= BREAKING_WALL_ANIMATION_FRAMES )
			{
				delete breakingWallAnimationVector[ i ];
				breakingWallAnimationVector[ i ] = nullptr;
				breakingWallAnimationVector.erase(breakingWallAnimationVector.begin() + i);
			}
		}
	}
}

void deallocateBreakingWallAnimation(std::vector<PlayerTrail*>& breakingWallAnimationVector) {
	for( int i = 0; i < breakingWallAnimationVector.size(); i++ )
	{
		if( breakingWallAnimationVector[ i ] != nullptr ) {
			delete breakingWallAnimationVector[ i ];
			breakingWallAnimationVector[ i ] = nullptr;
		}
	}
	std::cout << "Deallocated all breaking wall animation\n";
}

void renderDeadNPCs(std::vector<HorizontalZombie*>& deadHorizontalZombiesVector, SDL_Rect& gDeadZombieClip, SDL_Rect& camera, Texture& deadZombieSpirteSheetTexture) {
	for( int i = 0; i < deadHorizontalZombiesVector.size(); i++ )
	{
		SDL_Rect* deadZombieClip = &gDeadZombieClip;

		deadHorizontalZombiesVector[ i ]->renderZombie(camera, deadZombieSpirteSheetTexture, deadZombieClip);
	}
}

void renderDeadNPCs(std::vector<VerticalZombie*>& deadVerticalZombiesVector, SDL_Rect& gDeadZombieClip, SDL_Rect& camera, Texture& deadZombieSpirteSheetTexture) {
	for( int i = 0; i < deadVerticalZombiesVector.size(); i++ )
	{
		SDL_Rect* deadZombieClip = &gDeadZombieClip;

		deadVerticalZombiesVector[ i ]->renderZombie(camera, deadZombieSpirteSheetTexture, deadZombieClip);
	}
}

void destroyDeadNPCsAnimation(std::vector<HorizontalZombie*>& deadHorizontalZombiesVector) {
	for( int i = 0; i < deadHorizontalZombiesVector.size(); i++ )
	{
		deadHorizontalZombiesVector[ i ]->decreaseCoprseDuration();
		if( deadHorizontalZombiesVector[ i ]->checkIfCorpseDurationExpired() == true )
		{
			delete deadHorizontalZombiesVector[ i ];
			deadHorizontalZombiesVector[ i ] = nullptr;
			deadHorizontalZombiesVector.erase(deadHorizontalZombiesVector.begin() + i);
		}
	}

}

void destroyDeadNPCsAnimation(std::vector<VerticalZombie*>& deadVerticalZombiesVector) {
	for( int i = 0; i < deadVerticalZombiesVector.size(); i++ )
	{
		deadVerticalZombiesVector[ i ]->decreaseCoprseDuration();
		if( deadVerticalZombiesVector[ i ]->checkIfCorpseDurationExpired() == true )
		{
			delete deadVerticalZombiesVector[ i ];
			deadVerticalZombiesVector[ i ] = nullptr;
			deadVerticalZombiesVector.erase(deadVerticalZombiesVector.begin() + i);
		}
	}

}

void deallocateDeadNPCsAnimation(std::vector<HorizontalZombie*>& deadHorizontalZombiesVector) {
	for( auto& deadHorizontalZombie : deadHorizontalZombiesVector )
	{
		if( deadHorizontalZombie != nullptr )
		{
			delete deadHorizontalZombie;
			deadHorizontalZombie = nullptr;
		}
	}
}

void deallocateDeadNPCsAnimation(std::vector<VerticalZombie*>& deadVerticalZombiesVector) {
	for( auto& deadVerticalZombies : deadVerticalZombiesVector )
	{
		if( deadVerticalZombies != nullptr )
		{
			delete deadVerticalZombies;
			deadVerticalZombies = nullptr;
		}
	}
}

void resetGame( int& deadScreenTimer, Player& player, int& playerActionCheck, std::vector<HorizontalZombie*>& horizontalZombiesVector, std::vector<VerticalZombie*>& verticalZombiesVector, std::vector<Ghost*>& ghostsVector, std::vector<PlayerTrail*>& playerTileTrailsVector, std::vector<KillArea*>& killLinesVector, std::vector<PlayerTrail*>& breakingAllWallsAnimationVector, Text& scoreCounter, int& highscoreShowOnScreenTimer, bool& highscoreHit, int& loadedHighscore, int& countdownByFrameTimer) {
	int delayGameOverScreenTimer = 1000;
	while( delayGameOverScreenTimer > 0 )
	{
		killThemAll(horizontalZombiesVector, verticalZombiesVector );
		deallocatePlayerTrails(playerTileTrailsVector);
		deallocateKillLine(killLinesVector);
		//deallocateBreakingWallAnimation(breakingWallAnimationVector);
		deallocateAllBreakingWallsAnimation(breakingAllWallsAnimationVector);
		delayGameOverScreenTimer--;
	}
	playerActionCheck = STANDING_STILL_FACING_RIGHT;
	player.setToDefault();
	deadScreenTimer = DEAD_SCREEN_DURATION;
	scoreCounter.setKillCount(0);
	highscoreShowOnScreenTimer = HIGHSCORE_ALERT_DURATION;
	highscoreHit = false;
	loadedHighscore = loadHighscoreFromFile("saves/highscore.txt");
	countdownByFrameTimer = TIME_LEFT_TO_KILL;
}