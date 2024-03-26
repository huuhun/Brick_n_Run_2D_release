#pragma once

#include "../include/Enums/moving_enum.h"

#include "../entities/Player.h"
#include "../entities/Texture.h"
#include "../entities/PlayerTrail.h"
#include "../entities/KillArea.h"

#include "collision_funcs.h"

#include <vector>
#include <array>

#include <SDL.h>
#include <SDL_mixer.h>

class Player;
class Texture;
class PlayerTrail;
class KillArea;

//void renderKillLine(SDL_Rect& camera, SDL_Renderer* gRenderer, const SDL_Rect& currentPlayerTrailCollisionBox, const SDL_Rect& previousPlayerTrailCollisionBox);

//void connectLineAndRender(SDL_Rect& camera, SDL_Renderer* gRenderer, const SDL_Rect& currentPlayerTrailCollisionBox, const SDL_Rect& previousCollidedPlayerTrailCollisionBox);
void spawnConnectLine(const SDL_Rect& mostRecentTrail, const SDL_Rect& prevTrail, std::vector<KillArea*>& killLinesVector);

void renderPlayerMovingTextureAction(int& playerActionCheck, Player& player, SDL_Rect& camera, int& currentFrame, int& playerTimeStep, Texture& playerSpriteSheetTexture, std::array<SDL_Rect, WALKING_ANIMATION_FRAMES>& gPlayerWalkingDownSpriteClips, std::array<SDL_Rect, WALKING_ANIMATION_FRAMES>& gPlayerWalkingUpSpriteClips, std::array<SDL_Rect, WALKING_ANIMATION_FRAMES>& gPlayerWalkingLeftSpriteClips, std::array<SDL_Rect, WALKING_ANIMATION_FRAMES>& gPlayerWalkingRightSpriteClips, std::vector<PlayerTrail*>& playerTileTrailsVector, std::vector<KillArea*>& killLinesVector, Texture& wallBreakingTexture, std::array<SDL_Rect, BREAKING_WALL_ANIMATION_FRAMES>& gWallBreakingSpriteClips);
