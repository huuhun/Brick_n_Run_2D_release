#pragma once
inline const int SCREEN_WIDTH = 1020;
inline const int SCREEN_HEIGHT = 640;

inline const int WALKING_ANIMATION_FRAMES = 4;

//The dimensions of the level
inline const int LEVEL_WIDTH = 1680;
inline const int LEVEL_HEIGHT = 880;

//Tile constants
inline const int TILE_WIDTH = 80;
inline const int TILE_HEIGHT = 80;
inline const int TOTAL_TILES = 231; //192
inline const int TOTAL_TILE_SPRITES = 12;

//The different tile sprites
inline const int TILE_RED = 0;
inline const int TILE_GREEN = 1;
inline const int TILE_BLUE = 2;
inline const int TILE_CENTER = 3;
inline const int TILE_TOP = 4;
inline const int TILE_TOPRIGHT = 5;
inline const int TILE_RIGHT = 6;
inline const int TILE_BOTTOMRIGHT = 7;
inline const int TILE_BOTTOM = 8;
inline const int TILE_BOTTOMLEFT = 9;
inline const int TILE_LEFT = 10;
inline const int TILE_TOPLEFT = 11;

inline const int TILE_SIZE = 80;


//TRAILs
inline const int MAX_PLAYER_TRAILS = 20;
inline const int BREAKING_WALL_ANIMATION_FRAMES = 4;


//KILL LINES
inline const int MAX_KILL_LINES = MAX_PLAYER_TRAILS;
inline const int TRAILS_LIFETIME = 140;
inline const int KILLLINES_LIFETIME = TRAILS_LIFETIME;

//SCORES
inline const int HIGHSCORE_ALERT_DURATION = 95;

//DEAD SCREEN
inline const int DEAD_SCREEN_DURATION = 30;

//SAVES
inline const int TOTAL_DATA = 1;

//SOUND
inline const int NPC_DEAD_SOUND_CHANNEL = 0;
inline const int BREAKING_BRICKS_SOUND_CHANNEL = 1;
inline const int PLAYER_SOUND_CHANNEL = 2;

//TIMER
inline const int TIME_LEFT_TO_KILL = 1000;



