#include "../include/entities/Player.h"

Player::Player(const int& TEXTURE_WIDTH, const int& TEXTURE_HEIGHT)
{
    playerCollisionBox.x = 90;
    playerCollisionBox.y = 90;
    playerCollisionBox.w = TEXTURE_WIDTH / 4 - 35; /* 1/4 frames */
    playerCollisionBox.h = TEXTURE_HEIGHT / 4 - 35;

    //Initialize the velocity
    playerVelX = 0;
    playerVelY = 0;

    corpseDuration = 300;
    isDead = false;
}

void Player::setToDefault() {
    playerCollisionBox.x = 90;
    playerCollisionBox.y = 90;

    //Initialize the velocity
    playerVelX = 0;
    playerVelY = 0;

    corpseDuration = 300;
    isDead = false;

}

void Player::handleEvent(SDL_Event& e, int& DIRECTION_CHECK)
{  
    //If a key was pressed
    if( e.type == SDL_KEYDOWN && e.key.repeat == 0 )
    {

        //Adjust the velocity
        switch( e.key.keysym.sym )
        {
        case SDLK_UP: playerVelY -= PLAYER_VEL; DIRECTION_CHECK = WALKING_UP; break;
        case SDLK_DOWN: playerVelY += PLAYER_VEL; DIRECTION_CHECK = WALKING_DOWN; break;
        case SDLK_LEFT: playerVelX -= PLAYER_VEL; DIRECTION_CHECK = WALKING_LEFT; break;
        case SDLK_RIGHT: playerVelX += PLAYER_VEL; DIRECTION_CHECK = WALKING_RIGHT; break;
        }
    }

    //If a key was released
     if( e.type == SDL_KEYUP && e.key.repeat == 0 )
    {
        //Adjust the velocity
        switch( e.key.keysym.sym )
        {
        case SDLK_UP: playerVelY += PLAYER_VEL; DIRECTION_CHECK = STANDING_STILL_FACING_UP; break;
        case SDLK_DOWN: playerVelY -= PLAYER_VEL; DIRECTION_CHECK = STANDING_STILL_FACING_DOWN; break;
        case SDLK_LEFT: playerVelX += PLAYER_VEL; DIRECTION_CHECK = STANDING_STILL_FACING_LEFT; break;
        case SDLK_RIGHT: playerVelX -= PLAYER_VEL; DIRECTION_CHECK = STANDING_STILL_FACING_RIGHT; break;
        }
    }
}

bool Player::movePlayer(std::array<Tile*, TOTAL_TILES>& tiles, bool& isCollidedWithWall)
{
    //Move the dot left or right
    playerCollisionBox.x += playerVelX;

    //If the dot went too far to the left or right
    if( ( playerCollisionBox.x < 0 ) || ( playerCollisionBox.x + playerCollisionBox.w > LEVEL_WIDTH ) || touchesTileWall(playerCollisionBox, tiles) )
    {
        //Move back
        playerCollisionBox.x -= playerVelX;
        isCollidedWithWall = true;
    }
    
    //Move the dot up or down
    playerCollisionBox.y += playerVelY;

    //If the dot went too far up or down
    if( ( playerCollisionBox.y < 0 ) || ( playerCollisionBox.y + playerCollisionBox.h > LEVEL_HEIGHT ) || touchesTileWall(playerCollisionBox, tiles) )
    {
        //Move back
        playerCollisionBox.y -= playerVelY;
        isCollidedWithWall = true;
    }

    return isCollidedWithWall;
}

void Player::setCamera(SDL_Rect& camera)
{
    //Center the camera over the dot
    camera.x = ( playerCollisionBox.x + playerCollisionBox.w / 2 ) - SCREEN_WIDTH / 2 ;
    camera.y = ( playerCollisionBox.y + playerCollisionBox.h / 2 ) - SCREEN_HEIGHT / 2;

    //Keep the camera in bounds
    if( camera.x < 0 )
    {
        camera.x = 0;
    }
    if( camera.y < 0 )
    {
        camera.y = 0;
    }
    if( camera.x > LEVEL_WIDTH - camera.w )
    {
        camera.x = LEVEL_WIDTH - camera.w;
    }
    if( camera.y > LEVEL_HEIGHT - camera.h )
    {
        camera.y = LEVEL_HEIGHT - camera.h;
    }
}

//void Texture::renderTexture(const int& texturePosX, const int& texturePosY, SDL_Rect* clip) {
//
//    //Set rendering space and render to target location on screen
//    SDL_Rect renderQuad = { texturePosX , texturePosY , textureWidth, textureHeight };
//
//    if( clip != nullptr )
//    {
//        renderQuad.w = clip->w;
//        renderQuad.h = clip->h;
//    }
//    //Render to screen
//    SDL_RenderCopy(renderer, actualTexture, clip, &renderQuad);
//}

void Player::render(SDL_Rect& camera, Texture& gPlayerTexture, SDL_Rect* currentClip)
{
    gPlayerTexture.renderTexture(playerCollisionBox.x - camera.x, playerCollisionBox.y - camera.y, currentClip);
}