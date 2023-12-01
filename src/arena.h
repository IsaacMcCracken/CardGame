#ifndef ME_ARENA
#define ME_ARENA


#define Kilo(x) ((x)<<10)
#define Mega(x) ((x)<<20)
#define Giga(x) (((unsigned long long)(x))<<30)

#define ARENA_DEFAULT_SIZE  Mega(1)


typedef struct Arena Arena;
struct Arena {
  char *buff;
  unsigned long long pos;
  unsigned long long cap;
  unsigned long long align;
  Arena *next;
};

typedef struct TempArena TempArena;
struct TempArena {
  Arena *arena;
  unsigned long long pos;
};



Arena *ArenaInit(unsigned long long capacity);
void ArenaReset(Arena *arena);
void ArenaDeinit(Arena *arena);
void *ArenaPushNoZero(Arena *arena, unsigned long long size);
void *ArenaPush(Arena *arena, unsigned long long size);

TempArena TempArenaInit(Arena *backing_arena);
void TempArenaDeinit(TempArena temp_arena);

#endif