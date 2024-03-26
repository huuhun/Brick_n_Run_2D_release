#pragma once

#include <SDL.h>

#include "../entities/Texture.h"
#include <ctime> 
#include <cstdlib>
#include <random>
#include <array>

class Texture;

class HorizontalZombie
{
public:

	static const int ZOMBIE_VEL = 2;

	//Initializes the variables
	HorizontalZombie(const int& TEXTURE_WIDTH, const int& TEXTURE_HEIGHT);

	~HorizontalZombie();

	void moveZombie();

	//Shows the dot on the screen
	void renderZombie(SDL_Rect& camera, Texture& gZombieTexture, SDL_Rect* currentClip = nullptr);

	void destroySelf(HorizontalZombie*& horizontalZombie);

	SDL_Rect getZombieCollisionBox() {
		return zombieCollisionBox;
	}

	int getCurrentFrame() {
		return currentFrame;
	}

	void increaseCurrentFrame() {
		currentFrame++;
	}

	void setCurrentFrame(const int& currentFrame) {
		this->currentFrame = currentFrame;
	}

	void setIsOutOfBounds() {
		isOutOfBounds = true;
	}

	bool getIsOutOfBounds() {
		return isOutOfBounds;
	}

	void decreaseCoprseDuration() {
		corspeDuration--;
	}

	int getCorpseDuration() {
		return corspeDuration;
	}

	bool checkIfCorpseDurationExpired() {
		if( corspeDuration <= 0 )
		{
			return true;
		}
		return false;
	}

	void setZombieCollisionBoxPosX(const int& oldZombieCollisionBoxPosX) {
		zombieCollisionBox.x = oldZombieCollisionBoxPosX;
	}

	void setZombieCollisionBoxPosY(const int& oldZombieCollisionBoxPosY) {
		zombieCollisionBox.y = oldZombieCollisionBoxPosY;
	}

	void setIsDeadToTrue() {
		isDead = true;
	}

	bool getIsDead() {
		return isDead;
	}

protected:

	SDL_Rect zombieCollisionBox;
	bool isOutOfBounds;
	int currentFrame;
	int corspeDuration;
	bool isDead;
};

