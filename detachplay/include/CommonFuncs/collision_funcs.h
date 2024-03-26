#pragma once

#include "../Constants/common_constants.h"
#include "../entities/Tile.h"
#include "../entities/PlayerTrail.h"
#include "../entities/KillArea.h"
#include "../entities/HorizontalZombie.h"
#include "../entities/VerticalZombie.h"
#include "../entities/Player.h"
#include "../entities/Ghost.h"
#include "../CustomStructs/CustomStructs.h"

#include <SDL.h>
#include <SDL_mixer.h>

#include <algorithm>
#include <vector>
#include <tuple>

class Tile;
class PlayerTrail;
class KillArea;
class HorizontalZombie;
class Player;
class Ghost;
class VerticalZombie;

bool checkCollision(const SDL_Rect& a, const SDL_Rect& b);
bool checkCollisionWithNPC(const SDL_Rect& a, const SDL_Rect& b);
bool checkKillLineCollision(const KillLinePos& a, const KillLinePos& b);

bool touchesTileWall(SDL_Rect box, std::array<Tile*, TOTAL_TILES>& tiles);

const std::tuple<bool, SDL_Rect, SDL_Rect> isCurrentTrailCollideWithPrevious(const std::vector<PlayerTrail*>& playerTileTrailsVector);
const std::tuple<bool, int, int> isCurrentKillLineCollideWithPrevious(const std::vector<KillArea*>& killLinesVector);

void makeKillZonePolygonVector(std::vector<KillArea*>& killLineVector, std::vector<KillArea*>& killZonePolygonVector, int& currentKillLineIndex, int& prevCollidedKillLineIndex);
void destroyKillZonePolygonVector(std::vector<KillArea*>& killZonePolygonVector);
//void spawnConnectLineForKillZonePolygonVector(const int& currentKillLineIndex, const int& prevCollidedKillLineIndex, std::vector<KillArea*>& killZonePolygonVector, std::vector <KillArea*>& killLinesVector);

bool NPCinsideKillAreaPolygon(const SDL_Rect& NPCKillCollisionBox, std::vector<KillArea*>& killZonePolygonVector);
std::vector<PlayerTrail*> getTrailsFormingPolygon(const std::vector<PlayerTrail*>& playerTileTrailsVector);

void createBreakingAllWallsAnimation(std::vector<PlayerTrail*>& playerTileTrailsVector, std::vector<PlayerTrail*>& breakingAllWallsAnimationVector, std::array<SDL_Rect, BREAKING_WALL_ANIMATION_FRAMES>& gWallBreakingSpriteClips, Texture& wallBreakingTexture);

bool renderBreakingAllWallsAnimation(std::vector<PlayerTrail*>& breakingAllWallsAnimationVector, Texture& wallBreakingTexture, std::array<SDL_Rect, BREAKING_WALL_ANIMATION_FRAMES>& gWallBreakingSpriteClips, SDL_Rect& camera, Mix_Chunk*& gBreakingBricks);

void destroyAllBreakingWallsAnimation(std::vector<PlayerTrail*>& breakingAllWallsAnimationVector);
void deallocateAllBreakingWallsAnimation(std::vector<PlayerTrail*>& breakingAllWallsAnimationVector);

bool checkIfNPCTouchPlayer(std::vector<HorizontalZombie*>& horizontalZombiesVector, Player& player);
bool checkIfNPCTouchPlayer(std::vector<VerticalZombie*>& verticalZombiesVector, Player& player);
bool checkIfNPCTouchPlayer(std::vector<Ghost*>& ghostsVector, Player& player);

void renderDeadPlayer(Player& deadPlayer, SDL_Rect& gDeadPlayerClip, SDL_Rect& camera, Texture& deadPlayerSpriteSheetTexture);
void decreasePlayerCorpseDurationAnimation(Player& deadPlayer, bool& isDeadPlayerDeallocated);
void deallocateDeadPlayer(Player& deadPlayer);