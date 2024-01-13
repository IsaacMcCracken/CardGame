// This is is where code for ai behaivior to go goes.

#ifndef AGENT_H
#define AGENT_H


#include "world.h"



WorldCoordList *WorldCoordListFindPath(
  World *world,
  Arena *turn_arena,
  WorldCoord start,
  WorldCoord end,
  U32 max_iterations
);

static inline U32 WorldCoordDistanceSqr(WorldCoord a, WorldCoord b) {
  return (a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y);
}

void WorldCoordListDraw(World *world, WorldCoordList *list, U32 start);
void AgentTurn(World *world, Arena *turn_arena, Entity *agent, CardList *hand);
#endif