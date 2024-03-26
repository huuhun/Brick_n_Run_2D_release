#pragma once
#include <SDL.h>
#include "../Constants/common_constants.h"
#include "../entities/Texture.h"

class Texture;

class Text
{
public:
	Text(int posX, int posY, int width, int height);

	void render(Texture& gPlayerTexture, SDL_Rect* currentClip = nullptr);

	//void renderCounter(Texture& gPlayerTexture, SDL_Rect* currentClip = nullptr);

	int getKillCount() {
		return killCount;
	}

	void setKillCount(const int& killCount) {
		this->killCount = killCount;
	}

	void setScoreTrackerBox(const int& posX,const int& posY) {
		scoreTrackerBox.x = posX; scoreTrackerBox.y = posY;
	}

	void increaseKillCount() {
		killCount++;
	}
private:
	int killCount;
	SDL_Rect scoreTrackerBox;
};






//class Player
//{
//public:
//	//MOVEMENT MANAGING
//	static const int PLAYER_VEL = 10;
//
//	//Initializes the variables
//	Player(const int& TEXTURE_WIDTH, const int& TEXTURE_HEIGHT);
//
//	//Takes key presses and adjusts the dot's velocity
//	int handleEvent(SDL_Event& e, int& DIRECTION_CHECK);
//
//	bool movePlayer(std::array<Tile*, TOTAL_TILES>& tiles, bool& isCollidedWithWall);
//
//	void decreaseCorpseDuration() {
//		corpseDuration--;
//	}
//
//	int getCorpseDuration() {
//		return corpseDuration;
//	}
//
//	void setPlayerCollisionBoxPosX(const int& oldPlayerCollisionBoxX) {
//		playerCollisionBox.x = oldPlayerCollisionBoxX;
//	}
//
//	void setPlayerCollisionBoxPosY(const int& oldPlayerCollisionBoxY) {
//		playerCollisionBox.y = oldPlayerCollisionBoxY;
//	}
//
//	bool getIsDead() {
//		return isDead;
//	}
//
//	void setIsDeadToTrue() {
//		isDead = true;
//	}
//
//	//Centers the camera over the player
//	void setCamera(SDL_Rect& camera);
//
//	//Shows the dot on the screen
//	void renderPlayer(SDL_Rect& camera, Texture& gPlayerTexture, SDL_Rect* currentClip = nullptr);
//
//	SDL_Rect getPlayerCollisionBox() {
//		return playerCollisionBox;
//	}
//
//private:
//
//	SDL_Rect playerCollisionBox;
//
//	int playerVelX, playerVelY;
//	int corpseDuration;
//	bool isDead;
//};