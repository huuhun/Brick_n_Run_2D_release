#include <iostream>
#include <SDL.h>
#include <SDL_image.h>

#include "../include/entities/Texture.h"

Texture::Texture(SDL_Renderer* gRenderer)
{
	renderer = gRenderer;
	actualTexture = nullptr;
}

Texture::~Texture()
{
	freeTexture();
}

bool Texture::loadFromFile(std::string path)
{
	//Get rid of preexisting texture
	freeTexture();

	//The final texture
	SDL_Texture* finalTexture = nullptr;

	//Load image at specified path (surface is 2d image)
	SDL_Surface* loadedSurface = IMG_Load(path.c_str());

	if( loadedSurface == nullptr )
	{
		printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
	}
	else
	{
		//Color key image (make transparent background)
		SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0, 0xFF, 0xFF));

		//Create texture from surface pixels
		finalTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
		if( finalTexture == nullptr )
		{
			printf("Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
		}
		else
		{
			//Get image dimensions to object
			textureWidth = loadedSurface->w;
			textureHeight = loadedSurface->h;

			std::cout << "Texture width while load from file: " << textureWidth << "\n";
			std::cout << "Texture height while load from file: " << textureHeight << "\n";

		}

		//Get rid of old loaded surface
		SDL_FreeSurface(loadedSurface);
	}
	//Return success
	actualTexture = finalTexture;

	return actualTexture != nullptr;
}

void Texture::renderTexture(const int& texturePosX, const int& texturePosY, SDL_Rect* clip) {

	//Set rendering space and render to target location on screen
	SDL_Rect renderQuad = { texturePosX , texturePosY , textureWidth, textureHeight };

	if( clip != nullptr )
	{
		renderQuad.w = clip->w;
		renderQuad.h = clip->h;
	}
	//Render to screen
	SDL_RenderCopy(renderer, actualTexture, clip, &renderQuad);
}

void Texture::renderSquare(const int& texturePosX, const int& texturePosY) {
	////zombieKillBoxTexture.renderTexture()
	//SDL_SetRenderDrawColor(gRenderer, 255, 0, 0, 255);

	//SDL_Rect box = { zombieCollisionBox.x - zombieCollisionBox.w / 2, zombieCollisionBox.y - zombieCollisionBox.h / 2, zombieCollisionBox.w, zombieCollisionBox.h };

	//SDL_RenderDrawRect(gRenderer, &box);

	//SDL_RenderDrawPoint(gRenderer, zombieCollisionBox.x, zombieCollisionBox.y);

	SDL_SetRenderDrawColor(this->renderer, 0, 0, 255, 255); // blue

	SDL_Rect renderQuad = { texturePosX , texturePosY , textureWidth, textureHeight };

	SDL_RenderDrawRect(this->renderer, &renderQuad);

	SDL_RenderDrawPoint(this->renderer, texturePosX, texturePosY);
}

bool Texture::loadFromRenderedText(const std::string& textureText, SDL_Color& textColor, TTF_Font* gFont, SDL_Renderer* gRenderer) {
	//Get rid of preexisting texture
	freeTexture();

	//Render text surface
	
	SDL_Surface* textSurface = TTF_RenderText_Solid(gFont, textureText.c_str(), textColor);
	if( textSurface == nullptr )
	{
		std::cout << "Hey, unable to render text surface!SDL_ttf Error : " << TTF_GetError() << "\n";
	}
	else
	{
		//Create texture from surface pixels
		actualTexture = SDL_CreateTextureFromSurface(gRenderer, textSurface);
		if( actualTexture == nullptr )
		{
			std::cout << "Unable to create texture from rendered text! SDL Error: " << SDL_GetError() << "\n";
		}
		else
		{
			//Get image dimensions
			textureWidth = textSurface->w;
			textureHeight = textSurface->h;
		}

		//Get rid of old surface
		SDL_FreeSurface(textSurface);
	}

	//Return success
	return actualTexture != nullptr;
}

void Texture::freeTexture()
{
	//Free texture if it exists
	if( actualTexture != nullptr )
	{
		SDL_DestroyTexture(actualTexture);
		//delete actualTexture;  //error 
		actualTexture = nullptr;
		textureWidth = 0;
		textureHeight = 0;

		//std::cout << "Textures freed\n";
	}
}