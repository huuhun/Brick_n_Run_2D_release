#include "../include/CommonFuncs/spawner_funcs.h"

void spawnATestHorizontalZombies(Texture& horizontalZombieSpirteSheetTexture, std::vector<HorizontalZombie*>& horizontalZombiesVector) {

	HorizontalZombie* horizontalZombie = new HorizontalZombie(horizontalZombieSpirteSheetTexture.getTextureWidth(), horizontalZombieSpirteSheetTexture.getTextureHeight());
	horizontalZombiesVector.push_back(horizontalZombie);

	std::cout << "A Horizontal Zombie is spawned" << ", horizontalZombiesVector size is " << horizontalZombiesVector.size() << "\n";
}

void spawnNPC(Texture& horizontalZombieSpirteSheetTexture, std::vector<HorizontalZombie*>& horizontalZombiesVector) {

	srand(static_cast<unsigned>( time(nullptr) ));

	int random_number = rand() % 2;
	if( random_number == 1 )
	{
		HorizontalZombie* horizontalZombie = new HorizontalZombie(horizontalZombieSpirteSheetTexture.getTextureWidth(), horizontalZombieSpirteSheetTexture.getTextureHeight());
		horizontalZombiesVector.push_back(horizontalZombie);

		//std::cout << "A Horizontal Zombie is spawned" << ", horizontalZombiesVector size is " << horizontalZombiesVector.size() << "\n";
	}
}

void spawnNPC(Texture& verticalZombieSpirteSheetTexture, std::vector<VerticalZombie*>& verticalZombiesVector) {

	srand(static_cast<unsigned>( time(nullptr) ));

	int random_number = rand() % 2;
	if( random_number == 1 )
	{
		VerticalZombie* verticalZombie = new VerticalZombie(verticalZombieSpirteSheetTexture.getTextureWidth(), verticalZombieSpirteSheetTexture.getTextureHeight());
		verticalZombiesVector.push_back(verticalZombie);
	}
}

void spawnNPC(Texture& ghostSpirteSheetTexture, std::vector<Ghost*>& ghostsVector) {

	srand(static_cast<unsigned>( time(nullptr) ));

	int random_number = rand() % 2;
	if( random_number == 1 )
	{
		Ghost* ghost = new Ghost(ghostSpirteSheetTexture.getTextureWidth(), ghostSpirteSheetTexture.getTextureHeight());
		ghostsVector.push_back(ghost);
	}
}




