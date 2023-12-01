#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "arena.h"


Arena *ArenaInit(unsigned long long capacity) {
  capacity = (capacity < Kilo(4))? Kilo(4):capacity;
  void *ptr = malloc(capacity);
  printf("ptr: %p capacity: %llu\n", ptr, capacity);
  if (!ptr) {
    return NULL;
  }
  Arena *arena = ptr;
  arena->buff = (char*)&arena[1];
  arena->align = 8;
  arena->next = NULL;
  arena->pos = 0;
  arena->cap = capacity;
  
  return arena;
}

void *ArenaPushNoZero(Arena *arena, unsigned long long size) {
  while (arena->pos + size > arena->cap) {
    if (!arena->next) {
      arena->next = ArenaInit(ARENA_DEFAULT_SIZE);
    }

    arena = arena->next;
  }

  arena->pos = ((arena->pos + arena->align - 1) / arena->align) * arena->align;

  void *result = arena->buff + arena->pos;

  arena->pos += size;

  return result;
}

void *ArenaPush(Arena *arena, unsigned long long size) {
  void *result = ArenaPushNoZero(arena, size);
  memset(result, 0, size);
  return result;
}

void ArenaReset(Arena *arena) {
  arena->pos = 0;
}

TempArena TempArenaInit(Arena *backing_arena) {
  return (TempArena){
    .arena = backing_arena,
    .pos = backing_arena->pos,
  };
}

void TempArenaDeinit(TempArena temp_arena) {
  temp_arena.arena->pos = temp_arena.pos;
}
