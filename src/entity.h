#ifndef ENTITY_H
#define ENTITY_H

#include <basetypes.h>
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

  U8 name_buffer[ENTITY_NAME_SIZE];
  U8 name_len;
  U32 health;
  U32 health_cap;

  WorldCoord grid_pos;
  Vector2 visual_pos;

  EntityFlags flags;
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

#endif // ENTITY_H