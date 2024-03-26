#pragma once

#include <SDL.h>
#include <sstream>

#include "../window/WindowManager.h"
#include  "../entities/Texture.h"
#include  "../entities/Menu.h"
#include  "../entities/Player.h"
#include  "../score/Text.h"

#include "../CommonFuncs/read_write_files_funcs.h"

#include "../Enums/menu_enum.h"

class Text;
class Texture;
class Menu;
class Player;

void capFrameRate();
int showDeadMenu(WindowManager*& gGameWindow, TTF_Font*& gFont, Texture& chooseArrowTexture, Menu& chooseArrow, int& menuState);
int showPauseMenu(WindowManager*& gGameWindow, TTF_Font*& gFont, Texture& pauseChooseArrowTexture, Menu& pauseChooseArrow, int& menuState);
int showIntroMenu(WindowManager*& gGameWindow, TTF_Font*& gFont, Texture& introChooseArrowTexture, Menu& introChooseArrow,  Texture& logoTexture, int& menuState);
void showScore(Text& scoreCounter, WindowManager*& gGameWindow, TTF_Font*& gFont, Texture& scoreLabelTexture, bool& highscoreHit, int& highscoreShowOnScreenTimer);
void showCountdownTimer(WindowManager*& gGameWindow, TTF_Font*& gFont, int& countdownByFrameTimer); int showIntroMenu(WindowManager*& gGameWindow, TTF_Font*& gFont, Texture& introChooseArrowTexture, Menu& introChooseArrow, Texture& logoTexture, int& menuState);
