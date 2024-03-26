#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <vector>
#include <array>
#include <sstream>

#ifdef _WIN32
#include <windows.h>
#endif

#include "../include/Constants/common_constants.h"
#include "../include/Constants/npc_constants.h"

#include "../include/window/WindowManager.h"
#include "../include/entities/Texture.h"
#include "../include/entities/Player.h"
#include "../include/entities/Tile.h"
#include "../include/entities/PlayerTrail.h"
#include "../include/entities/HorizontalZombie.h"
#include "../include/entities/VerticalZombie.h"
#include "../include/entities/KillArea.h"
#include "../include/entities/Menu.h"
#include "../include/score/Text.h"

#include "../include/Enums/moving_enum.h"
#include "../include/Enums/menu_enum.h"

#include "../include/CustomStructs/CustomStructs.h"

#include "../include/CommonFuncs/res_loader_funcs.h"
#include "../include/CommonFuncs/npc_res_loader_funcs.h"
#include "../include/CommonFuncs/render_player_movement_func.h"
#include "../include/CommonFuncs/spawner_funcs.h"
#include "../include/CommonFuncs/despawner_funcs.h"
#include "../include/CommonFuncs/collision_funcs.h"
#include "../include/CommonFuncs/window_funcs.h"
#include "../include/CommonFuncs/read_write_files_funcs.h"

