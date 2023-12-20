#include "game.h"
#include "agent.h"

#include <raymath.h>

void GamePlayUpdate(  
  World *world,
  Arena *perm_arena, 
  Arena *turn_arena, 
  Arena *temp_arena
) {
  Vector2 mouse_screen_position = GetMousePosition();
  Vector2 mouse_world_position = GetScreenToWorld2D(mouse_screen_position, world->camera);
  WorldCoord mouse_coord = WorldCoordFromVector2(mouse_world_position);

  // Card Grabbing and UI Stuff
  {
    for (EachCardNodeReverse(card, world->hand->last)) {
      if (CheckCollisionPointRec(GetMousePosition(), (Rectangle){
        .x = card->screen_position.x,
        .y = card->screen_position.y,
        .width = 200,
        .height = 300})) {

        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && !world->grabbing_card) {
          world->grabbing_card = CardListRemove(world->hand, card);
          
        } else 
          card->screen_position = Vector2Lerp(
            card->screen_position,
            (Vector2){
              card->screen_position.x,
              GetScreenHeight() - 600},
              GetFrameTime() * 1.0
          );

        break;        
      } 
    }
  }

  // this is garbage will clean up later
  if (IsMouseButtonDown(MOUSE_BUTTON_LEFT) && world->grabbing_card) {
    world->grabbing_card->screen_position = Vector2Add(world->grabbing_card->screen_position, GetMouseDelta());
  } else if (world->grabbing_card) {
    CardListAppend(world->hand, world->grabbing_card);
    world->grabbing_card = NULL;
  } else if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
    Entity *entity_clicked = EntityFindByWorldCoord(world->entities, mouse_coord);
    if (entity_clicked) {
      world->grabbing_entity = entity_clicked;
    } else if (world->grabbing_entity) {
      Entity *e = world->grabbing_entity;
      e->path = WorldCoordListFindPath(world, turn_arena, e->grid_pos, mouse_coord, 0);
    }
  } 

  

  I32 c = GetCharPressed();

  if (c >= '0' && c <= '9') {
    c = c - '0';
    CardListPopAppend(world->hand, world->deck, c);
  }





}

#include <stdio.h>
void EntityUpdatePathPosition(Entity *entity) {
  const F32 speed = 10.0;

  if (entity->path) {
    WorldCoord coord_current_target = entity->path->ptr[entity->path_index];
    Vector2 vector_current_target = Vector2FromWorldCoord(coord_current_target);
    

    Vector2 delta = Vector2Subtract(vector_current_target, entity->visual_pos);
    Vector2 velocity = Vector2Scale(Vector2Normalize(delta), speed * GetFrameTime());
    F32 velocity_sqr = Vector2LengthSqr(velocity);

    TraceLog(LOG_ALL, "dt: %f\n", sqrt(velocity_sqr));
    
    F32 delta_sqr = Vector2LengthSqr(delta);
    while (velocity_sqr > delta_sqr && entity->path_index < entity->path->len) {
      entity->visual_pos = vector_current_target;


      //think about this some
      if (entity->path_index < entity->path->len - 1)
        entity->path_index += 1;
      else break;

      F32 distance_left = sqrtf(velocity_sqr - delta_sqr);

      coord_current_target = entity->path->ptr[entity->path_index];
      vector_current_target = Vector2FromWorldCoord(coord_current_target);

      delta = Vector2Subtract(vector_current_target, entity->visual_pos);
      velocity = Vector2Scale(Vector2Normalize(delta), distance_left);

  

      velocity_sqr = Vector2LengthSqr(velocity);
      delta_sqr = Vector2LengthSqr(delta);
    }
      
    entity->visual_pos = Vector2Add(entity->visual_pos, velocity);
    entity->grid_pos = WorldCoordFromVector2(entity->visual_pos);
    

    // go to next path index
    if (WorldCoordEqual(entity->grid_pos, coord_current_target))
      entity->path_index += 1;

    // stop condition
    if (WorldCoordEqual(entity->grid_pos, coord_current_target) && entity->path_index >= entity->path->len) {
      entity->path = NULL;
      entity->path_index = 0;
    }
  } else {
    Vector2 grid_position = Vector2FromWorldCoord(entity->grid_pos);
    if (!Vector2Equals(entity->visual_pos, grid_position)) {
      Vector2 delta = Vector2Subtract(grid_position, entity->visual_pos);
      Vector2 velocity = Vector2Scale(Vector2Normalize(delta), speed * GetFrameTime());

      if (Vector2LengthSqr(velocity) > Vector2LengthSqr(delta)) 
        velocity = delta;
      
      entity->visual_pos = Vector2Add(entity->visual_pos, velocity);
    }
  }
}

void EntityUpdate(EntityList *list, Arena *perm_arena) {
  for (EachEntity(entity, list->first)) {
    // if the entity has a path we update its position
    EntityUpdatePathPosition(entity);
    
    

  }
}