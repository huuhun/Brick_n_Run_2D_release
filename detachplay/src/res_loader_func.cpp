#include "../include/CommonFuncs/res_loader_funcs.h"

bool loadPlayerMedia(Texture& playerSpriteSheetTexture, std::array<SDL_Rect, WALKING_ANIMATION_FRAMES>& gPlayerWalkingLeftSpriteClips, std::array<SDL_Rect, WALKING_ANIMATION_FRAMES>& gPlayerWalkingRightSpriteClips, std::array<SDL_Rect, WALKING_ANIMATION_FRAMES>& gPlayerWalkingUpSpriteClips, std::array<SDL_Rect, WALKING_ANIMATION_FRAMES>& gPlayerWalkingDownSpriteClips, Texture& deadPlayerSpriteSheetTexture, SDL_Rect& gDeadPlayerSpriteClip)
{
	//Loading success flag
	bool isSuccess = true;

	//Load sprite sheet texture
	if( !deadPlayerSpriteSheetTexture.loadFromFile("resources/player-sprites/dead-player.png") )
	{
		std::cerr << "Failed to load dead player texture!\n";
		isSuccess = true;
	}
	else
	{
		gDeadPlayerSpriteClip.x = 0;
		gDeadPlayerSpriteClip.y = 0;
		gDeadPlayerSpriteClip.w = 126;
		gDeadPlayerSpriteClip.h = 79;
	}

	if( !playerSpriteSheetTexture.loadFromFile("resources/player-sprites/moving-player.png") )
	{
		std::cerr << "Failed to load walking animation texture!\n";
		isSuccess = false;
	}
	else
	{
		gPlayerWalkingRightSpriteClips[ 0 ].x = 0;
		gPlayerWalkingRightSpriteClips[ 0 ].y = 11;
		gPlayerWalkingRightSpriteClips[ 0 ].w = 70;
		gPlayerWalkingRightSpriteClips[ 0 ].h = 109;

		gPlayerWalkingRightSpriteClips[ 1 ].x = 69;
		gPlayerWalkingRightSpriteClips[ 1 ].y = 11;
		gPlayerWalkingRightSpriteClips[ 1 ].w = 70;
		gPlayerWalkingRightSpriteClips[ 1 ].h = 109;

		gPlayerWalkingRightSpriteClips[ 2 ].x = 140;
		gPlayerWalkingRightSpriteClips[ 2 ].y = 11;
		gPlayerWalkingRightSpriteClips[ 2 ].w = 70;
		gPlayerWalkingRightSpriteClips[ 2 ].h = 109;

		gPlayerWalkingRightSpriteClips[ 3 ].x = 214;
		gPlayerWalkingRightSpriteClips[ 3 ].y = 11;
		gPlayerWalkingRightSpriteClips[ 3 ].w = 70;
		gPlayerWalkingRightSpriteClips[ 3 ].h = 109;

		//Walking left

		gPlayerWalkingLeftSpriteClips[ 0 ].x = 0;
		gPlayerWalkingLeftSpriteClips[ 0 ].y = 128;
		gPlayerWalkingLeftSpriteClips[ 0 ].w = 70;
		gPlayerWalkingLeftSpriteClips[ 0 ].h = 111;

		gPlayerWalkingLeftSpriteClips[ 1 ].x = 69;
		gPlayerWalkingLeftSpriteClips[ 1 ].y = 128;
		gPlayerWalkingLeftSpriteClips[ 1 ].w = 70;
		gPlayerWalkingLeftSpriteClips[ 1 ].h = 111;

		gPlayerWalkingLeftSpriteClips[ 2 ].x = 140;
		gPlayerWalkingLeftSpriteClips[ 2 ].y = 128;
		gPlayerWalkingLeftSpriteClips[ 2 ].w = 70;
		gPlayerWalkingLeftSpriteClips[ 2 ].h = 111;

		gPlayerWalkingLeftSpriteClips[ 3 ].x = 214;
		gPlayerWalkingLeftSpriteClips[ 3 ].y = 128;
		gPlayerWalkingLeftSpriteClips[ 3 ].w = 70;
		gPlayerWalkingLeftSpriteClips[ 3 ].h = 111;

		//Walking down

		gPlayerWalkingDownSpriteClips[ 0 ].x = 0;
		gPlayerWalkingDownSpriteClips[ 0 ].y = 243;
		gPlayerWalkingDownSpriteClips[ 0 ].w = 70;
		gPlayerWalkingDownSpriteClips[ 0 ].h = 110;

		gPlayerWalkingDownSpriteClips[ 1 ].x = 69;
		gPlayerWalkingDownSpriteClips[ 1 ].y = 243;
		gPlayerWalkingDownSpriteClips[ 1 ].w = 70;
		gPlayerWalkingDownSpriteClips[ 1 ].h = 110;

		gPlayerWalkingDownSpriteClips[ 2 ].x = 140;
		gPlayerWalkingDownSpriteClips[ 2 ].y = 244;
		gPlayerWalkingDownSpriteClips[ 2 ].w = 70;
		gPlayerWalkingDownSpriteClips[ 2 ].h = 105;

		gPlayerWalkingDownSpriteClips[ 3 ].x = 214;
		gPlayerWalkingDownSpriteClips[ 3 ].y = 243;
		gPlayerWalkingDownSpriteClips[ 3 ].w = 70;
		gPlayerWalkingDownSpriteClips[ 3 ].h = 110;

		//Walking up

		gPlayerWalkingUpSpriteClips[ 0 ].x = 0;
		gPlayerWalkingUpSpriteClips[ 0 ].y = 366;
		gPlayerWalkingUpSpriteClips[ 0 ].w = 70;
		gPlayerWalkingUpSpriteClips[ 0 ].h = 128;

		gPlayerWalkingUpSpriteClips[ 1 ].x = 69;
		gPlayerWalkingUpSpriteClips[ 1 ].y = 366;
		gPlayerWalkingUpSpriteClips[ 1 ].w = 70;
		gPlayerWalkingUpSpriteClips[ 1 ].h = 128;

		gPlayerWalkingUpSpriteClips[ 2 ].x = 140;
		gPlayerWalkingUpSpriteClips[ 2 ].y = 366;
		gPlayerWalkingUpSpriteClips[ 2 ].w = 70;
		gPlayerWalkingUpSpriteClips[ 2 ].h = 128;

		gPlayerWalkingUpSpriteClips[ 3 ].x = 214;
		gPlayerWalkingUpSpriteClips[ 3 ].y = 366;
		gPlayerWalkingUpSpriteClips[ 3 ].w = 70;
		gPlayerWalkingUpSpriteClips[ 3 ].h = 128;
	}

	return isSuccess;
}

