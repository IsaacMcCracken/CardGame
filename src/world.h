#ifndef ME_WORLD_H
#define ME_WORLD_H

#include <raylib.h>
#include "arena.h"
#include "entity.h"
#include "card.h"


typedef U8 AnimationStates;
enum {
  AnimationState_standing,
  AnimationState_attacking,
  AnimationState_running,
};


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


typedef struct TurnData TurnData;
struct TurnData {
  Entity *characters[128]; // need a more dynamic solution but a static array will work for now;
  U32 current_turn;
  U32 current_turn_len;
};

typedef struct World World;
struct World {
  WorldMode mode; 
  // world stuff
  Camera2D camera;
  U32 height;
  U32 width;
  Tile *tiles;
  Entities *entities;
  
  // player stuff
  U32 turn_count;
  Entity *selected_entity;
  Card *grabbing_card;
  WorldCoordList *selected_path;

  Deity player;
  Deity enemy;
  TurnData turn_data;
  // maybe have asset structure
  Texture *textures;

};



// World 
World WorldInit(Arena *arena, U32 width, U32 height);
void WorldLoad(World *world, Arena* arena, const char *filepath);
void WorldSave(World *world, const char *filepath);
void WorldDraw(World *world, Arena *turn_arena); // draws the whole world including entities

void WorldUpdateFrame(
  World *world,
  Arena *perm_arena, 
  Arena *turn_arena, 
  Arena *temp_arena
);
void WorldUpdateTurn(World *world, Arena *turn_arena);

// World Coordinates
WorldCoord WorldCoordFromVector2(Vector2 v) ;
WorldCoord WorldCoordFromIndex(World *world, U32 Index);
U32 WorldIndexFromWorldCoord(World *world, WorldCoord coord);
Vector2 Vector2FromWorldCoord(WorldCoord coord);
U32 WorldIndexFromVector2(World *world, Vector2 v);
bool WorldCoordEqual(WorldCoord a, WorldCoord b);


#endif