#include "../include/CommonFuncs/collision_funcs.h"
bool checkCollision(const SDL_Rect& a, const SDL_Rect& b)
{
	//The sides of the rectangles
	int leftA, leftB;
	int rightA, rightB;
	int topA, topB;
	int bottomA, bottomB;

	//Calculate the sides of rect A
	leftA = a.x;
	rightA = a.x + a.w;
	topA = a.y;
	bottomA = a.y + a.h;

	//Calculate the sides of rect B
	leftB = b.x;
	rightB = b.x + b.w;
	topB = b.y;
	bottomB = b.y + b.h;

	//If any of the sides from A are outside of B
	if( bottomA <= topB )
	{
		return false;
	}

	if( topA >= bottomB )
	{
		return false;
	}

	if( rightA <= leftB )
	{
		return false;
	}

	if( leftA >= rightB )
	{
		return false;
	}

	//If none of the sides from A are outside B
	return true;
}

bool checkKillLineCollision(const KillLinePos& a, const KillLinePos& b)
{
	if( a.posX2 == b.posX1 && a.posY2 == b.posY1 )
	{
		return true;
	}
	return false;

}

bool checkCollisionWithNPC(const SDL_Rect& a, const SDL_Rect& b)
{
	//The sides of the rectangles
	int leftA, leftB;
	int rightA, rightB;
	int topA, topB;
	int bottomA, bottomB;

	//Calculate the sides of rect A
	leftA = a.x;
	rightA = a.x + a.w;
	topA = a.y;
	bottomA = a.y + a.h;

	//Calculate the sides of rect B
	leftB = b.x + 43;
	rightB = b.x + b.w - 10;
	topB = b.y - 50;
	bottomB = b.y + b.h - 10;

	//If any of the sides from A are outside of B
	if( bottomA <= topB )
	{
		return false;
	}

	if( topA >= bottomB )
	{
		return false;
	}

	if( rightA <= leftB )
	{
		return false;
	}

	if( leftA >= rightB )
	{
		return false;
	}

	//If none of the sides from A are outside B
	return true;
}


bool touchesTileWall(SDL_Rect box, std::array<Tile*, TOTAL_TILES>& tiles)
{
	//Go through the tiles
	for( int i = 0; i < TOTAL_TILES; ++i )
	{
		//If the tile is a wall type tile
		if( ( tiles[ i ]->getTileType() >= TILE_CENTER ) && ( tiles[ i ]->getTileType() <= TILE_TOPLEFT ) )
		{
			//If the collision box touches the wall tile
			if( checkCollision(box, tiles[ i ]->getCollisionBox()) )
			{
				return true;
			}
		}
	}

	//If no wall tiles were touched
	return false;
}

const std::tuple<bool, SDL_Rect, SDL_Rect> isCurrentTrailCollideWithPrevious(const std::vector<PlayerTrail*>& playerTileTrailsVector) {

	if( playerTileTrailsVector.size() < 5 )
	{
		const SDL_Rect& falseValues = { 0,0,0,0 };
		return { false, falseValues, falseValues };
	}

	const PlayerTrail* mostRecent = playerTileTrailsVector.back();
	const SDL_Rect& mostRecentRect = mostRecent->getPlayerTileTrailCollisionBox();

	for( size_t i = 0; i < playerTileTrailsVector.size() - 2; ++i ) {
		const PlayerTrail* previous = playerTileTrailsVector[ i ];
		const SDL_Rect& previousRect = previous->getPlayerTileTrailCollisionBox();

		if( checkCollision(mostRecentRect, previousRect) ) {
			// Collision detected
			std::cout << "Trail collided\n";
			return { true, mostRecentRect, previousRect };
		}
	}
	const SDL_Rect& falseValues = { 0,0,0,0 };
	return { false, falseValues, falseValues };
}

const std::tuple<bool, int, int> isCurrentKillLineCollideWithPrevious(const std::vector<KillArea*>& killLinesVector) {

	if( killLinesVector.size() < 5 )
	{
		//const KillLinePos& falseValues = { 0,0,0,0 };
		return std::make_tuple(false, 0, 0);
	}

	KillArea* mostRecentKillLine = killLinesVector.back();
	KillLinePos mostRecentKillLinePoss = { mostRecentKillLine->getCurrentKillPointPosX(), mostRecentKillLine->getCurrentKillPointPosY(), mostRecentKillLine->getPrevKillPointPosX(), mostRecentKillLine->getPrevKillPointPosY() };

	for( size_t i = 0; i < killLinesVector.size() - 2; ++i ) {
		KillArea* previousKillLine = killLinesVector[ i ];
		KillLinePos previousKillLinePoss = { previousKillLine->getCurrentKillPointPosX(), previousKillLine->getCurrentKillPointPosY(), previousKillLine->getPrevKillPointPosX(), previousKillLine->getPrevKillPointPosY() };

		if( checkKillLineCollision(mostRecentKillLinePoss, previousKillLinePoss) ) {
			// Collision detected
			std::cout << "Kill Line collided\n";
			int mostRecentIndex = killLinesVector.size() - 1;
			return { true, mostRecentIndex, i };
		}
	}
	//const KillLinePos& falseValues = { 0,0,0,0 };
	return { false, 0, 0 };
}

