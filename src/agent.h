// This is is where code for ai behaivior to go goes.

#include "arena.h"
#include "world.h"




typedef struct WorldCoordList WorldCoordList;
struct WorldCoordList {
  WorldCoord *ptr;
  U64 len;
}; 



WorldCoordList *FindPath(
  World *world,
  Arena *turn_arena,
  WorldCoord start,
  WorldCoord end,
  U32 max_iterations
);

void WorldCoordListDraw(World *world, WorldCoordList *list);