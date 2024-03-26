#pragma once
#include "../entities/HorizontalZombie.h"
#include "../entities/PlayerTrail.h"
#include "../entities/Tile.h"
#include "../entities/KillArea.h"
#include "../entities/VerticalZombie.h"
#include "../entities/Ghost.h"
#include "../score/Text.h"

#include "../Constants/common_constants.h"
#include "../Constants/npc_constants.h"

#include "../Enums/menu_enum.h"

#include "../include/CommonFuncs/read_write_files_funcs.h"

#include <array>
#include <vector>

class HorizontalZombie;
class PlayerTrail;
class KillArea;
class Tile;
class Text;
class VerticalZombie;
class Ghost;

void deallocatePlayerTrails(std::vector<PlayerTrail*>& playerTileTrailsVector);

void deallocateTileSet(std::array<Tile*, TOTAL_TILES>& tileSet);

void killThemAll(std::vector<HorizontalZombie*>& horizontalZombiesVector, std::vector<VerticalZombie*>& verticalZombiesVector);

void deallocateKillLine(std::vector<KillArea*>& killLinesVector);

void destroyExpiredTrails(std::vector<PlayerTrail*>& playerTileTrailsVector, std::array<SDL_Rect, BREAKING_WALL_ANIMATION_FRAMES>& gWallBreakingSpriteClips, Texture& wallBreakingTexture, std::vector<PlayerTrail*>& breakingWallAnimationVector);
void destroyExpiredKillLines(std::vector<KillArea*>& killLinesVector);


void renderBreakingWallAnimation(std::vector<PlayerTrail*>& breakingWallAnimationVector, Texture& wallBreakingTexture, std::array<SDL_Rect, BREAKING_WALL_ANIMATION_FRAMES>& gWallBreakingSpriteClips, SDL_Rect& camera);
void destroyBreakingWallAnimation(std::vector<PlayerTrail*>& breakingWallAnimationVector);

void deallocateBreakingWallAnimation(std::vector<PlayerTrail*>& breakingWallAnimationVector);

void renderDeadNPCs(std::vector<HorizontalZombie*>& deadHorizontalZombiesVector, SDL_Rect& gDeadZombieClip, SDL_Rect& camera, Texture& deadZombieSpirteSheetTexture);
void renderDeadNPCs(std::vector<VerticalZombie*>& deadVerticalZombiesVector, SDL_Rect& gDeadZombieClip, SDL_Rect& camera, Texture& deadZombieSpirteSheetTexture);

void destroyDeadNPCsAnimation(std::vector<HorizontalZombie*>& deadHorizontalZombiesVector);
void destroyDeadNPCsAnimation(std::vector<VerticalZombie*>& deadHorizontalZombiesVector);

void deallocateDeadNPCsAnimation(std::vector<HorizontalZombie*>& deadHorizontalZombiesVector);
void deallocateDeadNPCsAnimation(std::vector<VerticalZombie*>& deadVerticalZombiesVector);

void resetGame(int& deadScreenTimer, Player& player, int& playerActionCheck, std::vector<HorizontalZombie*>& horizontalZombiesVector, std::vector<VerticalZombie*>& verticalZombiesVector, std::vector<Ghost*>& ghostsVector, std::vector<PlayerTrail*>& playerTileTrailsVector, std::vector<KillArea*>& killLinesVector, std::vector<PlayerTrail*>& breakingAllWallsAnimationVector, Text& scoreCounter, int& highscoreShowOnScreenTimer, bool& highscoreHit, int& loadedHighscore, int& countdownByFrameTimer);
