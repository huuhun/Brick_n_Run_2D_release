#pragma once
#include "../entities/HorizontalZombie.h"
#include "../entities/PlayerTrail.h"
#include "../entities/Tile.h"
#include "../entities/KillArea.h"
#include "../entities/Texture.h"
#include "../entities/VerticalZombie.h"
#include "../entities/Ghost.h"

#include "../Constants/common_constants.h"
#include "../Constants/npc_constants.h"

#include <vector>
#include <cstdlib> // for rand() and srand()
#include <ctime>   // for time()

class HorizontalZombie;
class Ghost;
class VerticalZombie;
class Texture;

void spawnATestHorizontalZombies(Texture& horizontalZombieSpirteSheetTexture, std::vector<HorizontalZombie*>& horizontalZombiesVector);

void spawnNPC(Texture& horizontalZombieSpirteSheetTexture, std::vector<HorizontalZombie*>& horizontalZombiesVector);

void spawnNPC(Texture& verticalZombieSpirteSheetTexture, std::vector<VerticalZombie*>& verticalZombiesVector);
void spawnNPC(Texture& ghostSpirteSheetTexture, std::vector<Ghost*>& ghostsVector);