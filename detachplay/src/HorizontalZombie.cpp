#include "../include/entities/HorizontalZombie.h"

HorizontalZombie::HorizontalZombie(const int& TEXTURE_WIDTH, const int& TEXTURE_HEIGHT){

    std::random_device rd;
    std::mt19937 gen(rd());
    std::array<int,7> randomPosY = {230, 260, 300, 350, 400, 500, 600};
    std::uniform_int_distribution<> distribution(0, static_cast<int>( randomPosY.size() ) - 1);

    std::size_t index = distribution(gen);

    zombieCollisionBox.x = 0;
    zombieCollisionBox.y = randomPosY[index];
    zombieCollisionBox.w = TEXTURE_WIDTH / 4 - 10; /* 1/4 frames */
    zombieCollisionBox.h = TEXTURE_HEIGHT / 4;

    isOutOfBounds = false;
    isDead = false;
    currentFrame = 0;
    corspeDuration = 70;
}

HorizontalZombie::~HorizontalZombie() {
    isOutOfBounds = false;
    isDead = false;
    zombieCollisionBox = { 0,0,0,0 };
}

void HorizontalZombie::moveZombie(){

    isOutOfBounds = false;

    //Move the dot left or right
    zombieCollisionBox.x += ZOMBIE_VEL;

    //If the dot went too far to the left or right
    if( ( zombieCollisionBox.x < 0 ) || ( zombieCollisionBox.x + zombieCollisionBox.w > LEVEL_WIDTH ) )
    {
        //Go out of bound
        isOutOfBounds = true;
    }
}


void HorizontalZombie::renderZombie(SDL_Rect& camera, Texture& gZombieTexture, SDL_Rect* currentClip){

    gZombieTexture.renderTexture(zombieCollisionBox.x - camera.x, zombieCollisionBox.y - camera.y, currentClip);
}

void HorizontalZombie::destroySelf(HorizontalZombie*& horizontalZombie) {
    if( horizontalZombie != nullptr )
    {
        delete horizontalZombie;
        horizontalZombie = nullptr;
        std::cout << "A horizontal zombie was killed by the player\n";
	}
}
