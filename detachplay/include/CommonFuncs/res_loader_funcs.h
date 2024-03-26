#pragma once
#include <SDL.h>
#include <SDL_mixer.h>

#include <array>

#include "../entities/Player.h"
#include "../Constants/common_constants.h"


bool loadPlayerMedia(Texture& playerSpriteSheetTexture, std::array<SDL_Rect, WALKING_ANIMATION_FRAMES>& gPlayerWalkingLeftSpriteClips, std::array<SDL_Rect, WALKING_ANIMATION_FRAMES>& gPlayerWalkingRightSpriteClips, std::array<SDL_Rect, WALKING_ANIMATION_FRAMES>& gPlayerWalkingUpSpriteClips, std::array<SDL_Rect, WALKING_ANIMATION_FRAMES>& gPlayerWalkingDownSpriteClips, Texture& deadPlayerSpriteSheetTexture, SDL_Rect& gDeadPlayerSpriteClip);

bool loadBackgroundMedia(Texture& backgroundTexture);

bool setTiles(std::array<Tile*, TOTAL_TILES>& tiles, std::array<SDL_Rect, TOTAL_TILE_SPRITES>& gTileClips);

bool loadTilesMedia(std::array<Tile*, TOTAL_TILES>& tiles, Texture& tileTexture, std::array<SDL_Rect, TOTAL_TILE_SPRITES>& gTileClips);

bool loadBreakingWallMedia(Texture& breakingWallSpriteSheetTexture, std::array<SDL_Rect, BREAKING_WALL_ANIMATION_FRAMES>& gWallBreakingSpriteClips);

bool loadFontMedia(TTF_Font*& gFont, Texture& textTexture, SDL_Renderer* gRenderer);

bool loadMenuMedia(Texture& chooseArrowTexture, Texture& introChooseArrowTexture, Texture& pauseChooseArrowTexture, Texture& logoTexture, SDL_Renderer* gRenderer);

bool loadSoundEffects(Mix_Chunk*& gChangeSelection, Mix_Chunk*& gBreakingBricks, Mix_Chunk*& gDeadSound, Mix_Chunk*& gZombieDeadSound);

bool loadMusic(Mix_Music*& gMainMenu, Mix_Music*& gPlayingMusic, Mix_Music*& gDeadMusic);