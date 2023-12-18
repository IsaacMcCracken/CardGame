#include "world.h"
#include "agent.h"
#include <raymath.h>
// Coordinate Type Conversion Functions 
Vector2 Vector2FromWorldIndex(World *world, U32 index) {
  return (Vector2){
    .x = index % world->width,
    .y = index / world->width,
  };
}

Vector2 Vector2FromWorldCoord(WorldCoord coord) {
  return (Vector2) {
    .x = (F32)coord.x,
    .y = (F32)coord.y,
  };
}

WorldCoord WorldCoordFromVector2(Vector2 v) {
  return (WorldCoord){v.x, v.y};
}

WorldCoord WorldCoordFromIndex(World *world, U32 index) {
  return (WorldCoord){
    .x = index % world->width,
    .y = index / world->width,
  };
}

U32 WorldIndexFromVector2(World *world, Vector2 v) {
  return (U32)v.x + (U32)v.y * world->width;
}

U32 WorldIndexFromWorldCoord(World *world, WorldCoord coord) {
  return coord.x + coord.y * world->width;
}

U8 WorldCoordEqual(WorldCoord a, WorldCoord b) {
  return a.x == b.x && a.y == b.y;
}


World WorldInit(Arena *arena, U32 width, U32 height) {
  return (World) {
    .width = width,
    .height = height,
    .tiles = ArenaPush(arena, sizeof(Tile) * width * height),
    .camera = (Camera2D) {
      .zoom = 2 * width,
    },
    .entities = ArenaPush(arena, sizeof(EntityList)),
    .hand = CardListInit(arena, 0),
    .discard = CardListInit(arena, 0),
    .deck = CardListInit(arena, 30),
  };
}

void WorldLoad(World *world, Arena* arena, const char *filepath) {
  // TODO: implement this function
}

void WorldSave(World *world, const char *filepath) {
  // TODO: implement this function
}

void WorldDraw(World *world) {
  BeginMode2D(world->camera);
  {
    for (U32 i = 0; i < world->width * world->height; i++) {
      Vector2 tile_pos = Vector2FromWorldIndex(world, i);

      Color color;

      switch (world->tiles[i]) {
        case Tile_wall: color = DARKGRAY; break;
        default: color = BLACK; break;
      }

      DrawRectangleV(tile_pos, (Vector2){1,1}, color);
    }
    


    for (EachEntity(entity, world->entities->first)) {
      if (entity->path) 
        WorldCoordListDraw(world, entity->path, entity->path_index);

      Rectangle entity_rect = (Rectangle) {
        .height = 1,
        .width = 1,
        .x = entity->visual_pos.x,
        .y = entity->visual_pos.y,
      };
      DrawRectangleRec(entity_rect, SKYBLUE);
      if (entity == world->grabbing_entity) {
        DrawRectangleLinesEx(entity_rect, 0.05, GREEN );
      }
    }

    if (world->grabbing_card) {
      Vector2 card_world_postion = GetScreenToWorld2D(world->grabbing_card->screen_position, world->camera);
      Vector2 card_target_vector = Vector2Subtract(card_world_postion, Vector2One());

      WorldCoord card_target_coord = WorldCoordFromVector2(card_target_vector);
        Rectangle card_target_rect = (Rectangle){
          .x = card_target_coord.x,
          .y = card_target_coord.y,
          .width = 1,
          .height = 1,
        };
        DrawRectangleLinesEx(card_target_rect, 0.1, RED);

        DrawLineEx(
          card_world_postion, 
          Vector2FromWorldCoord(WorldCoordFromVector2(card_world_postion)), 
          0.07, 
          RED
        );
    }
  }
  EndMode2D();

  CardListHandDraw(world->hand);
  if (world->grabbing_card)
    CardDraw(world->grabbing_card);
}




void WorldUpdateFrame(
  World *world,
  Arena *perm_arena, 
  Arena *turn_arena, 
  Arena *temp_arena
) {
  // TODO: implement this function
  Vector2 mouse_pos = GetMousePosition();
  Vector2 mouse_world_pos = GetScreenToWorld2D(mouse_pos, world->camera);
  WorldCoord mouse_world_coord = WorldCoordFromVector2(mouse_world_pos);

  if (world->mode == WorldMode_edit) {
    if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
      const U32 index = WorldIndexFromVector2(world, mouse_world_pos);
      world->tiles[index] = Tile_wall;
    }

    if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT)) {
      const U32 index = WorldIndexFromVector2(world, mouse_world_pos);
      world->tiles[index] = Tile_void;
    }
  }






  if (world->mode == WorldMode_game) {
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

    // this is garbage will clean up later
    if (IsMouseButtonDown(MOUSE_BUTTON_LEFT) && world->grabbing_card) {
      world->grabbing_card->screen_position = Vector2Add(world->grabbing_card->screen_position, GetMouseDelta());
    } else if (world->grabbing_card) {
      CardListAppend(world->hand, world->grabbing_card);
      world->grabbing_card = NULL;
    } else if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
      Entity *entity_clicked = EntityFindByWorldCoord(world->entities, mouse_world_coord);

      if (entity_clicked) {
        world->grabbing_entity = entity_clicked;
      } else if (world->grabbing_entity) {
        Entity *e = world->grabbing_entity;
        
        e->path = WorldCoordListFindPath(world, turn_arena, e->grid_pos, mouse_world_coord, 0);
        e->path_index = 0;
      }
    } 

    

    I32 c = GetCharPressed();

    if (c >= '0' && c <= '9') {
      c = c - '0';
      CardListPopAppend(world->hand, world->deck, c);
    }


  }

  for (EachEntity(entity, world->entities->first)) {
    if (entity->path) {
      WorldCoord path_target_coord = entity->path->ptr[entity->path_index];
      Vector2 path_target_vector = Vector2FromWorldCoord(path_target_coord);
      Vector2 path_target_direction = 
        Vector2Scale(Vector2Normalize(Vector2Subtract(path_target_vector, entity->visual_pos)), 0.01);

      entity->visual_pos = Vector2Add(entity->visual_pos, path_target_direction);
      
      entity->grid_pos = WorldCoordFromVector2(entity->visual_pos);

      if (WorldCoordEqual(entity->grid_pos, path_target_coord) 
        && entity->path_index < entity->path->len) 
        entity->path_index += 1; 


    }
  }
  
}

void WorldUpdateWorld(World *world) {
  // TODO: implement this function
}
