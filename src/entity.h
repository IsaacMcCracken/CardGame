#ifndef ENTITY_H
#define ENTITY_H

#include <basetypes.h>
#include <raylib.h>
#include "arena.h"

#define ENTITY_NAME_SIZE 64


typedef struct EffectFlags EffectFlags;
struct EffectFlags {
  U8 is_on_fire: 1;
  U8 is_iced: 1;
  U8 is_greesed: 1;
  U8 is_acidified: 1;
  U8 is_wet: 1;
  U8 is_electrified: 1;
};

typedef struct EntityFlags EntityFlags;
struct EntityFlags {
  U8 is_flamable: 1;
  U8 is_freezable: 1;
  U8 is_wetable: 1; // is it able to get wet
  U8 __padding__ : 6;
};

typedef struct Entity Entity;
struct Entity {
  Entity *next;
  Entity *prev;

  char name_buffer[ENTITY_NAME_SIZE];
  U8 name_len;
  U16 health;
  U16 health_cap;
  U16 health_temp;


  WorldCoord grid_pos;
  Vector2 visual_pos;

  WorldCoordList *path;
  U32 path_index;
  F32 path_ratio;

  EntityFlags flags;

  // Game Stuff
  U8 action_count;
  U8 bonus_count; // bonus action count
};

typedef struct EntityList EntityList;
struct EntityList {
  Entity *first;
  Entity *last;
  Entity *free_list;
  U64 count;
};

// for loop entity iterator
#define EachEntity(it, first) Entity *it = (first); it != NULL; it = it->next 


Entity *EntityAlloc(Arena *arena, EntityList *list, const char *name);
Entity *EntityFindByWorldCoord(EntityList *list, WorldCoord coord);
#endif // ENTITY_H