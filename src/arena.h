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
}

#endif