void makeKillZonePolygonVector(std::vector<KillArea*>& killLineVector, std::vector<KillArea*>& killZonePolygonVector, int& currentKillLineIndex, int& prevCollidedKillLineIndex) {

	for( int i = prevCollidedKillLineIndex + 1; i <= currentKillLineIndex; i++ )
	{
		KillArea* killZoneLinePolygon = new KillArea(killLineVector[ i ]->getCurrentKillPointPosX() - TILE_SIZE / 2, killLineVector[ i ]->getCurrentKillPointPosY() - TILE_SIZE / 2, killLineVector[ i ]->getPrevKillPointPosX() - TILE_SIZE / 2, killLineVector[ i ]->getPrevKillPointPosY() - TILE_SIZE / 2);
		killZonePolygonVector.push_back(killZoneLinePolygon);
	}
}

//void spawnConnectLineForKillZonePolygonVector(const int& currentKillLineIndex, const int& prevCollidedKillLineIndex, std::vector<KillArea*>& killZonePolygonVector, std::vector <KillArea*>& killLinesVector) {
//	int lastElementIndex = killLinesVector.size() - 1;
//
//	KillArea* killLine = new KillArea(killLinesVector[ lastElementIndex ]->getCurrentKillPointPosX(), killLinesVector[ lastElementIndex ]->getCurrentKillPointPosY(), 0, 0);
//	killLine->setPrevKillPointPosX(killLinesVector[ lastElementIndex ]->getPrevKillPointPosX());
//	killLine->setPrevKillPointPosY(killLinesVector[ lastElementIndex ]->getPrevKillPointPosY());
//
//	killZonePolygonVector.push_back(killLine);
//}

void destroyKillZonePolygonVector(std::vector<KillArea*>& killZonePolygonVector) {
	for( int i = 0; i < killZonePolygonVector.size(); i++ )
	{
		if( killZonePolygonVector[ i ] != nullptr ) {

			delete killZonePolygonVector[ i ];
			killZonePolygonVector[ i ] = 0;
			killZonePolygonVector.erase(killZonePolygonVector.begin() + i);
		}
	}
}

std::vector<PlayerTrail*> getTrailsFormingPolygon(const std::vector<PlayerTrail*>& playerTileTrailsVector) {
	std::vector<PlayerTrail*> polygonTrails;

	if( playerTileTrailsVector.size() < 5 ) {
		// If there are not enough trails, return an empty vector
		return polygonTrails;
	}

	const PlayerTrail* mostRecent = playerTileTrailsVector.back();
	const SDL_Rect& mostRecentRect = mostRecent->getPlayerTileTrailCollisionBox();

	for( size_t i = 0; i < playerTileTrailsVector.size() - 2; ++i ) {
		const PlayerTrail* previous = playerTileTrailsVector[ i ];
		const SDL_Rect& previousRect = previous->getPlayerTileTrailCollisionBox();

		if( checkCollision(mostRecentRect, previousRect) ) {
			// Collision detected
			std::cout << "Trail collided\n";
			polygonTrails.push_back(const_cast<PlayerTrail*>( mostRecent ));
			polygonTrails.push_back(const_cast<PlayerTrail*>( previous ));
		}
	}

	return polygonTrails;
}

