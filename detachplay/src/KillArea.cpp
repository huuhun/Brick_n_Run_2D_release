#include "../include/entities/KillArea.h"


//KillBox::KillBox(const int& NPC_KILLBOX_POSX, const int& NPC_KILLBOX_POSY, const int& NPC_KILLBOX_WIDTH, const int& NPC_KILLBOX_HEIGHT) {
//
//	killBoxCollisionBox.x = NPC_KILLBOX_POSX;
//	killBoxCollisionBox.y = NPC_KILLBOX_POSY;
//	killBoxCollisionBox.w = NPC_KILLBOX_WIDTH;
//	killBoxCollisionBox.h = NPC_KILLBOX_HEIGHT;
//}
//
//void KillBox::syncWithNPCCollisionBox(const SDL_Rect& NPCcollisionBox) {
//	killBoxCollisionBox.x = NPCcollisionBox.x - 100;
//	killBoxCollisionBox.y = NPCcollisionBox.y - 100;
//	killBoxCollisionBox.w = NPCcollisionBox.w + 200;
//	killBoxCollisionBox.h = NPCcollisionBox.h + 230;
//}
//
//void KillBox::renderKillBox(SDL_Rect& camera, SDL_Renderer* gRenderer) {
//
//	if( SDL_SetRenderDrawColor(gRenderer, 0, 0, 255, 255) < 0 )
//	{
//		std::cout << "Can't set draw color for the test trailLine->getPlayerTileTrailCollisionBox().ngle. SDL Error: " << SDL_GetError() << "\n";
//	}
//	//std::cout << "renderKillBox w and h: " << this->killBoxCollisionBox.w << " " << this->killBoxCollisionBox.h <<"\n";
//	SDL_Rect outlineRect = { killBoxCollisionBox.x - camera.x, killBoxCollisionBox.y - camera.y, killBoxCollisionBox.w, killBoxCollisionBox.h };
//	if( SDL_RenderDrawRect(gRenderer, &outlineRect) < 0 )
//	{
//		std::cout << "Can't draw the test trailLine->getPlayerTileTrailCollisionBox().ngle. SDL Error: " << SDL_GetError() << "\n";
//	}
//}

KillArea::KillArea(const int& currentKillPointPosX, const int& currentKillPointPosY, const int& prevKillPointPosX, const int& prevKillPointPosY) {
	this->currentKillPointPosX = currentKillPointPosX + TILE_SIZE/2;
	this->currentKillPointPosY = currentKillPointPosY + TILE_SIZE/2;
	this->prevKillPointPosX = prevKillPointPosX + TILE_SIZE / 2;
	this->prevKillPointPosY = prevKillPointPosY + TILE_SIZE / 2;
	isExpired = false;
	lifetime = KILLLINES_LIFETIME;
}

void KillArea::renderKillLine(SDL_Rect& camera, SDL_Renderer* gRenderer) {

	SDL_SetRenderDrawColor(gRenderer, 0, 0, 255, 255); //BLUE

	SDL_RenderDrawLine(gRenderer, currentKillPointPosX - camera.x, currentKillPointPosY - camera.y, prevKillPointPosX - camera.x, prevKillPointPosY - camera.y);

}

void KillArea::renderKillAreaPolygon(SDL_Rect& camera, SDL_Renderer* gRenderer) {
	SDL_SetRenderDrawColor(gRenderer, 255, 0, 0, 255);//RED

	SDL_RenderDrawLine(gRenderer, currentKillPointPosX - camera.x, currentKillPointPosY - camera.y, prevKillPointPosX - camera.x, prevKillPointPosY - camera.y);
}

void KillArea::destroySelf(KillArea* killLine) {
	if( killLine != nullptr )
	{
		delete killLine;
		killLine = nullptr;
		std::cout << "A killline destroyed\n";
	}
}
