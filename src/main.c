#include <raylib.h>
#include <raymath.h>
#include "arena.h"
#include "card.h"
#include "world.h"

// Ok I have this idea to combine a card game with a 
// turn based strategy game I think the idea would be 
// kinda interesting

// Supporters would be like spirits that you can call on 
// and items would be physical items that you throw on the grid

// we could have emergent game play like throwing a flamable liquid 
// on the ground then lighting it on fire would cause the whole area to 
// light up

// we could possibly save on art assets by having a paper mario kinda animation 
// thing going on. 

// Rules each player controls three characters 
// == Card Types == 
// Item Cards
// - weapons - each character can hold one weapon at a time

#define CARD_SIZE (Vector2){200, 300}
#define EachCardNode(it, first) Card *it = (first); it != NULL; it = it->next
#define EachCardNodeReverse(it, last) Card *it = (last); it != NULL; it = it->prev

int main() {

  TraceLogLevel(LOG_ALL);
  InitWindow(800, 800, "Card Game");

  Arena *arena = ArenaInit(Megabyte(100));
  Arena *temp_arena = ArenaInit(Megabyte(100));
  
  CardList *deck = CardListInit(arena, 30);
  CardList *hand = CardListInit(arena, 0);


  World world = WorldInit(arena, 20, 20);


  Card *grabbing_card = NULL;
  while (!WindowShouldClose()) {
    // Update 
    ArenaReset(temp_arena);
    
    Vector2 mouse_position = GetMousePosition();
    for (EachCardNodeReverse(card, hand->last)) {
      if (CheckCollisionPointRec(GetMousePosition(), (Rectangle){
        .x = card->screen_position.x,
        .y = card->screen_position.y,
        .width = 200,
        .height = 300})) {

        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && !grabbing_card) {
          grabbing_card = CardListRemove(hand, card);
          
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

    if (IsMouseButtonDown(MOUSE_BUTTON_LEFT) && grabbing_card) {
      grabbing_card->screen_position = Vector2Add(grabbing_card->screen_position, GetMouseDelta());
    } else if (grabbing_card) {
      CardListAppend(hand, grabbing_card);
      grabbing_card = NULL;
    }
    
    // Draw 
    BeginDrawing();
      ClearBackground(BLACK);
      
      int c = GetCharPressed();

      if (c >= '0' && c <= '9') {
        c = c - '0';
        CardListPopAppend(hand, deck, c);
      }

      WorldDraw(&world);
      WorldUpdateFrame(&world, temp_arena);
      CardListHandDraw(hand);
      if (grabbing_card) {
        CardDraw(grabbing_card);
        Vector2 card_world_postion = GetScreenToWorld2D(grabbing_card->screen_position, world.camera);
        Vector2 card_target_vector = Vector2Subtract(card_world_postion, Vector2One());

        WorldCoord card_target_coord = WorldCoordFromVector2(card_target_vector);
        BeginMode2D(world.camera);
          Rectangle card_target_rect = (Rectangle){
            .x = card_target_coord.x,
            .y = card_target_coord.y,
            .width = 1,
            .height = 1,
          };
          DrawLineEx(card_world_postion, Vector2FromWorldCoord(card_target_coord), 0.05, RED);
          DrawRectangleLinesEx(card_target_rect, 0.1, RED);
        EndMode2D();
      }

    EndDrawing();
  }
  
}