bool NPCinsideKillAreaPolygon(const SDL_Rect& NPCKillCollisionBox, std::vector<KillArea*>& killZonePolygonVector) {

	int intersectCount = 0;
	size_t numVertices = killZonePolygonVector.size();

	for( size_t i = 0, j = numVertices - 1; i < numVertices; j = i++ ) {
		if( ( ( killZonePolygonVector[ i ]->getCurrentKillPointPosY() > NPCKillCollisionBox.y ) != ( killZonePolygonVector[ j ]->getCurrentKillPointPosY() > NPCKillCollisionBox.y ) ) &&
			( NPCKillCollisionBox.x < ( killZonePolygonVector[ j ]->getCurrentKillPointPosX() - killZonePolygonVector[ i ]->getCurrentKillPointPosX() ) * ( NPCKillCollisionBox.y - killZonePolygonVector[ i ]->getCurrentKillPointPosY() ) / ( killZonePolygonVector[ j ]->getCurrentKillPointPosY() - killZonePolygonVector[ i ]->getCurrentKillPointPosY() ) + killZonePolygonVector[ i ]->getCurrentKillPointPosX() ) ) {
			intersectCount++;
		}
	}

	return ( intersectCount % 2 == 1 );




	//double npcX = NPCKillCollisionBox.x + NPCKillCollisionBox.w / 2;  // NPC's center x-coordinate
	//double npcY = NPCKillCollisionBox.y + NPCKillCollisionBox.h / 2;  // NPC's center y-coordinate

	//double intersectCount = 0;

	//for( auto& line : killZonePolygonVector ) {
	//	// Check if the NPC center intersects with the current line
	//	if( ( ( line.getCurrentKillPointPosY() <= npcY && npcY < line.getPrevKillPointPosY() ) || ( line.getPrevKillPointPosY() <= npcY && npcY < line.getCurrentKillPointPosY() ) ) &&
	//		npcX < ( line.getPrevKillPointPosX() - line.getCurrentKillPointPosX() ) * ( npcY - line.getCurrentKillPointPosY() ) / ( line.getPrevKillPointPosY() - line.getCurrentKillPointPosY() ) + line.getCurrentKillPointPosX() ) {
	//		intersectCount++;
	//	}
	//}

	//// If the number of intersections is odd, the NPC is inside the polygon
	//return static_cast<int>( intersectCount ) % 2 == 1;


	//int windingNumber = 0;

	//int npcX = NPCKillCollisionBox.x + NPCKillCollisionBox.w / 2;  // NPC's center x-coordinate
	//int npcY = NPCKillCollisionBox.y + NPCKillCollisionBox.h / 2;  // NPC's center y-coordinate

	//for( auto& line : killZonePolygonVector ) {
	//	// Check if the NPC center is on the same side of the line
	//	if( line.getCurrentKillPointPosY() <= npcY && line.getPrevKillPointPosY() > npcY ) {
	//		double vt = ( npcY - line.getCurrentKillPointPosY() ) / ( line.getPrevKillPointPosY() - line.getCurrentKillPointPosY() );
	//		double intersectX = line.getCurrentKillPointPosX() + vt * ( line.getPrevKillPointPosX() - line.getCurrentKillPointPosX() );

	//		if( npcX < intersectX ) {
	//			windingNumber++;
	//		}
	//	}
	//	else if( line.getPrevKillPointPosY() <= npcY && line.getCurrentKillPointPosY() > npcY ) {
	//		double vt = ( npcY - line.getCurrentKillPointPosY() ) / ( line.getPrevKillPointPosY() - line.getCurrentKillPointPosY() );
	//		double intersectX = line.getCurrentKillPointPosX() + vt * ( line.getPrevKillPointPosX() - line.getCurrentKillPointPosX() );

	//		if( npcX < intersectX ) {
	//			windingNumber++;
	//		}
	//	}
	//}

	// If the winding number is not zero, the NPC is inside the polygon
	//return windingNumber % 2 != 0;
}

void createBreakingAllWallsAnimation(std::vector<PlayerTrail*>& playerTileTrailsVector, std::vector<PlayerTrail*>& breakingAllWallsAnimationVector, std::array<SDL_Rect, BREAKING_WALL_ANIMATION_FRAMES>& gWallBreakingSpriteClips, Texture& wallBreakingTexture) {
	for( int i = 0; i < playerTileTrailsVector.size(); i++ )
	{
		PlayerTrail* breakingWallAnimation = new PlayerTrail(0, playerTileTrailsVector[ i ]->getPlayerTileTrailCollisionBox().x - 50, playerTileTrailsVector[ i ]->getPlayerTileTrailCollisionBox().y - 20);

		breakingAllWallsAnimationVector.push_back(breakingWallAnimation);
	}
	//std::cout << "createBreakingAllWallsAnimation func, size of vector breakingAllWallsAnimationVector is: " << breakingAllWallsAnimationVector.size() << "\n";

}

