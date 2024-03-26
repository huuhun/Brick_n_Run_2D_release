#include "../include/entities/Tile.h"

//---------------
Tile::Tile(const int& tilePosX, const int& tilePosY, const int& tileType)
{
    //Get the offsets
    tileCollisionBox.x = tilePosX;
    tileCollisionBox.y = tilePosY;

    //Set the collision box
    tileCollisionBox.w = TILE_WIDTH;
    tileCollisionBox.h = TILE_HEIGHT;

    //Get the tile type
    this->tileType = tileType;
}

void Tile::render(SDL_Rect& camera, Texture& gTileTexture, std::array<SDL_Rect, TOTAL_TILE_SPRITES>& gTileClips)
{
    //If the tile is on screen
    if( checkCollision(camera, tileCollisionBox) )
    {
        gTileTexture.renderTexture(tileCollisionBox.x - camera.x, tileCollisionBox.y - camera.y, &gTileClips[ tileType ]);
    }
}

