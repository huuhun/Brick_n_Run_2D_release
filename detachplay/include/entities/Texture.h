#pragma once
#include <SDL.h>
#include <SDL_ttf.h>
#include <iostream>
#include "../Constants/common_constants.h"

class Texture
{
public:
	Texture(SDL_Renderer* gRenderer);

	~Texture();

	bool loadFromFile(std::string path);

	void renderTexture(const int& texturePosX, const int& texturePosY, SDL_Rect* clip = nullptr);

	void renderSquare(const int& texturePosX, const int& texturePosY);

	void freeTexture();

	int getTextureWidth() {
		return textureWidth;
	}
	int getTextureHeight() {
		return textureHeight;
	}

	SDL_Texture* getActualTexture() {
		return actualTexture;
	}

	bool loadFromRenderedText(const std::string& textureText, SDL_Color& textColor, TTF_Font* gFont, SDL_Renderer* gRenderer);

private:
	SDL_Texture* actualTexture;
	SDL_Renderer* renderer;

	int textureWidth;
	int textureHeight;
};