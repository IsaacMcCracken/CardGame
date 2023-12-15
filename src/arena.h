#ifndef ME_ARENA
#define ME_ARENA

#include <basetypes.h>

#define Kilobyte(x) ((x)<<10)
#define Megabyte(x) ((x)<<20)
#define Gigabyte(x) (((U64)(x))<<30)

#define ARENA_DEFAULT_SIZE  Megabyte(1)


typedef struct Arena Arena;
struct Arena {
  char *buff;
  U64 pos;
  U64 cap;
  U64 align;
  Arena *next;
  U64 unused[3];
};

typedef struct TempArena TempArena;
struct TempArena {
  Arena *arena;
  U64 pos;
};



Arena *ArenaInit(U64 capacity);
void ArenaDeinit(Arena *arena);
void ArenaReset(Arena *arena);
void *ArenaPushNoZero(Arena *arena, U64 size);
void *ArenaPush(Arena *arena, U64 size);

TempArena TempArenaInit(Arena *backing_arena);
void TempArenaDeinit(TempArena temp_arena);

#endif // ME_ARENA_H