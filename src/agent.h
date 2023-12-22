// This is is where code for ai behaivior to go goes.

#ifndef AGENT_H
#define AGENT_H

#include "arena.h"
#include "world.h"

WorldCoordList *WorldCoordListFindPath(
  World *world,
  Arena *turn_arena,
  WorldCoord start,
  WorldCoord end,
  U32 max_iterations
);

void WorldCoordListDraw(World *world, WorldCoordList *list);

#endif