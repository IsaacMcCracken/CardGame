// This is is where code for ai behaivior to go goes.


#include "world.h"

WorldCoordList *WorldCoordListFindPath(
  World *world,
  Arena *turn_arena,
  WorldCoord start,
  WorldCoord end,
  U32 max_iterations
);

void WorldCoordListDraw(World *world, WorldCoordList *list, U32 start);