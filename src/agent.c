#include "agent.h"
#include "raymath.h"
#include <stdlib.h>
#include <assert.h>



typedef struct AStarNode AStarNode;
struct AStarNode {
  AStarNode *prev_path; // previous node in the path
  AStarNode *next_list; // next in the list
  WorldCoord coord;
  U32 g_cost; 
  U32 h_cost;
};


// Turn these structures into heap nodes
typedef struct AStarList AStarList;
struct AStarList {
  AStarNode *first;
  AStarNode *last;
  U64 count;
};


U32 AStarNodeDistance(AStarNode *a, AStarNode *b) {
  // dont be scared this is just the absolute distance
  U32 distance_x = labs(a->coord.x - b->coord.x);
  U32 distance_y = labs(a->coord.y - b->coord.y);

  if (distance_x > distance_y)
    return 14 * distance_y + 10 * (distance_x - distance_y); // 14 = ~10*sqrt(2)

  return 14 * distance_x + 10 * (distance_y - distance_x);
}


U32 AStarNodeFCost(AStarNode *node) {
  return node->g_cost + node->h_cost;
}


AStarNode *AStarNodeCreate(Arena *arena, WorldCoord coord) {
  AStarNode *result = ArenaPush(arena, sizeof(AStarNode));
  result->coord = coord;
  // calculate g_cost and h_cost
  return result;
}


void AStarListAppend(AStarList *list, AStarNode *node) {
  if (list->last) {
    list->last->next_list = node;
    list->last = node;
    list->count += 1;
  } else {
    list->first = node;
    list->last = node;
    list->count = 1;
  }
}


// TODO: test this 
void AStarListRemove(AStarList *list, AStarNode *node) {
  if (list->first == node) {
    list->first = node->next_list;
    if (list->last == node) {
      list->first = NULL;
      list->last = NULL;
      list->count = 0;
      return;
    }

    list->count -= 1;
    return;
  }

  AStarNode *current = list->first;
  AStarNode *prev = NULL;
  while (current && current != node) {
    AStarNode *next = current->next_list;

    prev = current;
    current = next;
  }
  // make sure this node is in this list
  
  if (prev) {
    prev->next_list = node->next_list;
    list->count -= 1;
  } else {
    list->first = NULL;
    list->last = NULL;
    list->count = 0;
  }
}


AStarNode *AStarListFindByCoord(AStarList *list, WorldCoord coord) {
  AStarNode *node = list->first;
  while (node) {
    AStarNode *next = node->next_list;
    
    if (coord.x == node->coord.x && coord.y == node->coord.y)
      return node;

    node = next;
  }
  
  return NULL;
}


WorldCoordList *WorldCoordListFromAStar(Arena *arena, AStarNode *end_node) {
  U32 path_node_count = 0;
  AStarNode *astar_node = end_node;
  while (astar_node) {
    path_node_count++;
    astar_node = astar_node->prev_path;
  }

  WorldCoordList *list = ArenaPush(arena, sizeof(WorldCoordList));

  WorldCoord *coord_array = ArenaPush(arena, sizeof(WorldCoord) * path_node_count);
  astar_node = end_node;
  for (U32 i = 0; i < path_node_count; i++) {
    coord_array[path_node_count - i - 1] = astar_node->coord;

    astar_node = astar_node->prev_path;
  }

  if (coord_array) {
    list->len = path_node_count;
    list->ptr = coord_array;
  }
  
  
  return list;
}


