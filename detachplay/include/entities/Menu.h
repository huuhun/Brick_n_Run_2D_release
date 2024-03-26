#pragma once
#include <SDL.h>
#include <SDL_mixer.h>

#include <array>

#include "Texture.h"

#include "../Constants/common_constants.h"
#include "../Enums/menu_enum.h"

#include "../CommonFuncs/collision_funcs.h"

class Texture;

class Menu
{
public:
	//Initializes the variables
	Menu(const int& posX, const int& posY);

	//Takes key presses and adjusts the dot's velocity
	void handleEvent(SDL_Event& e, int& menuState, Mix_Chunk*& gChangeSelection);
	void moveChooseArrowBackToFirst(int& menuState);
	void setPosX(const int& posX) {
		this->posX = posX;
	}

	void setPosY(const int& posY) {
		this->posY = posY;
	}

	//Shows the dot on the screen
	void render(Texture& gMenuTexture, SDL_Rect* currentClip = nullptr);

	int getDecision() {
		return decision;
	}

	int getIntroDecision() {
		//std::cout << "get intro des: " << introDecision << "\n";
		return introDecision;
	}

	void setDeadArrowToDefault() {
		decision = NOTHING;
		hovering = PLAY_TRY_AGAIN;
	}

	void setIntroArrowToDefault() {
		introDecision = INTRO_NOTHING;
		introHovering = PLAY;
	}

	void setPauseArrowToDefault() {
		introDecision = INTRO_NOTHING;
		introHovering = PLAY;
	}

	void setArrowPos(const int& posX, const int& posY) {
		this->posX = posX;
		this->posY = posY;
	}

private:
	int decision, hovering, introHovering, introDecision, pauseHovering, pauseDecision;
	int posX, posY;
	//int menuState;
};