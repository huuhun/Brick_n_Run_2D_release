#include "../include/CommonFuncs/window_funcs.h"

void capFrameRate() {
	static Uint32 currentTime = 0;
	static Uint32 lastTime = 0;
	static float deltaTime = 0.0f;

	currentTime = SDL_GetTicks();
	deltaTime = ( currentTime - lastTime ) / 1000.f;
	lastTime = currentTime;

	// Cap the frame rate to 60 FPS
	Uint32 frameTime = SDL_GetTicks() - currentTime;
	if( frameTime < 16 ) // 1000 milliseconds / 60 frames per second = 16.6666 milliseconds per frame
	{
		SDL_Delay(16 - frameTime);
	}
}

int showDeadMenu(WindowManager*& gGameWindow, TTF_Font*& gFont, Texture& chooseArrowTexture, Menu& chooseArrow, int& menuState) {
	int deadDecision = NOTHING;

	SDL_SetRenderDrawColor(gGameWindow->getRenderer(), 0, 0, 0, 255);
	SDL_RenderClear(gGameWindow->getRenderer());

	Text gameOverLabel(SCREEN_WIDTH / 2 - 57, SCREEN_HEIGHT / 2 - 47, 0, 0);
	Text tryAgainLabel(SCREEN_WIDTH / 2 - 40, SCREEN_HEIGHT / 2 - 3, 0, 0);
	Text backToMenuLabel(SCREEN_WIDTH / 2 - 60, SCREEN_HEIGHT / 2 + 30, 0, 0);

	Texture gameOverTexture(gGameWindow->getRenderer());
	Texture tryAgainTexture(gGameWindow->getRenderer());
	Texture backToMenuTexture(gGameWindow->getRenderer());

	std::stringstream gameOverText;
	std::stringstream tryAgainText;
	std::stringstream backToMenuText;

	SDL_Color gameOverTextColor = { 255, 255, 255, 255 };

	gameOverText.str("");
	gameOverText << "GAME OVER";
	if( !gameOverTexture.loadFromRenderedText(gameOverText.str().c_str(), gameOverTextColor, gFont, gGameWindow->getRenderer()) )
	{
		std::cout << "Unable to render game over text!" << "\n";
	}
	gameOverLabel.render(gameOverTexture);

	tryAgainText.str("");
	tryAgainText << "Try Again";
	if( !tryAgainTexture.loadFromRenderedText(tryAgainText.str().c_str(), gameOverTextColor, gFont, gGameWindow->getRenderer()) )
	{
		std::cout << "Unable to render try again text!" << "\n";
	}
	tryAgainLabel.render(tryAgainTexture);

	backToMenuText.str("");
	backToMenuText << "Back To Menu";
	if( !backToMenuTexture.loadFromRenderedText(backToMenuText.str().c_str(), gameOverTextColor, gFont, gGameWindow->getRenderer()) )
	{
		std::cout << "Unable to render backToMenu text!" << "\n";
	}
	backToMenuLabel.render(backToMenuTexture);

	chooseArrow.moveChooseArrowBackToFirst(menuState);
	chooseArrow.render(chooseArrowTexture);

	gGameWindow->updateScreen();

	if( chooseArrow.getDecision() == PLAY_TRY_AGAIN )
	{
		deadDecision = PLAY_TRY_AGAIN;
		menuState = PLAYING;
		chooseArrow.setDeadArrowToDefault();
		chooseArrow.setArrowPos(SCREEN_WIDTH / 2 - 85, SCREEN_HEIGHT / 2 - 3);
	}
	else if( chooseArrow.getDecision() == BACK_TO_MENU )
	{
		deadDecision = BACK_TO_MENU;
		menuState = INTRO_MENU;
		chooseArrow.setDeadArrowToDefault();
		chooseArrow.setArrowPos(SCREEN_WIDTH / 2 - 85, SCREEN_HEIGHT / 2 - 3);
	}

	return deadDecision;
}

