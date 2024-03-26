#pragma once

#include <SDL.h>
#include <array>

#include "../entities/Texture.h"
#include "../Constants/common_constants.h"

class Texture;
bool loadVerticalZombieMedia(Texture& verticalZombieSpriteSheetTexture, std::array<SDL_Rect, WALKING_ANIMATION_FRAMES>& gZombieWalkingDownSpriteClips);
bool loadHorizontalZombieMedia(Texture& horizontalZombieSpriteSheetTexture, std::array<SDL_Rect, WALKING_ANIMATION_FRAMES>& gZombieWalkingRightSpriteClips, Texture& deadZombieSpriteSheetTexture, SDL_Rect& gDeadZombieClip);
bool loadGhostMedia(Texture& ghostSpriteSheetTexture, std::array<SDL_Rect, WALKING_ANIMATION_FRAMES>& ghostSpriteClips);