bool renderBreakingAllWallsAnimation(std::vector<PlayerTrail*>& breakingAllWallsAnimationVector, Texture& wallBreakingTexture, std::array<SDL_Rect, BREAKING_WALL_ANIMATION_FRAMES>& gWallBreakingSpriteClips, SDL_Rect& camera, Mix_Chunk*& gBreakingBricks) {

	bool thereAreElements = false;
	if( breakingAllWallsAnimationVector.size() > 0 )
	{
		thereAreElements = true;
	}

	for( int i = 0; i < breakingAllWallsAnimationVector.size(); i++ ) {
		if( breakingAllWallsAnimationVector[ i ] != nullptr )
		{
			SDL_Rect* currentBreakingWallClip = &gWallBreakingSpriteClips[ breakingAllWallsAnimationVector[ i ]->getCurrentBreakingWallFrame() / 4 ];
			//std::cout << "Step 1: " << i << "\n";

			breakingAllWallsAnimationVector[ i ]->renderBreakingWall(camera, wallBreakingTexture, currentBreakingWallClip);
		}
	}

	return thereAreElements;
}

void destroyAllBreakingWallsAnimation(std::vector<PlayerTrail*>& breakingAllWallsAnimationVector) {
	// Increase the frame after rendering all objects
	for( int i = 0; i < breakingAllWallsAnimationVector.size(); i++ ) {
		if( breakingAllWallsAnimationVector[ i ] != nullptr )
		{
			//std::cout << "breakingAllWallsAnimationVector:" << i << "\n";
			breakingAllWallsAnimationVector[ i ]->increaseCurrentBreakingWallFrame();
		}

	}

	//ERROR IF CHANGE 3 TO 4
	for( int i = 0; i < breakingAllWallsAnimationVector.size(); i++ ) {
		if( breakingAllWallsAnimationVector[ i ] != nullptr )
		{
			if( breakingAllWallsAnimationVector[ i ]->getCurrentBreakingWallFrame() / 3 >= BREAKING_WALL_ANIMATION_FRAMES )
			{
				//std::cout << "deallocating breakingAllWallsAnimationVector:" << i << "\n";
				delete breakingAllWallsAnimationVector[ i ];
				breakingAllWallsAnimationVector[ i ] = nullptr;
				breakingAllWallsAnimationVector.erase(breakingAllWallsAnimationVector.begin() + i);
			}
		}
	}
}

void deallocateAllBreakingWallsAnimation(std::vector<PlayerTrail*>& breakingAllWallsAnimationVector) {
	for( auto& breakingAllWallsAnimation : breakingAllWallsAnimationVector )
	{
		if( breakingAllWallsAnimation != nullptr ) {
			delete breakingAllWallsAnimation;
			breakingAllWallsAnimation = nullptr;
		}
	}
	std::cout << "breakingAllWallsAnimation deallocated\n";
}

bool checkIfNPCTouchPlayer(std::vector<HorizontalZombie*>& horizontalZombiesVector, Player& player) {
	for( int i = 0; i < horizontalZombiesVector.size(); i++ )
	{
		if( checkCollisionWithNPC(horizontalZombiesVector[ i ]->getZombieCollisionBox(), player.getPlayerCollisionBox()) )
		{
			std::cout << "Game over\n";
			return true;
		}
	}
	return false;
}

bool checkIfNPCTouchPlayer(std::vector<VerticalZombie*>& verticalZombiesVector, Player& player) {
	for( int i = 0; i < verticalZombiesVector.size(); i++ )
	{
		if( checkCollisionWithNPC(verticalZombiesVector[ i ]->getZombieCollisionBox(), player.getPlayerCollisionBox()) )
		{
			std::cout << "Game over\n";
			return true;
		}
	}
	return false;
}

bool checkIfNPCTouchPlayer(std::vector<Ghost*>& ghostsVector, Player& player) {
	for( int i = 0; i < ghostsVector.size(); i++ )
	{
		if( checkCollisionWithNPC(ghostsVector[ i ]->getZombieCollisionBox(), player.getPlayerCollisionBox()) )
		{
			std::cout << "Game over\n";
			return true;
		}
	}
	return false;
}

void renderDeadPlayer(Player& deadPlayer, SDL_Rect& gDeadPlayerClip, SDL_Rect& camera, Texture& deadPlayerSpriteSheetTexture) {

	SDL_Rect* deadPlayerClip = &gDeadPlayerClip;

	deadPlayer.render(camera, deadPlayerSpriteSheetTexture, deadPlayerClip);

}

void decreasePlayerCorpseDurationAnimation(Player& deadPlayer, bool& isDeadPlayerDeallocated) {

	deadPlayer.decreaseCorpseDuration();
	/*if( deadPlayer.getCorpseDuration() <= 0 )
	{
		delete deadPlayer;
		deadPlayer = nullptr;
		isDeadPlayerDeallocated = true;
		std::cout << "Destroyed deadPlayer\n";
	}*/
}

void deallocateDeadPlayer(Player& deadPlayer) {
	/*if( deadPlayer != nullptr )
	{
		std::cout << "dead player deallocated\n";
		delete deadPlayer;
		deadPlayer = nullptr;
	}*/
}