int main(int argc, char* argv[])
{
	#ifdef _WIN32
    // Hide the console window on Windows
    FreeConsole();
#endif

	SDL_Window* gWindow = nullptr;
	SDL_Renderer* gRenderer = nullptr;
	WindowManager* gGameWindow = new WindowManager(gWindow, gRenderer);

	TTF_Font* gFont = nullptr;

	Mix_Chunk* gChangeSelection = nullptr;
	Mix_Chunk* gBreakingBricks = nullptr;
	Mix_Chunk* gDeadSound = nullptr;
	Mix_Chunk* gZombieDeadSound = nullptr;

	Mix_Music* gMainMenuMusic = nullptr;
	Mix_Music* gPlayingMusic = nullptr;
	Mix_Music* gDeadMusic = nullptr;

	std::array<SDL_Rect, WALKING_ANIMATION_FRAMES> gPlayerWalkingRightSpriteClips;
	std::array<SDL_Rect, WALKING_ANIMATION_FRAMES> gPlayerWalkingLeftSpriteClips;
	std::array<SDL_Rect, WALKING_ANIMATION_FRAMES> gPlayerWalkingUpSpriteClips;
	std::array<SDL_Rect, WALKING_ANIMATION_FRAMES> gPlayerWalkingDownSpriteClips;
	SDL_Rect gDeadPlayerClip;

	std::array<SDL_Rect, TOTAL_TILE_SPRITES> gTileClips;

	std::array<SDL_Rect, WALKING_ANIMATION_FRAMES> gZombieWalkingRightSpriteClips;
	std::array<SDL_Rect, WALKING_ANIMATION_FRAMES> gZombieWalkingDownSpriteClips;
	std::array<SDL_Rect, WALKING_ANIMATION_FRAMES> ghostSpriteClips;
	SDL_Rect gDeadZombieClip;

	std::array<SDL_Rect, BREAKING_WALL_ANIMATION_FRAMES> gWallBreakingSpriteClips;
	//-------------------------------------------------------------------------
	if( !gGameWindow->init() )
	{
		std::cout << "Failed to initialize!\n";
	}
	else
	{
		//--------------------------
		Texture backgroundTexture(gGameWindow->getRenderer());

		Texture playerSpriteSheetTexture(gGameWindow->getRenderer());
		Texture deadPlayerSpriteSheetTexture(gGameWindow->getRenderer());

		Texture tileTexture(gGameWindow->getRenderer());
		Texture wallBreakingTexture(gGameWindow->getRenderer());
		//-----
		Texture horizontalZombieSpirteSheetTexture(gGameWindow->getRenderer());
		Texture deadZombieSpirteSheetTexture(gGameWindow->getRenderer());

		Texture verticalZombieSpirteSheetTexture(gGameWindow->getRenderer());

		Texture ghostSpirteSheetTexture(gGameWindow->getRenderer());
		//-----
		Texture scoreLabelTexture(gGameWindow->getRenderer());

		Texture chooseArrowTexture(gGameWindow->getRenderer());

		Texture introChooseArrowTexture(gGameWindow->getRenderer());
		Texture logoTexture(gGameWindow->getRenderer());

		Texture pauseChooseArrowTexture(gGameWindow->getRenderer());
		//--------------------------

		std::array<Tile*, TOTAL_TILES> tileSet;

		std::vector<PlayerTrail*> playerTileTrailsVector;
		std::vector<PlayerTrail*> breakingWallAnimationVector;
		std::vector<PlayerTrail*> breakingAllWallsAnimationVector;
		std::vector<PlayerTrail*> polygonTrails;

		std::vector<KillArea*> killLinesVector;
		std::vector<KillArea*> killZonePolygonVector;

		std::vector<HorizontalZombie*> horizontalZombiesVector;
		std::vector<HorizontalZombie*> deadHorizontalZombiesVector;

		std::vector<VerticalZombie*> verticalZombiesVector;
		std::vector<VerticalZombie*> deadVerticalZombiesVector;

		std::vector<Ghost*> ghostsVector;

		Text scoreCounter(800, 1, 0, 0);

		Menu chooseArrow(SCREEN_WIDTH / 2 - 85, SCREEN_HEIGHT / 2 - 3);
		Menu introChooseArrow(SCREEN_WIDTH / 2 + 46, SCREEN_HEIGHT / 2 - 150);
		Menu pauseChooseArrow(SCREEN_WIDTH / 2 - 90, SCREEN_HEIGHT / 2 - 20);

		//Load everythiing
		int loadedHighscore = loadHighscoreFromFile("saves/highscore.txt");
		std::cout << "Loaded number: " << loadedHighscore << std::endl;

		if( !loadPlayerMedia(playerSpriteSheetTexture, gPlayerWalkingLeftSpriteClips, gPlayerWalkingRightSpriteClips, gPlayerWalkingUpSpriteClips, gPlayerWalkingDownSpriteClips, deadPlayerSpriteSheetTexture, gDeadPlayerClip)
			|| !loadTilesMedia(tileSet, tileTexture, gTileClips) || !loadBreakingWallMedia(wallBreakingTexture, gWallBreakingSpriteClips) || !loadFontMedia(gFont, scoreLabelTexture, gGameWindow->getRenderer()) || !loadMenuMedia(chooseArrowTexture, introChooseArrowTexture, pauseChooseArrowTexture, logoTexture, gGameWindow->getRenderer()) ) {
			std::cerr << "Failed to load media!\n";
		}
		else if( !loadHorizontalZombieMedia(horizontalZombieSpirteSheetTexture, gZombieWalkingRightSpriteClips, deadZombieSpirteSheetTexture, gDeadZombieClip) || !loadVerticalZombieMedia(verticalZombieSpirteSheetTexture, gZombieWalkingDownSpriteClips) || !loadGhostMedia(ghostSpirteSheetTexture, ghostSpriteClips) )
		{
			std::cerr << "Failed to load NPCs media!\n";
		}
		else if( !loadSoundEffects(gChangeSelection, gBreakingBricks, gDeadSound, gZombieDeadSound) || !loadMusic(gMainMenuMusic, gPlayingMusic, gDeadMusic) )
		{
			std::cerr << "Failed to sound or music media!\n";
		}
		else {
			Player player(playerSpriteSheetTexture.getTextureWidth(), playerSpriteSheetTexture.getTextureHeight());
			Player deadPlayer(deadPlayerSpriteSheetTexture.getTextureWidth(), deadPlayerSpriteSheetTexture.getTextureHeight());

			spawnATestHorizontalZombies(horizontalZombieSpirteSheetTexture, horizontalZombiesVector);
			//--------------------------
			bool quit = false;

			SDL_Event e;

			int currentPlayerFrame = 0;

			int playerTimeStep = 0;

			int generalTimer = 1;
			int deadScreenTimer = DEAD_SCREEN_DURATION;
			int loadScreenTimer = 30;
			int countdownByFrameTimer = TIME_LEFT_TO_KILL;

			int menuState = INTRO_MENU;

			int highscoreShowOnScreenTimer = HIGHSCORE_ALERT_DURATION;
			bool highscoreHit = false;

			int playerActionCheck = STANDING_STILL_FACING_RIGHT;

			bool spawnAnotherKillLineYet = true;
			bool isDeadPlayerDeallocated = false;

			bool isCollidedWithWall = false;

			bool isAllBreakingWallsAnimationRendered = false;

			SDL_Rect camera = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
			SDL_Color textColor = { 0, 0, 0, 255 };

			Mix_PlayMusic(gMainMenuMusic, -1);
			while( !quit )
			{
				while( SDL_PollEvent(&e) != 0 )
				{
					//User requests quit
					if( e.type == SDL_QUIT )
					{
						quit = true;
					}
					if( !player.getIsDead())
					{
						player.handleEvent(e, playerActionCheck);
					}
					if( player.getIsDead() && menuState == DEAD_MENU )
					{
						chooseArrow.handleEvent(e, menuState, gChangeSelection);
					}
					if( menuState == INTRO_MENU ) {
						introChooseArrow.handleEvent(e, menuState, gChangeSelection);
					}
					if( e.type == SDL_KEYDOWN && e.key.repeat == 0 && e.key.keysym.sym == SDLK_ESCAPE && menuState != DEAD_MENU && menuState != INTRO_MENU )
					{
						menuState = PAUSED;
					}
					if( menuState == PAUSED )
					{
						pauseChooseArrow.handleEvent(e, menuState, gChangeSelection);
					}
				}

				if( menuState == INTRO_MENU )
				{
					//std::cout << "HEY\n";
					int introDecision = showIntroMenu(gGameWindow, gFont, introChooseArrowTexture, introChooseArrow, logoTexture, menuState);

					if( introDecision == EXIT )
					{
						quit = true;
						std::cout<<"HEY I'M QUIT\n";
					}
					else if( introDecision == PLAY )
					{
						menuState = PLAYING;
						Mix_PlayMusic(gPlayingMusic, -1);
					}
					else if( introDecision == CHOOSE_TUTORIAL )
					{
						menuState = TUTORIAL;
					}
				}
				if( menuState == TUTORIAL )
				{
					std::cout << "YO\n";
				}
				if( menuState == PAUSED )
				{
					if( showPauseMenu(gGameWindow, gFont, pauseChooseArrowTexture, pauseChooseArrow, menuState) == BACK_TO_MENU ) {
						resetGame(deadScreenTimer, player, playerActionCheck, horizontalZombiesVector, verticalZombiesVector,ghostsVector, playerTileTrailsVector, killLinesVector, breakingAllWallsAnimationVector, scoreCounter, highscoreShowOnScreenTimer, highscoreHit, loadedHighscore, countdownByFrameTimer);
						Mix_PlayMusic(gMainMenuMusic, -1);
					}
				}

				if( player.getIsDead() && deadScreenTimer == 0 && menuState == DEAD_MENU )
				{
					//Mix_PauseMusic();
					int deadDecision = showDeadMenu(gGameWindow, gFont, chooseArrowTexture, chooseArrow, menuState);
					if( deadDecision == PLAY_TRY_AGAIN )
					{
						Mix_PlayMusic(gPlayingMusic, -1);
						resetGame(deadScreenTimer, player, playerActionCheck, horizontalZombiesVector, verticalZombiesVector, ghostsVector,playerTileTrailsVector, killLinesVector, breakingAllWallsAnimationVector, scoreCounter, highscoreShowOnScreenTimer, highscoreHit, loadedHighscore, countdownByFrameTimer);
					}
					else if( deadDecision == BACK_TO_MENU )
					{
						Mix_PlayMusic(gMainMenuMusic, -1);
						resetGame(deadScreenTimer, player, playerActionCheck, horizontalZombiesVector, verticalZombiesVector, ghostsVector,playerTileTrailsVector, killLinesVector, breakingAllWallsAnimationVector, scoreCounter, highscoreShowOnScreenTimer, highscoreHit, loadedHighscore, countdownByFrameTimer);
					}
				}

				if( menuState == PLAYING )
				{
					if( !player.getIsDead())
					{
						player.setCamera(camera);
						player.movePlayer(tileSet, isCollidedWithWall);
					}
					if( player.getIsDead() )
					{
						Mix_PlayMusic(gDeadMusic, -1);

						if( Mix_Playing(PLAYER_SOUND_CHANNEL) == 0 ) {
							Mix_PlayChannel(PLAYER_SOUND_CHANNEL, gDeadSound, 0);
						}

						deadPlayer.setPlayerCollisionBoxPosX(player.getPlayerCollisionBox().x);
						deadPlayer.setPlayerCollisionBoxPosY(player.getPlayerCollisionBox().y);
					}
					//Handle zombie spawning
					if( horizontalZombiesVector.size() < MAX_ZOMBIE_AMOUNT && generalTimer % 30 == 0 )
					{
						spawnNPC(horizontalZombieSpirteSheetTexture, horizontalZombiesVector);
					}
					if( verticalZombiesVector.size() < MAX_VERTICAL_ZOMBIE_AMOUNT && generalTimer % 30 == 0 && scoreCounter.getKillCount() > KILL_AMOUNT_TO_SPAWN_VERTICAL_ZOMBIE )
					{
						spawnNPC(verticalZombieSpirteSheetTexture, verticalZombiesVector);
					}
					if( ghostsVector.size() < 1 && generalTimer % 30 == 0 && scoreCounter.getKillCount() > KILL_AMOUNT_TO_SPAWN_GHOST )
					{
						spawnNPC(ghostSpirteSheetTexture, ghostsVector);
					}

					//Move zombies
					for( int i = 0; i < horizontalZombiesVector.size(); i++ )
					{
						horizontalZombiesVector[ i ]->moveZombie();

						if( horizontalZombiesVector[ i ]->getIsOutOfBounds() )
						{
							if( horizontalZombiesVector[ i ] != nullptr )
							{
								delete horizontalZombiesVector[ i ];
								horizontalZombiesVector[ i ] = nullptr;
								horizontalZombiesVector.erase(horizontalZombiesVector.begin() + i);
								std::cout << "A zombie and its killbox in horizontalZombiesVector deallocated for running out of bounds\n";
							}
						}
					}
					for( int i = 0; i < verticalZombiesVector.size(); i++ )
					{
						verticalZombiesVector[ i ]->moveZombie();

						if( verticalZombiesVector[ i ]->getIsOutOfBounds() )
						{
							if( verticalZombiesVector[ i ] != nullptr )
							{
								delete verticalZombiesVector[ i ];
								verticalZombiesVector[ i ] = nullptr;
								verticalZombiesVector.erase(verticalZombiesVector.begin() + i);
							}
						}
					}
					for( int i = 0; i < ghostsVector.size(); i++ )
					{
						ghostsVector[ i ]->move(player.getPlayerCollisionBox());

						if( ghostsVector[ i ]->getIsOutOfBounds() )
						{
							if( ghostsVector[ i ] != nullptr )
							{
								delete ghostsVector[ i ];
								ghostsVector[ i ] = nullptr;
								ghostsVector.erase(ghostsVector.begin() + i);
							}
						}
					}

					if( checkIfNPCTouchPlayer(horizontalZombiesVector, player) || checkIfNPCTouchPlayer(verticalZombiesVector, player) || checkIfNPCTouchPlayer(ghostsVector, player) || countdownByFrameTimer < 150 )
					{
						player.setIsDeadToTrue();
					}

					gGameWindow->clearScreen();

					//Render level
					for( int i = 0; i < TOTAL_TILES; ++i )
					{
						tileSet[ i ]->render(camera, tileTexture, gTileClips);
					}

					for( int i = 0; i < playerTileTrailsVector.size(); ++i ) {

						playerTileTrailsVector[ i ]->renderPlayerTrail(camera, tileTexture, gTileClips);
					}

					/*for( int i = 1; i < killLinesVector.size(); i++ )
					{
						killLinesVector[ i ]->renderKillLine(camera, gGameWindow->getRenderer());
					}*/

					capFrameRate();

					if( !player.getIsDead() )
					{
						renderPlayerMovingTextureAction(playerActionCheck, player, camera, currentPlayerFrame, playerTimeStep, playerSpriteSheetTexture, gPlayerWalkingDownSpriteClips, gPlayerWalkingUpSpriteClips, gPlayerWalkingLeftSpriteClips, gPlayerWalkingRightSpriteClips, playerTileTrailsVector, killLinesVector, wallBreakingTexture, gWallBreakingSpriteClips);
					}

					//check if recent trail collide with any previous trails
					auto& trailCollisionResult = isCurrentTrailCollideWithPrevious(playerTileTrailsVector);
					const bool& trailCollisionOccurred = std::get<0>(trailCollisionResult);
					if( !player.getIsDead() && trailCollisionOccurred && spawnAnotherKillLineYet )
					{
						const SDL_Rect& mostRecentTrail = std::get<1>(trailCollisionResult);
						const SDL_Rect& prevTrail = std::get<2>(trailCollisionResult);
						spawnConnectLine(mostRecentTrail, prevTrail, killLinesVector);
						spawnAnotherKillLineYet = false;
					}

					//check if recent killline collide with any previous
					auto [killLineCollidedWithPrevOccured, currentKillLineIndex, prevCollidedKillLineIndex] = isCurrentKillLineCollideWithPrevious(killLinesVector);
					if( !player.getIsDead() && killLineCollidedWithPrevOccured )
					{
						makeKillZonePolygonVector(killLinesVector, killZonePolygonVector, currentKillLineIndex, prevCollidedKillLineIndex);
					}

					/*for( int i = 1; i < killZonePolygonVector.size(); i++ )
					{
						killZonePolygonVector[ i ]->renderKillAreaPolygon(camera, gGameWindow->getRenderer());
					}*/

					if( !player.getIsDead() && killLineCollidedWithPrevOccured )
					{
						for( int i = 0; i < horizontalZombiesVector.size(); i++ )
						{
							if( NPCinsideKillAreaPolygon(horizontalZombiesVector[ i ]->getZombieCollisionBox(), killZonePolygonVector) )
							{
								HorizontalZombie* deadHorizontalZombie = new HorizontalZombie(deadZombieSpirteSheetTexture.getTextureWidth(), deadZombieSpirteSheetTexture.getTextureHeight());
								deadHorizontalZombie->setZombieCollisionBoxPosX(horizontalZombiesVector[ i ]->getZombieCollisionBox().x);
								deadHorizontalZombie->setZombieCollisionBoxPosY(horizontalZombiesVector[ i ]->getZombieCollisionBox().y);
								deadHorizontalZombiesVector.push_back(deadHorizontalZombie);

								horizontalZombiesVector[ i ]->destroySelf(horizontalZombiesVector[ i ]);
								horizontalZombiesVector.erase(horizontalZombiesVector.begin() + i);
								countdownByFrameTimer += 300;

								if( Mix_Playing(NPC_DEAD_SOUND_CHANNEL) == 0 ) {
									Mix_PlayChannel(NPC_DEAD_SOUND_CHANNEL, gZombieDeadSound, 0);
								}

								scoreCounter.increaseKillCount();
								if( scoreCounter.getKillCount() > loadedHighscore )
								{
									saveHighscoreToFile(scoreCounter.getKillCount(), "saves/highscore.txt");
									highscoreHit = true;
								}
							}
						}
						for( int i = 0; i < verticalZombiesVector.size(); i++ )
						{
							if( NPCinsideKillAreaPolygon(verticalZombiesVector[ i ]->getZombieCollisionBox(), killZonePolygonVector) )
							{
								VerticalZombie* deadVerticalZombie = new VerticalZombie(deadZombieSpirteSheetTexture.getTextureWidth(), deadZombieSpirteSheetTexture.getTextureHeight());
								deadVerticalZombie->setZombieCollisionBoxPosX(verticalZombiesVector[ i ]->getZombieCollisionBox().x);
								deadVerticalZombie->setZombieCollisionBoxPosY(verticalZombiesVector[ i ]->getZombieCollisionBox().y);
								deadVerticalZombiesVector.push_back(deadVerticalZombie);

								verticalZombiesVector[ i ]->destroySelf(verticalZombiesVector[ i ]);
								verticalZombiesVector.erase(verticalZombiesVector.begin() + i);
								countdownByFrameTimer += 300;

								if( Mix_Playing(NPC_DEAD_SOUND_CHANNEL) == 0 ) {
									Mix_PlayChannel(NPC_DEAD_SOUND_CHANNEL, gZombieDeadSound, 0);
								}

								scoreCounter.increaseKillCount();
								if( scoreCounter.getKillCount() > loadedHighscore )
								{
									saveHighscoreToFile(scoreCounter.getKillCount(), "saves/highscore.txt");
									highscoreHit = true;
								}
							}
						}
						for( int i = 0; i < ghostsVector.size(); i++ )
						{
							if( NPCinsideKillAreaPolygon(ghostsVector[ i ]->getZombieCollisionBox(), killZonePolygonVector) )
							{
								ghostsVector[ i ]->destroySelf(ghostsVector[ i ]);
								ghostsVector.erase(ghostsVector.begin() + i);
								countdownByFrameTimer += 300;

								if( Mix_Playing(NPC_DEAD_SOUND_CHANNEL) == 0 ) {
									Mix_PlayChannel(NPC_DEAD_SOUND_CHANNEL, gZombieDeadSound, 0);
								}

								scoreCounter.increaseKillCount();
								if( scoreCounter.getKillCount() > loadedHighscore )
								{
									saveHighscoreToFile(scoreCounter.getKillCount(), "saves/highscore.txt");
									highscoreHit = true;
								}
							}
						}

						createBreakingAllWallsAnimation(playerTileTrailsVector, breakingAllWallsAnimationVector, gWallBreakingSpriteClips, wallBreakingTexture);

						for( int i = 0; i < playerTileTrailsVector.size(); i++ )
						{
							playerTileTrailsVector[ i ]->destroySelf(playerTileTrailsVector[ i ]);
						}
						playerTileTrailsVector.erase(playerTileTrailsVector.begin(), playerTileTrailsVector.end());

						spawnAnotherKillLineYet = true;
					}
					destroyExpiredTrails(playerTileTrailsVector, gWallBreakingSpriteClips, wallBreakingTexture, breakingWallAnimationVector);
					destroyExpiredKillLines(killLinesVector);

					if( generalTimer % 15 == 0 )
					{
						destroyKillZonePolygonVector(killZonePolygonVector);
					}

					//RENDER NPCS--------------------------------------------
					for( int i = 0; i < horizontalZombiesVector.size(); i++ )
					{
						SDL_Rect* currentClip = &gZombieWalkingRightSpriteClips[ horizontalZombiesVector[ i ]->getCurrentFrame() / 4 ];
						horizontalZombiesVector[ i ]->renderZombie(camera, horizontalZombieSpirteSheetTexture, currentClip);
					}
					for( int i = 0; i < verticalZombiesVector.size(); i++ )
					{
						SDL_Rect* currentClip = &gZombieWalkingDownSpriteClips[ verticalZombiesVector[ i ]->getCurrentFrame() / 4 ];
						verticalZombiesVector[ i ]->renderZombie(camera, verticalZombieSpirteSheetTexture, currentClip);
					}
					for( int i = 0; i < ghostsVector.size(); i++ )
					{
						SDL_Rect* currentClip = &ghostSpriteClips[ ghostsVector[ i ]->getCurrentFrame() / 4 ];
						ghostsVector[ i ]->renderZombie(camera, ghostSpirteSheetTexture, currentClip);
					}

					showScore(scoreCounter, gGameWindow, gFont, scoreLabelTexture, highscoreHit, highscoreShowOnScreenTimer);

					//RENDER BREAKING WALL AND ALL WALLS
					renderBreakingWallAnimation(breakingWallAnimationVector, wallBreakingTexture, gWallBreakingSpriteClips, camera);

					if( renderBreakingAllWallsAnimation(breakingAllWallsAnimationVector, wallBreakingTexture, gWallBreakingSpriteClips, camera, gBreakingBricks) == true )
					{
						if( Mix_Playing(BREAKING_BRICKS_SOUND_CHANNEL) == 0 ) {
							Mix_PlayChannel(BREAKING_BRICKS_SOUND_CHANNEL, gBreakingBricks, 0);
						}
					}

					renderDeadNPCs(deadHorizontalZombiesVector, gDeadZombieClip, camera, deadZombieSpirteSheetTexture);
					renderDeadNPCs(deadVerticalZombiesVector, gDeadZombieClip, camera, deadZombieSpirteSheetTexture);

					if( player.getIsDead() )
					{
						renderDeadPlayer(deadPlayer, gDeadPlayerClip, camera, deadPlayerSpriteSheetTexture);
					}

					showCountdownTimer(gGameWindow, gFont, countdownByFrameTimer);

					gGameWindow->updateScreen();

					if( !player.getIsDead() )
					{
						++currentPlayerFrame;
						if( currentPlayerFrame / 4 >= WALKING_ANIMATION_FRAMES )
						{
							currentPlayerFrame = 0;
						}
					}

					for( int i = 0; i < horizontalZombiesVector.size(); i++ )
					{
						horizontalZombiesVector[ i ]->increaseCurrentFrame();
						if( horizontalZombiesVector[ i ]->getCurrentFrame() / 4 >= ZOMBIE_ANIMATION_FRAMES )
						{
							horizontalZombiesVector[ i ]->setCurrentFrame(0);
						}
					}
					for( int i = 0; i < verticalZombiesVector.size(); i++ )
					{
						verticalZombiesVector[ i ]->increaseCurrentFrame();
						if( verticalZombiesVector[ i ]->getCurrentFrame() / 4 >= ZOMBIE_ANIMATION_FRAMES )
						{
							verticalZombiesVector[ i ]->setCurrentFrame(0);
						}
					}
					for( int i = 0; i < ghostsVector.size(); i++ )
					{
						ghostsVector[ i ]->increaseCurrentFrame();
						if( ghostsVector[ i ]->getCurrentFrame() / 4 >= ZOMBIE_ANIMATION_FRAMES )
						{
							ghostsVector[ i ]->setCurrentFrame(0);
						}
					}

					isCollidedWithWall = false;
					generalTimer++;
					//std::cout << "countdownByFrameTimer: " << countdownByFrameTimer << "\n";
					countdownByFrameTimer--;

					if( deadScreenTimer == 1 )
					{
						menuState = DEAD_MENU;
					}
					if( player.getIsDead() )
					{
						deadScreenTimer--;
					}

					for( const auto& trail : playerTileTrailsVector ) {
						if( trail != nullptr )
						{
							trail->decreaseLifeTime();
						}
					}

					for( const auto& line : killLinesVector ) {
						if( line != nullptr )
						{
							line->decreaseLifeTime();
						}
					}

					destroyDeadNPCsAnimation(deadHorizontalZombiesVector);
					destroyDeadNPCsAnimation(deadVerticalZombiesVector);

					destroyBreakingWallAnimation(breakingWallAnimationVector);
					destroyAllBreakingWallsAnimation(breakingAllWallsAnimationVector);
					if( isDeadPlayerDeallocated == false )
					{
						decreasePlayerCorpseDurationAnimation(deadPlayer, isDeadPlayerDeallocated);
					}
				}


			}
		}

		killThemAll(horizontalZombiesVector, verticalZombiesVector);
		deallocatePlayerTrails(playerTileTrailsVector);
		deallocateKillLine(killLinesVector);
		deallocateTileSet(tileSet);

		deallocateBreakingWallAnimation(breakingWallAnimationVector);
		deallocateAllBreakingWallsAnimation(breakingAllWallsAnimationVector);

		deallocateDeadNPCsAnimation(deadHorizontalZombiesVector);
		deallocateDeadNPCsAnimation(deadVerticalZombiesVector);

		gGameWindow->deallocateSound(2, gChangeSelection, gBreakingBricks);
		gGameWindow->deallocateMusic(3, gMainMenuMusic, gPlayingMusic, gDeadMusic);
		gGameWindow->close(gGameWindow, gFont);
	}

	return 0;
}


