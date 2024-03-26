#include "../include/entities/Ghost.h"
//DerivedClass::DerivedClass(int derivedValue) : FatherClass(derivedValue) {
//    std::cout << "DerivedClass constructor with parameter: " << derivedValue << std::endl;
//}
Ghost::Ghost(const int& TEXTURE_WIDTH, const int& TEXTURE_HEIGHT) : HorizontalZombie(TEXTURE_WIDTH, TEXTURE_HEIGHT) {

	std::srand(std::time(0));
	int random_number = std::rand() % 1000 + 100;

	double random_location = static_cast<double>( std::rand() ) / RAND_MAX;

	if( random_location == 1 )
	{
		zombieCollisionBox.x = 0;
		zombieCollisionBox.y = random_number;
	}
	else
	{
		zombieCollisionBox.x = random_number;
		zombieCollisionBox.y = 0;
	}
	zombieCollisionBox.w = TEXTURE_WIDTH / 4 - 10; /* 1/4 frames */
	zombieCollisionBox.h = TEXTURE_HEIGHT / 4;

	isOutOfBounds = false;
	isDead = false;
	currentFrame = 0;
	corspeDuration = 70;
}

void Ghost::destroySelf(Ghost*& ghost) {
	if( ghost != nullptr )
	{
		delete ghost;
		ghost = nullptr;
		//std::cout << "A horizontal zombie was killed by the player\n";
	}
}

void Ghost::move(const SDL_Rect& playerCollisionBox) {

	if( zombieCollisionBox.x < playerCollisionBox.x ) {
		zombieCollisionBox.x += GHOST_VEL;
	}
	else if( zombieCollisionBox.x > playerCollisionBox.x ) {
		zombieCollisionBox.x -= GHOST_VEL;
	}

	if( zombieCollisionBox.y < playerCollisionBox.y ) {
		zombieCollisionBox.y += GHOST_VEL;
	}
	else if( zombieCollisionBox.y > playerCollisionBox.y ) {
		zombieCollisionBox.y -= GHOST_VEL;
	}
}

//
//VerticalZombie::~VerticalZombie() {
//    isOutOfBounds = false;
//    isDead = false;
//    zombieCollisionBox = { 0,0,0,0 };
//}
//
//void VerticalZombie::moveZombie() {
//
//    isOutOfBounds = false;
//
//    //Move the dot left or right
//    zombieCollisionBox.x += ZOMBIE_VEL;
//
//    //If the dot went too far to the left or right
//    if( ( zombieCollisionBox.x < 0 ) || ( zombieCollisionBox.x + zombieCollisionBox.w > LEVEL_WIDTH ) )
//    {
//        //Go out of bound
//        isOutOfBounds = true;
//    }
//}
//
//
//void VerticalZombie::renderZombie(SDL_Rect& camera, Texture& gVerticalZombieTexture, SDL_Rect* currentClip) {
//
//    gVerticalZombieTexture.renderTexture(zombieCollisionBox.x - camera.x, zombieCollisionBox.y - camera.y, currentClip);
//}
//
//void VerticalZombie::destroySelf(VerticalZombie*& verticalZombie) {
//    if( verticalZombie != nullptr )
//    {
//        delete verticalZombie;
//        verticalZombie = nullptr;
//        std::cout << "A vertical zombie was killed by the player\n";
//    }
//}