bool loadBackgroundMedia(Texture& backgroundTexture) {
	bool isSuccess = true;
	if( !backgroundTexture.loadFromFile("resources/backgrounds/bg.png") )
	{
		std::cerr<<"Failed to load background texture!\n";
		isSuccess = false;
	}
	return isSuccess;
}

bool setTiles(std::array<Tile*, TOTAL_TILES>& tiles, std::array<SDL_Rect, TOTAL_TILE_SPRITES>& gTileClips)
{
	//Success flag
	bool tilesLoaded = true;

	//The tile offsets
	int x = 0, y = 0;

	//Open the map
	std::ifstream map("resources/map/lazy.map");

	//If the map couldn't be loaded
	if( map.fail() )
	{
		printf("Unable to load map file!\n");
		tilesLoaded = false;
	}
	else
	{
		//Initialize the tiles
		for( int i = 0; i < TOTAL_TILES; ++i )
		{
			//Determines what kind of tile will be made
			int tileType = -1;

			//Read tile from map file
			map >> tileType;

			//If the was a problem in reading the map
			if( map.fail() )
			{
				//Stop loading map
				printf("Error loading map: Unexpected end of file!\n");
				tilesLoaded = false;
				break;
			}

			//If the number is a valid tile number
			if( ( tileType >= 0 ) && ( tileType < TOTAL_TILE_SPRITES ) )
			{
				tiles[ i ] = new Tile(x, y, tileType);
			}
			//If we don't recognize the tile type
			else
			{
				//Stop loading map
				std::cerr<<"Error loading map: Invalid tile type at "<< i <<"\n";
				tilesLoaded = false;
				break;
			}

			//Move to next tile spot
			x += TILE_WIDTH;

			//If we've gone too far
			if( x >= LEVEL_WIDTH )
			{
				//Move back
				x = 0;

				//Move to the next row
				y += TILE_HEIGHT;
			}
		}

		//Clip the sprite sheet
		if( tilesLoaded )
		{
			gTileClips[ TILE_RED ].x = 0;
			gTileClips[ TILE_RED ].y = 0;
			gTileClips[ TILE_RED ].w = TILE_WIDTH;
			gTileClips[ TILE_RED ].h = TILE_HEIGHT;

			gTileClips[ TILE_GREEN ].x = 0;
			gTileClips[ TILE_GREEN ].y = 80;
			gTileClips[ TILE_GREEN ].w = TILE_WIDTH;
			gTileClips[ TILE_GREEN ].h = TILE_HEIGHT;

			gTileClips[ TILE_BLUE ].x = 0;
			gTileClips[ TILE_BLUE ].y = 160;
			gTileClips[ TILE_BLUE ].w = TILE_WIDTH;
			gTileClips[ TILE_BLUE ].h = TILE_HEIGHT;

			gTileClips[ TILE_TOPLEFT ].x = 80;
			gTileClips[ TILE_TOPLEFT ].y = 0;
			gTileClips[ TILE_TOPLEFT ].w = TILE_WIDTH;
			gTileClips[ TILE_TOPLEFT ].h = TILE_HEIGHT;

			gTileClips[ TILE_LEFT ].x = 80;
			gTileClips[ TILE_LEFT ].y = 80;
			gTileClips[ TILE_LEFT ].w = TILE_WIDTH;
			gTileClips[ TILE_LEFT ].h = TILE_HEIGHT;

			gTileClips[ TILE_BOTTOMLEFT ].x = 80;
			gTileClips[ TILE_BOTTOMLEFT ].y = 160;
			gTileClips[ TILE_BOTTOMLEFT ].w = TILE_WIDTH;
			gTileClips[ TILE_BOTTOMLEFT ].h = TILE_HEIGHT;

			gTileClips[ TILE_TOP ].x = 160;
			gTileClips[ TILE_TOP ].y = 0;
			gTileClips[ TILE_TOP ].w = TILE_WIDTH;
			gTileClips[ TILE_TOP ].h = TILE_HEIGHT;

			gTileClips[ TILE_CENTER ].x = 160;
			gTileClips[ TILE_CENTER ].y = 80;
			gTileClips[ TILE_CENTER ].w = TILE_WIDTH;
			gTileClips[ TILE_CENTER ].h = TILE_HEIGHT;

			gTileClips[ TILE_BOTTOM ].x = 160;
			gTileClips[ TILE_BOTTOM ].y = 160;
			gTileClips[ TILE_BOTTOM ].w = TILE_WIDTH;
			gTileClips[ TILE_BOTTOM ].h = TILE_HEIGHT;

			gTileClips[ TILE_TOPRIGHT ].x = 240;
			gTileClips[ TILE_TOPRIGHT ].y = 0;
			gTileClips[ TILE_TOPRIGHT ].w = TILE_WIDTH;
			gTileClips[ TILE_TOPRIGHT ].h = TILE_HEIGHT;

			gTileClips[ TILE_RIGHT ].x = 240;
			gTileClips[ TILE_RIGHT ].y = 80;
			gTileClips[ TILE_RIGHT ].w = TILE_WIDTH;
			gTileClips[ TILE_RIGHT ].h = TILE_HEIGHT;

			gTileClips[ TILE_BOTTOMRIGHT ].x = 240;
			gTileClips[ TILE_BOTTOMRIGHT ].y = 160;
			gTileClips[ TILE_BOTTOMRIGHT ].w = TILE_WIDTH;
			gTileClips[ TILE_BOTTOMRIGHT ].h = TILE_HEIGHT;
		}
	}

	//Close the file
	map.close();

	//If the map was loaded fine
	return tilesLoaded;
}

