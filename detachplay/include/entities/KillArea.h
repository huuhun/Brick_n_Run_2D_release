#pragma once

#include <SDL.h>
#include <vector>
#include <iostream>

#include "../Constants/common_constants.h"

class KillArea
{
public:
	KillArea(const int& currentKillPointPosX, const int& currentKillPointPosY, const int& prevKillPointPosX, const int& prevKillPointPosY);
	
	int getCurrentKillPointPosX() {
		return currentKillPointPosX;
	}

	int getCurrentKillPointPosY() {
		return currentKillPointPosY;
	}

	int getPrevKillPointPosX() {
		return prevKillPointPosX;
	}

	int getPrevKillPointPosY() {
		return prevKillPointPosY;
	}

	void setPrevKillPointPosX(int prevKillPointPosX) {
		this->prevKillPointPosX = prevKillPointPosX;
	}
	void setPrevKillPointPosY(int prevKillPointPosY) {
		this->prevKillPointPosY = prevKillPointPosY;
	}

	void renderKillLine(SDL_Rect& camera, SDL_Renderer* gRenderer);

	void renderKillAreaPolygon(SDL_Rect& camera, SDL_Renderer* gRenderer);

	void destroySelf(KillArea* killLine);

	bool getIsExpired() {
		return isExpired;
	}

	void setIsExpiredToTrue() {
		isExpired = true;
	}

	void decreaseLifeTime() {
		lifetime--;
	}

	bool checkIfExpired() {
		if( lifetime <= 0 )
			return true;
		return false;
	}

private:
	int currentKillPointPosX, currentKillPointPosY;
	int prevKillPointPosX, prevKillPointPosY;
	bool isExpired;
	int lifetime;
};


