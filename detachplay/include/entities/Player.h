#pragma once
#include <SDL.h>
#include <array>

#include "Tile.h"
#include "Texture.h"

#include "../Constants/common_constants.h"
#include "../Enums/moving_enum.h"

#include "../CommonFuncs/collision_funcs.h"

class Texture;
class Tile;

class Player
{
public:
	//MOVEMENT MANAGING
	static const int PLAYER_VEL = 10;

	//Initializes the variables
	Player(const int& TEXTURE_WIDTH, const int& TEXTURE_HEIGHT);

	//Takes key presses and adjusts the dot's velocity
	void handleEvent(SDL_Event& e, int& DIRECTION_CHECK);

	bool movePlayer(std::array<Tile*, TOTAL_TILES>& tiles, bool& isCollidedWithWall);

	void setToDefault();

	void decreaseCorpseDuration() {
		corpseDuration--;
	}

	int getCorpseDuration() {
		return corpseDuration;
	}

	void setPlayerCollisionBoxPosX(const int& oldPlayerCollisionBoxX) {
		playerCollisionBox.x = oldPlayerCollisionBoxX;
	}

	void setPlayerCollisionBoxPosY(const int& oldPlayerCollisionBoxY) {
		playerCollisionBox.y = oldPlayerCollisionBoxY;
	}

	bool getIsDead() {
		return isDead;
	}

	void setIsDeadToTrue() {
		isDead = true;
	}

	void setIsDeadToFalse() {
		isDead = false;
	}

	bool respawnPlayer() {
		bool isRespawn = false;
		isDead = false;
		isRespawn = true;
		return isRespawn;
	}

	//Centers the camera over the player
	void setCamera(SDL_Rect& camera);

	//Shows the dot on the screen
	void render(SDL_Rect& camera, Texture& gPlayerTexture, SDL_Rect* currentClip = nullptr);

	SDL_Rect getPlayerCollisionBox() {
		return playerCollisionBox;
	}

private:

	SDL_Rect playerCollisionBox;

	int playerVelX, playerVelY;
	int corpseDuration;
	bool isDead;
};