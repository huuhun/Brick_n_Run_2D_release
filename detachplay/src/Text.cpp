#include "../include/score/Text.h"

Text::Text(int posX, int posY, int width, int height) {
	killCount = 0;
	scoreTrackerBox = { posX, posY, width, height };
}

void Text::render( Texture& scoreTrackerTexture, SDL_Rect* currentClip) {
	scoreTrackerTexture.renderTexture(scoreTrackerBox.x, scoreTrackerBox.y, currentClip);
}

//void Text::renderCounter( Texture& scoreTrackerTexture, SDL_Rect* currentClip) {
//	scoreTrackerTexture.renderTexture(scoreTrackerBox.x, scoreTrackerBox.y, currentClip);
//}



