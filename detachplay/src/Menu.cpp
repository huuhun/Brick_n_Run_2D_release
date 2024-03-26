#include "../include/entities/Menu.h"

Menu::Menu(const int& posX, const int& posY)
{
	decision = NOTHING;
	introDecision = INTRO_NOTHING;

	hovering = PLAY_TRY_AGAIN;
	introHovering = PLAY;

	this->posX = posX;
	this->posY = posY;

	//newPosX = 10;
	//newPosY = 10;

	//tempPosX = 0;
	//tempPosY = 0;
}

void Menu::handleEvent(SDL_Event& e, int& menuState, Mix_Chunk*& gChangeSelection)
{
	//std::cout << "handleEvent's menuState:" << menuState << "\n";
	if( e.type == SDL_KEYDOWN && e.key.repeat == 0 && menuState == DEAD_MENU )
	{
		//Adjust the velocity
		switch( e.key.keysym.sym )
		{
		case SDLK_UP:
			posX = SCREEN_WIDTH / 2 - 85;
			posY = SCREEN_HEIGHT / 2 - 3;
			hovering = PLAY_TRY_AGAIN;
			std::cout << decision << "\n";
			break;

		case SDLK_DOWN:
			posX = SCREEN_WIDTH / 2 - 111;
			posY = SCREEN_HEIGHT / 2 + 30;
			hovering = BACK_TO_MENU;
			std::cout << hovering << "\n";
			break;

		case SDLK_RETURN:
			if( hovering == PLAY_TRY_AGAIN )
			{
				std::cout << "Try again\n";
				decision = hovering;
				Mix_PlayChannel(-1, gChangeSelection, 0);
			}
			else if( hovering == BACK_TO_MENU )
			{
				std::cout << "Back\n";
				decision = hovering;
				Mix_PlayChannel(-1, gChangeSelection, 0);
			}
			break;
		}
	}

	/*Text playButtonLabel(SCREEN_WIDTH / 2 + 100, SCREEN_HEIGHT / 2 - 150, 0, 0);
	Text exitButtonLabel(SCREEN_WIDTH / 2 + 100, SCREEN_HEIGHT / 2 - 90, 0, 0);
	*/

	else if( e.type == SDL_KEYDOWN && e.key.repeat == 0 && menuState == INTRO_MENU )
	{
		//Adjust the velocity
		switch( e.key.keysym.sym )
		{
		case SDLK_UP:
			posX = SCREEN_WIDTH / 2 + 46;
			posY -= 60;
			if( posY == SCREEN_HEIGHT / 2 - 150 )
			{
				introHovering = PLAY;
			}
			/*std::cout << hovering << "\n";
			std::cout << introHovering << "\n";*/
			break;

		case SDLK_DOWN:
			posX = SCREEN_WIDTH / 2 + 46;
			posY += 60;
			/*if( posY == SCREEN_HEIGHT / 2 - 60 )
			{*/
				introHovering = EXIT;
			/*}*/
			std::cout << "Here posY:" << posY<< "\n"; //230
			std::cout<<"what MOVIND DOW " << introHovering << "\n";

			//std::cout <<"what is this" << hovering << "\n";
			break;

		case SDLK_RETURN:
			if( introHovering == PLAY )
			{
				std::cout << "PLAY\n";
				introDecision = introHovering;
				Mix_PlayChannel(-1, gChangeSelection, 0);
			}
			else if( introHovering == CHOOSE_TUTORIAL )
			{
				std::cout << "CHOOSE_TUTORIAL\n";
				introDecision = introHovering;
				Mix_PlayChannel(-1, gChangeSelection, 0);
			}
			else if( introHovering == EXIT )
			{
				std::cout << "EXIT\n";
				introDecision = introHovering;
				Mix_PlayChannel(-1, gChangeSelection, 0);
			}
			break;
		}
	}

	else if( e.type == SDL_KEYDOWN && e.key.repeat == 0 && menuState == PAUSED )
	{
		//Adjust the velocity
		switch( e.key.keysym.sym )
		{
		case SDLK_UP:
			posX = SCREEN_WIDTH / 2 - 90;
			posY = SCREEN_HEIGHT / 2 - 20;
			hovering = PLAY_TRY_AGAIN;
			std::cout << decision << "\n";
			break;

		case SDLK_DOWN:
			posX = SCREEN_WIDTH / 2 - 120;
			posY = SCREEN_HEIGHT / 2 + 30;
			hovering = BACK_TO_MENU;
			std::cout << hovering << "\n";
			break;

		case SDLK_RETURN:
			if( hovering == PLAY_TRY_AGAIN )
			{
				std::cout << "Try again\n";
				decision = hovering;
				Mix_PlayChannel(-1, gChangeSelection, 0);
			}
			else if( hovering == BACK_TO_MENU )
			{
				std::cout << "Back\n";
				decision = hovering;
				Mix_PlayChannel(-1, gChangeSelection, 0);
			}
			break;
		}
	}

	//If a key was released
	//if( e.type == SDL_KEYUP && e.key.repeat == 0 )
	//{
	//	//Adjust the velocity
	//	switch( e.key.keysym.sym )
	//	{
	//	case SDLK_UP: posX = 30; decision--;
	//		std::cout<< posY << " HEY\n";
	//		break;
	//	case SDLK_DOWN: posX = 60; decision++;
	//		std::cout << posY << " HEY\n";
	//		break;
	//	}
	//}
}

void Menu::moveChooseArrowBackToFirst(int& menuState)
{
	//If the dot went too far to the left or right
	if( hovering != NOTHING && hovering != PLAY_TRY_AGAIN && hovering != BACK_TO_MENU && menuState == DEAD_MENU )
	{
		//Move back
		hovering = PLAY_TRY_AGAIN;
		std::cout << "Reset decision:" << hovering << "\n";
	}
	else if( posY != SCREEN_HEIGHT / 2 - 150 && posY != SCREEN_HEIGHT / 2 - 90  && menuState == INTRO_MENU )
	{
		introHovering = PLAY;
		posY = SCREEN_HEIGHT / 2 - 150;
		std::cout << "Reset decision:" << introHovering << "\n";
	}
}

void Menu::render(Texture& gMenuTexture, SDL_Rect* currentClip)
{
	gMenuTexture.renderTexture(posX, posY, currentClip);
}