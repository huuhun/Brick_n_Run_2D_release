#pragma once
#include <SDL.h>
#include <iostream>
#include <vector>
#include <fstream>

void saveHighscoreToFile(int highscore, const std::string& filename);
int loadHighscoreFromFile(const std::string& filename);