int showIntroMenu(WindowManager*& gGameWindow, TTF_Font*& gFont, Texture& introChooseArrowTexture, Menu& introChooseArrow, Texture& logoTexture, int& menuState) {
	int introDecision = INTRO_NOTHING;

	int loadedHighscore = loadHighscoreFromFile("saves/highscore.txt");
	std::string formatedHighscore = std::string(3 - std::to_string(loadedHighscore).length(), '0') + std::to_string(loadedHighscore);

	SDL_SetRenderDrawColor(gGameWindow->getRenderer(), 0, 0, 0, 255);
	SDL_RenderClear(gGameWindow->getRenderer());

	Text playButtonLabel(SCREEN_WIDTH / 2 + 100, SCREEN_HEIGHT / 2 - 150, 0, 0);
	//Text tutorialButtonLabel(SCREEN_WIDTH / 2 + 100, SCREEN_HEIGHT / 2 - 90, 0, 0);
	Text exitButtonLabel(SCREEN_WIDTH / 2 + 100, SCREEN_HEIGHT / 2 - 90, 0, 0);
	Text highscoreLabelLocation(SCREEN_WIDTH / 2 -140, SCREEN_HEIGHT / 2 - 230, 0, 0);
	Text highscoreLocation(SCREEN_WIDTH / 2 + 30, SCREEN_HEIGHT / 2 - 230, 0, 0);

	Menu logo(SCREEN_WIDTH / 2 - 270, SCREEN_HEIGHT / 2- 150);
	Texture playButtonTexture(gGameWindow->getRenderer());
	Texture exitButtonTexture(gGameWindow->getRenderer());
	//Texture tutorialButtonTexture(gGameWindow->getRenderer());
	Texture highscoreLabelTexture(gGameWindow->getRenderer());
	Texture highscoreTexture(gGameWindow->getRenderer());

	std::stringstream playButtonText;
	std::stringstream exitButtonText;
	//std::stringstream tutorialButtonText;

	std::stringstream highscoreLabelText;
	std::stringstream highscoreText;

	SDL_Color introTextColor = { 255, 255, 255, 255 };

	highscoreLabelText.str("");
	highscoreLabelText << "HIGHSCORE: ";
	if( !highscoreLabelTexture.loadFromRenderedText(highscoreLabelText.str().c_str(), introTextColor, gFont, gGameWindow->getRenderer()) )
	{
		std::cout << "Unable to render Highscore text!" << "\n";
	}
	highscoreLabelLocation.render(highscoreLabelTexture);

	highscoreText.str("");
	highscoreText << formatedHighscore;
	if( !highscoreTexture.loadFromRenderedText(highscoreText.str().c_str(), introTextColor, gFont, gGameWindow->getRenderer()) )
	{
		std::cout << "Unable to render Highscore text!" << "\n";
	}
	highscoreLocation.render(highscoreTexture);

	playButtonText.str("");
	playButtonText << "PLAY";
	if( !playButtonTexture.loadFromRenderedText(playButtonText.str().c_str(), introTextColor, gFont, gGameWindow->getRenderer()) )
	{
		std::cout << "Unable to render play button text!" << "\n";
	}
	playButtonLabel.render(playButtonTexture);

	exitButtonText.str("");
	exitButtonText << "EXIT GAME";
	if( !exitButtonTexture.loadFromRenderedText(exitButtonText.str().c_str(), introTextColor, gFont, gGameWindow->getRenderer()) )
	{
		std::cout << "Unable to render game over text!" << "\n";
	}
	exitButtonLabel.render(exitButtonTexture);
	
	introChooseArrow.moveChooseArrowBackToFirst(menuState);
	introChooseArrow.render(introChooseArrowTexture);

	logo.render(logoTexture);

	gGameWindow->updateScreen();

	if( introChooseArrow.getIntroDecision() == PLAY )
	{
		introDecision = PLAY;
		introChooseArrow.setIntroArrowToDefault();
		introChooseArrow.setArrowPos(SCREEN_WIDTH / 2 + 46, SCREEN_HEIGHT / 2 - 150);
	}
	else if( introChooseArrow.getIntroDecision() == EXIT )
	{
		introDecision = EXIT;
		introChooseArrow.setIntroArrowToDefault();
		introChooseArrow.setArrowPos(SCREEN_WIDTH / 2 + 46, SCREEN_HEIGHT / 2 - 150);
	}

	return introDecision;
}

