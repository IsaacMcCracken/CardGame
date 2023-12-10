#include <raylib.h>
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

void DrawRectangleBorder(Vector2 position, Vector2 size, Color color) {
  Color darker = ColorBrightness(color, -0.5);
  DrawRectangleV(position, size, color);
  DrawRectangleLinesEx(
    (Rectangle){
      .x = position.x,
      .y = position.y,
      .width = size.x,
      .height = size.y,
    }, 
    0.05, 
    darker
  );
}

void DrawCard(Vector2 positon, Vector2 size, Card *card) {
  Rectangle rect = (Rectangle){
    .width = size.x,
    .height = size.y,
    .x = positon.x,
    .y = positon.y,
  };

  DrawRectangleRec(rect, WHITE);

  DrawText(card->name, positon.x, positon.y, rect.height/10, BLACK);
}

int main() {

  TraceLogLevel(LOG_ALL);
  InitWindow(800, 800, "Card Game");

  Arena *arena = ArenaInit(Megabyte(100));
  Arena *temp_arena = ArenaInit(Megabyte(100));
  
  CardList *deck = CardListInit(arena, 30);
  CardList *hand = CardListInit(arena, 0);


  World world = WorldInit(arena, 20, 20);


  
  while (!WindowShouldClose()) {
    // Update 
    ArenaReset(temp_arena);

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

    EndDrawing();
  }
  
}