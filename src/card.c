#include "card.h"
#include "arena.h"
#include <raylib.h>

CardList CardListPopToOther(CardList *dest, CardList* src, int count) {
  dest->count += count;
  src->count -= count;

  Card *card = src->last;
  int i = 0;
  while (card && i < count) {
    
    card = card->prev;
  }
}

Deck *InitDeck(Arena *arena, int count) {
  Deck *deck = ArenaPush(arena, sizeof(CardList));
  Card *cards = ArenaPush(arena, sizeof(Card) * count);

  deck->count = count;
  deck->first = &cards[0];
  deck->last = &cards[count - 1];
  for (size_t i = 0; i < count; i++) 
  {
    cards[i].health = i + 1;

    if (i > 0)
      cards[i].prev = &cards[i - 1];
    if (i < count - 1)
      cards[i].next =  &cards[i + 1];
  } 

  return deck;
}

// This function takes a 
void CardListShuffle(Arena *temp_arena, CardList *list) {
  TempArena temp = TempArenaInit(temp_arena);
  Card **card_p_list = ArenaPushNoZero(temp_arena, sizeof(Card*) * list->count); 
  
  // We put all the pointers in a temporary list
  Card *node = list->first;
  for (size_t i = 0; i < list->count; i++) {
    Card *next = node->next;

    card_p_list[i] = node;

    node = next;
  }

  // Shuffle all the pointers
  for (size_t i = 0; i < list->count; i++) {
    int index = GetRandomValue(0, list->count - 1);

    Card *swap = card_p_list[index];

    card_p_list[index] = card_p_list[i];
    card_p_list[i] = swap;

  }

  // Use Array Ordering to update links
  Card *first = card_p_list[0];
  Card *last = card_p_list[list->count - 1];
  for (size_t i = 0; i < list->count; i++) {   
    node = card_p_list[i];

    if (i > 0)
      node->prev = card_p_list[i - 1];
    else
      node->prev = NULL;
    
    if (i < list->count - 1)
      node->next = card_p_list[i + 1];
    else 
      node->next = NULL;

  }


  list->first = first;
  list->last = last;
  
  
  
  

  TempArenaDeinit(temp);
} 