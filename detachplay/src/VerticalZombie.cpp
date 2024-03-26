#include "../include/entities/VerticalZombie.h"
//DerivedClass::DerivedClass(int derivedValue) : FatherClass(derivedValue) {
//    std::cout << "DerivedClass constructor with parameter: " << derivedValue << std::endl;
//}
VerticalZombie::VerticalZombie(const int& TEXTURE_WIDTH, const int& TEXTURE_HEIGHT) : HorizontalZombie(TEXTURE_WIDTH, TEXTURE_HEIGHT) {

	std::random_device rd;
	std::mt19937 gen(rd());
	std::array<int, 22> randomPosX = { 200, 260, 300, 360, 400, 460, 500, 560, 600, 670, 700, 770, 800, 860, 900, 960, 1000, 1160, 1200, 1260 ,1300 ,1360 };
	std::uniform_int_distribution<> distribution(0, static_cast<int>( randomPosX.size() ) - 1);

	std::size_t index = distribution(gen);

	zombieCollisionBox.x = randomPosX[ index ];
	zombieCollisionBox.y = 0;
	zombieCollisionBox.w = TEXTURE_WIDTH / 4 - 10; /* 1/4 frames */
	zombieCollisionBox.h = TEXTURE_HEIGHT / 4;

	isOutOfBounds = false;
	isDead = false;
	currentFrame = 0;
	corspeDuration = 70;
}

void VerticalZombie::destroySelf(VerticalZombie*& verticalZombie) {
	if( verticalZombie != nullptr )
	{
		delete verticalZombie;
		verticalZombie = nullptr;
		//std::cout << "A horizontal zombie was killed by the player\n";
	}
}

//
//VerticalZombie::~VerticalZombie() {
//    isOutOfBounds = false;
//    isDead = false;
//    zombieCollisionBox = { 0,0,0,0 };
//}
//
void VerticalZombie::moveZombie() {

	isOutOfBounds = false;

	//Move the dot left or right
	zombieCollisionBox.y += ZOMBIE_VEL;

	//If the dot went too far to the left or right
	if( ( zombieCollisionBox.y < 0 ) || ( zombieCollisionBox.y + zombieCollisionBox.h > LEVEL_HEIGHT ) )
	{
		//Go out of bound
		isOutOfBounds = true;
	}
}
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
