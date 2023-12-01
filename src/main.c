#include <stdio.h>
#include <raylib.h>
#include "arena.h"
#include "card.h"

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

int main() {
  InitWindow(800, 800, "Card Game");

  Arena *arena = ArenaInit(sizeof(Card)*1000);
  
  CardList *deck = InitDeck(40);

  printf("Unshuffled Deck");
  Card *node = deck->first;
  while (node) {
    const Card *next = node->next;

    printf("\tHealth: %ld\n", node->health);

    node = next;
  }

  CardListShuffle(arena, deck);

  printf("Shuffled Deck");
  node = deck->first;
  while (node) {
    const Card *next = node->next;

    printf("\tHealth: %ld\n", node->health);

    node = next;
  }
  
  
  
  while (!WindowShouldClose()) {
    BeginDrawing();
      ClearBackground(BLACK);

      
    EndDrawing();
  }
  
}