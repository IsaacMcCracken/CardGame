#ifndef ME_WORLD_H
#define ME_WORLD_H

#include <raylib.h>
#include "arena.h"

struct Entity;

typedef U8 Tile;
enum {
  Tile_void,
  Tile_wall,
};

typedef struct World World;
struct World {
  Camera2D camera;
  U32 height;
  U32 width;
  Tile *tiles;
  
};

typedef struct WorldCoord WorldCoord;
struct WorldCoord {
  I32 x;
  I32 y;
};

// World 
World WorldInit(Arena *arena, U32 width, U32 height);
void WorldLoad(World *world, Arena* arena, const char *filepath);
void WorldSave(World *world, const char *filepath);
void WorldDraw(World *world); // draws the whole world including entities
void WorldUpdateFrame(World *world, Arena *temp_arena); // used to update animations and get input
void WorldUpdateWorld(World *world); // used to update the state of the world


// World Coordinates
WorldCoord WorldCoordFromVector2(Vector2 v) ;
WorldCoord WorldCoordFromIndex(World *world, U32 Index);
U32 WorldIndexFromWorldCoord(World *world, WorldCoord coord);
Vector2 Vector2FromWorldCoord(WorldCoord coord);

#endif