int showPauseMenu(WindowManager*& gGameWindow, TTF_Font*& gFont, Texture& pauseChooseArrowTexture, Menu& pauseChooseArrow, int& menuState) {
	int deadDecision = NOTHING;

	int loadedHighscore = 

	SDL_SetRenderDrawColor(gGameWindow->getRenderer(), 0, 0, 0, 255);
	SDL_RenderClear(gGameWindow->getRenderer());

	Text pauseLabel(SCREEN_WIDTH / 2 - 70, SCREEN_HEIGHT / 2 - 70, 0, 0);
	Text resumeLabel(SCREEN_WIDTH / 2 - 30, SCREEN_HEIGHT / 2 - 20, 0, 0);
	Text backToMenuLabel(SCREEN_WIDTH / 2 - 60, SCREEN_HEIGHT / 2 + 30, 0, 0);

	Texture pauseTexture(gGameWindow->getRenderer());
	Texture resumeTexture(gGameWindow->getRenderer());
	Texture backToMenuTexture(gGameWindow->getRenderer());

	std::stringstream pauseText;
	std::stringstream resumeText;
	std::stringstream backToMenuText;

	SDL_Color pauseMenuTextColor = { 255, 255, 255, 255 };

	pauseText.str("");
	pauseText << "GAME PAUSED";
	if( !pauseTexture.loadFromRenderedText(pauseText.str().c_str(), pauseMenuTextColor, gFont, gGameWindow->getRenderer()) )
	{
		std::cout << "Unable to render game over text!" << "\n";
	}
	pauseLabel.render(pauseTexture);

	resumeText.str("");
	resumeText << "Resume";
	if( !resumeTexture.loadFromRenderedText(resumeText.str().c_str(), pauseMenuTextColor, gFont, gGameWindow->getRenderer()) )
	{
		std::cout << "Unable to render try again text!" << "\n";
	}
	resumeLabel.render(resumeTexture);

	backToMenuText.str("");
	backToMenuText << "Back To Menu";
	if( !backToMenuTexture.loadFromRenderedText(backToMenuText.str().c_str(), pauseMenuTextColor, gFont, gGameWindow->getRenderer()) )
	{
		std::cout << "Unable to render backToMenu text!" << "\n";
	}
	backToMenuLabel.render(backToMenuTexture);

	pauseChooseArrow.moveChooseArrowBackToFirst(menuState);
	pauseChooseArrow.render(pauseChooseArrowTexture);

	gGameWindow->updateScreen();

	if( pauseChooseArrow.getDecision() == PLAY_TRY_AGAIN )
	{
		deadDecision = PLAY_TRY_AGAIN;
		menuState = PLAYING;
		pauseChooseArrow.setDeadArrowToDefault();
		pauseChooseArrow.setArrowPos(SCREEN_WIDTH / 2 - 90, SCREEN_HEIGHT / 2 - 20);
	}
	else if( pauseChooseArrow.getDecision() == BACK_TO_MENU )
	{
		deadDecision = BACK_TO_MENU;
		menuState = INTRO_MENU;
		pauseChooseArrow.setDeadArrowToDefault();
		pauseChooseArrow.setArrowPos(SCREEN_WIDTH / 2 - 90, SCREEN_HEIGHT / 2 - 20);
	}

	return deadDecision;
}

//case SDLK_UP:
//	posX = SCREEN_WIDTH / 2 - 90;
//	posY = SCREEN_HEIGHT / 2 - 20;
//	hovering = TRY_AGAIN;
//	std::cout << decision << "\n";
//	break;
//
//case SDLK_DOWN:
//	posX = SCREEN_WIDTH / 2 - 120;
//	posY = SCREEN_HEIGHT / 2 + 30;
//	hovering = BACK_TO_MENU;
//	std::cout << hovering << "\n";
//	break;

