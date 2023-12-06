// This is is where code for ai behaivior to go goes.

#include "arena.h"
#include "world.h"


typedef struct PathNode PathNode;
struct PathNode {
  PathNode *next;
  WorldCoord coord;
};

typedef struct PathNodeList PathNodeList;
struct PathNodeList {
  PathNode *first;
  PathNode *last;
  U64 count;
}; 



PathNodeList *FindPath(
  World *world,
  Arena *turn_arena,
  WorldCoord start,
  WorldCoord end,
  U32 max_iterations
);

void PathNodeListDraw(World *world, PathNodeList *list);