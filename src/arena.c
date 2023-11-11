#include <stdlib.h>
#include <string.h>
#include "arena.h"


Arena *ArenaInit(unsigned long long capacity) {
  capacity = (capacity < (4<<10))? (4<<10):capacity;
  Arena *arena = malloc(capacity);
  arena->buff = (char*)arena + sizeof(arena);
  arena->align = 8;
  arena->next = 0;
  arena->pos = 0;
  
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

void *ArenaReset(Arena *Arena) {

}