// This function can return null 
WorldCoordList *WorldCoordListFindPath(
  World *world,
  Arena *turn_arena,
  WorldCoord start,
  WorldCoord end,
  U32 max_iterations
) {
  // Lets check if we can actually get to the place
  if (end.x < 0 || end.x >= world->width || end.y < 0 || end.y >= world->height)
    return NULL;
  else if (world->tiles[WorldIndexFromWorldCoord(world, end)] == Tile_wall)
    return NULL;


  // We have a closed list and a open_list
  AStarList *closed_list = ArenaPush(turn_arena, sizeof(AStarList));
  AStarList *open_list = ArenaPush(turn_arena, sizeof(AStarList));

  // we have the start_list and append 
  AStarNode *start_node = AStarNodeCreate(turn_arena, start);
  AStarListAppend(open_list, start_node);

  AStarNode end_data = (AStarNode){.coord = end};
  AStarNode *end_node = &end_data;

  U32 iter = 0;
  
  while (open_list->count > 0 && (iter < max_iterations || max_iterations == 0)) {
    iter += 1;

    // This is the node that we are going to evaluate
    AStarNode *current_node = open_list->first;

    // we first get this node by naively going through the list
    // and getting the smallest one.
    AStarNode *node = current_node;
    while (node && node->next_list) {
      AStarNode *next = node->next_list;

      // get the node with the lowest f cost
      if (AStarNodeFCost(node) < AStarNodeFCost(current_node)) 
        current_node = node;

      node = next;
    }

    // Once we have the node with the lowest f-cost we 
    // add it to the closed list.
    AStarListRemove(open_list, current_node);
    AStarListAppend(closed_list, current_node);

    // now if the current node is in our target coord we end the cycle
    if (current_node->coord.x == end.x && current_node->coord.y == end.y) 
      return WorldCoordListFromAStar(turn_arena, current_node);

    // Go through each neighbor
    const WorldCoord p = current_node->coord;
    WorldCoord neighborCoord[8] = {
      {p.x - 1, p.y + 1}, {p.x, p.y + 1}, {p.x + 1, p.y + 1},
      {p.x - 1, p.y},                     {p.x + 1, p.y},
      {p.x - 1, p.y - 1}, {p.x, p.y -1 }, {p.x + 1, p.y - 1}
    };

    // First We get all the neighbors
    for (U8 i = 0; i < 8; i++) {

      // we bound check with the world's dimensions if its not in the
      // dimensions we skip it.
      if (neighborCoord[i].x < 0 || neighborCoord[i].x > world->width ||
        neighborCoord[i].y < 0 || neighborCoord[i].y > world->height)
        continue;

      // also if the tile is not tranversable 
      U32 world_index = WorldIndexFromWorldCoord(world, neighborCoord[i]);
      if (world->tiles[world_index] == Tile_wall)
        continue;

      // Or the node had already been in
      if (AStarListFindByCoord(closed_list, neighborCoord[i])) 
        continue;


      AStarNode *neighbor = AStarListFindByCoord(open_list, neighborCoord[i]);

      if (neighbor) {
        U32 new_movement_cost = current_node->g_cost + AStarNodeDistance(current_node, neighbor);

        if (new_movement_cost < neighbor->g_cost) {
          neighbor->g_cost = new_movement_cost;
          neighbor->h_cost = AStarNodeDistance(neighbor, end_node);
          neighbor->prev_path = current_node;
        }
      } else {
      

        neighbor = AStarNodeCreate(turn_arena, neighborCoord[i]);

        U32 new_movement_cost = current_node->g_cost + AStarNodeDistance(current_node, neighbor);

        neighbor->g_cost = new_movement_cost;
        neighbor->h_cost = AStarNodeDistance(neighbor, end_node);
        neighbor->prev_path = current_node;

        AStarListAppend(open_list, neighbor);
      }
    }
  }

  TraceLog(LOG_INFO, "Open List Count: %lu, Closed List Count: %lu, Iter: %lu", open_list->count, closed_list->count, iter);
  TraceLog(LOG_DEBUG, "Seriously what the fuck!");
  return NULL;
}


void WorldCoordListDraw(World *world, WorldCoordList *list, U32 start) {

  for (U32 i = start; i < list->len - 1; i++) {
    Vector2 start = Vector2Add(Vector2FromWorldCoord(list->ptr[i]), (Vector2){0.5, 0.5});    
    Vector2 end = Vector2Add(Vector2FromWorldCoord(list->ptr[i + 1]), (Vector2){0.5, 0.5});

    DrawLineEx(start, end, 0.1, WHITE);

  }
}