bool loadTilesMedia(std::array<Tile*, TOTAL_TILES>& tiles, Texture& tileTexture, std::array<SDL_Rect, TOTAL_TILE_SPRITES>& gTileClips)
{
	bool isSuccess = true;
	//Load tile texture
	if( !tileTexture.loadFromFile("resources/map/tiles.png") )
	{
		std::cerr<<"Failed to load tile set texture!\n";
		isSuccess = false;
	}
	//Load tile map
	if( !setTiles(tiles, gTileClips) )
	{
		std::cerr << "Failed to load tile set!\n";
		isSuccess = false;
	}

	return isSuccess;
}

bool loadBreakingWallMedia(Texture& breakingWallSpriteSheetTexture, std::array<SDL_Rect, BREAKING_WALL_ANIMATION_FRAMES>& gWallBreakingSpriteClips) {
	//Loading success flag
	bool isSuccess = true;

	//Load sprite sheet texture
	if( !breakingWallSpriteSheetTexture.loadFromFile("resources/map/wall_break_sprites.png") )
	{
		std::cerr << "Failed to load breaking walls animation texture!\n";
		isSuccess = false;
	}
	else
	{
		gWallBreakingSpriteClips[ 0 ].x = 0;
		gWallBreakingSpriteClips[ 0 ].y = 0;
		gWallBreakingSpriteClips[ 0 ].w = 159;
		gWallBreakingSpriteClips[ 0 ].h = 163;

		gWallBreakingSpriteClips[ 1 ].x = 159;
		gWallBreakingSpriteClips[ 1 ].y = 0;
		gWallBreakingSpriteClips[ 1 ].w = 208;
		gWallBreakingSpriteClips[ 1 ].h = 163;

		gWallBreakingSpriteClips[ 2 ].x = 367;
		gWallBreakingSpriteClips[ 2 ].y = 0;
		gWallBreakingSpriteClips[ 2 ].w = 247;
		gWallBreakingSpriteClips[ 2 ].h = 163;

		gWallBreakingSpriteClips[ 3 ].x = 614;
		gWallBreakingSpriteClips[ 3 ].y = 0;
		gWallBreakingSpriteClips[ 3 ].w = 233;
		gWallBreakingSpriteClips[ 3 ].h = 163;
	}

	return isSuccess;
}

