#ifndef ME_WORLD_H
#define ME_WORLD_H

#include <raylib.h>
#include "arena.h"
#include "entity.h"
#include "card.h"

typedef U8 Tile;
enum {
  Tile_void,
  Tile_wall,
};

typedef U8 WorldMode;
enum {
  WorldMode_game,
  WorldMode_edit,
};

typedef struct World World;
struct World {
  WorldMode mode; 
  // world stuff
  Camera2D camera;
  U32 height;
  U32 width;
  Tile *tiles;
  EntityList *entities;
  
  // player stuff
  U32 turn_count;
  Entity *grabbing_entity;
  Card *grabbing_card;
  CardList *deck;
  CardList *hand;
  CardList *discard;
};




// World 
World WorldInit(Arena *arena, U32 width, U32 height);
void WorldLoad(World *world, Arena* arena, const char *filepath);
void WorldSave(World *world, const char *filepath);
void WorldDraw(World *world); // draws the whole world including entities

void WorldUpdateFrame(
  World *world,
  Arena *perm_arena, 
  Arena *turn_arena, 
  Arena *temp_arena
);

void WorldUpdateWorld(World *world); // used to update the state of the world


// World Coordinates
WorldCoord WorldCoordFromVector2(Vector2 v) ;
WorldCoord WorldCoordFromIndex(World *world, U32 Index);
U32 WorldIndexFromWorldCoord(World *world, WorldCoord coord);
Vector2 Vector2FromWorldCoord(WorldCoord coord);
bool WorldCoordEqual(WorldCoord a, WorldCoord b);

#endif