#include <stdio.h>
#include <raylib.h>
#include "arena.h"
#include "card.h"


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