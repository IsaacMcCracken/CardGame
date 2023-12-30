#ifndef SERIALIZATION_H
#define SERIALIZATION_H

#include "world.h"

typedef U32 SerializeEnityIndex;

typedef struct WorldFileHeader WorldFileHeader;
struct WorldFileHeader {
  U32 entity_count;
  U32 room_offset;
  U32 room_count;
  U32 reserved;
};


typedef struct SerializeEnity SerializeEnity;
struct SerializeEnity {
  char name_buffer[ENTITY_NAME_SIZE];
  U8 name_len;
  U16 health;
  U16 movement;

  EntityFaction faction;
  EntityFlags flags;
  U8 texture;
  F32 h_flip;
};

typedef struct RoomHeader RoomHeader;
struct RoomHeader {
  char name_buffer[256];
  U8 name_len;

  U32 width;
  U32 height;
};

typedef struct RoomEntity RoomEntity;
struct RoomEntity {
  SerializeEnityIndex index;
  WorldCoord coord;
};

void SerializeWorld(Arena *temp_arena, World *world, const char *filename);
void LoadWorld(Arena *perm_arena, World *world, const char *filename);

#endif