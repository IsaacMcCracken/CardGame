#include "asset.h"

void AssetLoadTexture(World *world) {
  world->textures[0] = LoadTexture("../assets/casey.png");
}