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


void EntityUpdate(Entities *list, Arena *perm_arena);
void GameGuiDraw(World *world, Arena *turn_arena);
void CameraUpdate(World *world);


#endif