void showScore(Text& scoreCounter, WindowManager*& gGameWindow, TTF_Font*& gFont, Texture& scoreLabelTexture , bool& highscoreHit, int& highscoreShowOnScreenTimer) {

	Text scoreLabel(700, 1, 0, 0);
	Text highscoreAlert(430, 1, 0, 0);

	Texture scoreCounterTexture(gGameWindow->getRenderer());
	Texture highscoreAlertTexture(gGameWindow->getRenderer());

	std::stringstream scoreCounterText;
	std::stringstream highscoreAlertText;

	SDL_Color textColor = { 255, 255, 255, 255 };

	scoreLabel.render(scoreLabelTexture);
	scoreCounterText.str("");
	scoreCounterText << scoreCounter.getKillCount();
	if( !scoreCounterTexture.loadFromRenderedText(scoreCounterText.str().c_str(), textColor, gFont, gGameWindow->getRenderer()) )
	{
		std::cout << "Unable to render score counter texture!" << "\n";
	}

	scoreCounter.render(scoreCounterTexture);

	if( highscoreHit == true )
	{
		std::cout <<"---------------------------\n";
		if( highscoreShowOnScreenTimer > 0 )
		{
			highscoreAlert.render(highscoreAlertTexture);
			highscoreAlertText.str("");
			highscoreAlertText << "HIGH SCORE!!!";
			if( !highscoreAlertTexture.loadFromRenderedText(highscoreAlertText.str().c_str(), textColor, gFont, gGameWindow->getRenderer()) )
			{
				std::cout << "Unable to high score counter texture!" << "\n";
			}
			highscoreAlert.render(highscoreAlertTexture);
			highscoreShowOnScreenTimer--;

		}
	}
}

void showCountdownTimer(WindowManager*& gGameWindow, TTF_Font*& gFont, int& countdownByFrameTimer) {

	static int timeToShowTutorial = 200;

	Text countdownLabel(SCREEN_WIDTH/2 - 95, 600, 0, 0);
	Text countdownTimer(SCREEN_WIDTH / 2 + 65, 600, 0, 0);
	Text tutorial(SCREEN_WIDTH / 2 - 300 , 500, 0, 0);

	Texture countdownTimerTexture(gGameWindow->getRenderer());
	Texture countdownLabelTexture(gGameWindow->getRenderer());
	Texture tutorialTexture(gGameWindow->getRenderer());

	std::stringstream countdownLabelText;
	std::stringstream countdownTimerText;
	std::stringstream tutorialText;

	SDL_Color textColor = { 0, 0, 0, 255 };

	countdownLabel.render(countdownLabelTexture);
	countdownLabelText.str("");
	countdownLabelText << "TIME LEFT:";
	if( !countdownLabelTexture.loadFromRenderedText(countdownLabelText.str().c_str(), textColor, gFont, gGameWindow->getRenderer()) )
	{
		std::cout << "Unable to render timer counter texture!" << "\n";
	}
	countdownLabel.render(countdownLabelTexture);

	countdownTimer.render(countdownTimerTexture);
	countdownTimerText.str("");
	int second = countdownByFrameTimer / 100 * 10;
	std::string formatedSecond = std::string(4 - std::to_string(second).length(), '0') + std::to_string(second);
	size_t lastNonZero = formatedSecond.find_last_not_of('0');
	formatedSecond = formatedSecond.substr(0, lastNonZero + 1);
	countdownTimerText << formatedSecond;
	if( !countdownTimerTexture.loadFromRenderedText(countdownTimerText.str().c_str(), textColor, gFont, gGameWindow->getRenderer()) )
	{
		std::cout << "Unable to render timer counter texture!" << "\n";
	}
	countdownTimer.render(countdownTimerTexture);

	if( timeToShowTutorial > 0 )
	{
		tutorialText.str("");
		tutorialText << "Surround monsters with your brick walls to kill them";
		if( !tutorialTexture.loadFromRenderedText(tutorialText.str().c_str(), textColor, gFont, gGameWindow->getRenderer()) )
		{
			std::cout << "Unable to render timer counter texture!" << "\n";
		}
		tutorial.render(tutorialTexture);
	}
	timeToShowTutorial--;
}

