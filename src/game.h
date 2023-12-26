#ifndef GAME_H
#define GAME_H

/* Game Stuff Actions such as input and UI here */
#include "world.h"



void GamePlayUpdate(  
  World *world,
  Arena *perm_arena, 
  Arena *turn_arena, 
  Arena *temp_arena
);


void EntityUpdate(EntityList *list, Arena *perm_arena);
void GameGuiDraw(World *world);

#endif