bool loadFontMedia(TTF_Font*& gFont, Texture& textTexture, SDL_Renderer* gRenderer) {
	//Loading success flag
	bool success = true;

	//Open the font
	gFont = TTF_OpenFont("resources/fonts/advanced_pixel-7.ttf", 40);
	if( gFont == nullptr )
	{
		std::cerr << "Init, Failed to load lazy font! SDL_ttf Error: " << TTF_GetError() << "\n";
		success = false;
	}
	else
	{
		//Render text
		SDL_Color textColor = { 255, 255, 255 };
		if( !textTexture.loadFromRenderedText("SCORE: ", textColor, gFont, gRenderer) )
		{
			std::cerr << "Failed to render text texture!\n";
			success = false;
		}
	}
	return success;
}

bool loadMenuMedia(Texture& chooseArrowTexture, Texture& introChooseArrowTexture, Texture& pauseChooseArrowTexture, Texture& logoTexture, SDL_Renderer* gRenderer) {
	//Loading success flag
	bool isSuccess = true;

	//Load sprite sheet texture
	if( !chooseArrowTexture.loadFromFile("resources/menu/choose_arrow.png") )
	{
		std::cerr << "Failed to load choose arrow texture!\n";
		isSuccess = false;
	}

	if( !introChooseArrowTexture.loadFromFile("resources/menu/choose_arrow.png") )
	{
		std::cerr << "Failed to load intro choose arrow texture!\n";
		isSuccess = false;
	}

	if( !pauseChooseArrowTexture.loadFromFile("resources/menu/choose_arrow.png") )
	{
		std::cerr << "Failed to load pause choose arrow texture!\n";
		isSuccess = false;
	}

	if( !logoTexture.loadFromFile("resources/menu/logo.png") )
	{
		std::cerr << "Failed to load logo texture!\n";
		isSuccess = false;
	}

	return isSuccess;
}

bool loadSoundEffects(Mix_Chunk*& gChangeSelection, Mix_Chunk*& gBreakingBricks, Mix_Chunk*& gDeadSound, Mix_Chunk*& gZombieDeadSound) {
	bool success = true;
	gChangeSelection = Mix_LoadWAV("resources/sound/change-selection.wav");
	if( gChangeSelection == nullptr )
	{
		std::cerr << "Failed to load change selection effect! SDL_mixer Error: " << Mix_GetError() << "\n";
		success = false;
	}

	gBreakingBricks = Mix_LoadWAV("resources/sound/breaking-bricks.wav");
	if( gBreakingBricks == nullptr )
	{
		std::cerr << "Failed to load lay brick effect! SDL_mixer Error: " << Mix_GetError() << "\n";
		success = false;
	}

	gDeadSound = Mix_LoadWAV("resources/sound/dead-sound.wav");
	if( gDeadSound == nullptr )
	{
		std::cerr << "Failed to load dead effect! SDL_mixer Error: " << Mix_GetError() << "\n";
		success = false;
	}

	gZombieDeadSound = Mix_LoadWAV("resources/sound/zombie-dead-sound.wav");
	if( gZombieDeadSound == nullptr )
	{
		std::cerr << "Failed to load dead effect! SDL_mixer Error: " << Mix_GetError() << "\n";
		success = false;
	}

	Mix_Volume(-1, 50);

	return success;
}

bool loadMusic(Mix_Music*& gMainMenu, Mix_Music*& gPlayingMusic, Mix_Music*& gDeadMusic) {
	bool success = true;
	gMainMenu = Mix_LoadMUS("resources/music/main-menu-music.wav");
	if( gMainMenu == nullptr )
	{
		std::cerr << "Failed to load music! SDL_mixer Error: " << Mix_GetError() << "\n";
		success = false;
	}

	gPlayingMusic = Mix_LoadMUS("resources/music/playing-music.wav");
	if( gPlayingMusic == nullptr )
	{
		std::cerr << "Failed to load music! SDL_mixer Error: " << Mix_GetError() << "\n";
		success = false;
	}

	gDeadMusic = Mix_LoadMUS("resources/music/dead-music.wav");
	if( gDeadMusic == nullptr )
	{
		std::cerr << "Failed to load music! SDL_mixer Error: " << Mix_GetError() << "\n";
		success = false;
	}

	Mix_VolumeMusic(50);
	return success;
}
