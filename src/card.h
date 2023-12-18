/*
  This file is for 
*/
#ifndef CARD_H 
#define CARD_H

#include <raylib.h>
#include "arena.h"

#define DefaultCardSize (Vector2){200, 300}

typedef U8 CardCostType;
enum {
  CardCostType_no_cost = 0,
  CardCostType_action,
  CardCostType_bonus_action,
  CardCostType_full_action,
};

typedef struct Card Card;
struct Card {
  Card *next;
  Card *prev;
  Vector2 screen_position;
  U16 data;
};

// typedef void (*CardFn)(World *, WorldCoord*, Entity *, Entity *);

typedef struct CardData CardData;
struct CardData {
  const char *name;
  const char *description;
  CardCostType cost_type;
  // CardFn method;
};

typedef struct CardList CardList;
struct CardList {
  Card *first;
  Card *last;
  int count;
};

typedef CardList Deck;
typedef CardList Hand;
typedef CardList Discard;

CardList *CardListInit(Arena *arena, U32 count);
void CardListShuffle(Arena *temp_arena, CardList *list);
void CardListPopAppend(CardList *to, CardList *from, U64 count);
void CardDraw(Card *card);
void CardListHandDraw(CardList *hand);
void CardListAppend(CardList *list, Card *card);
Card *CardListRemove(CardList *list, Card* card); 

// Card Macros
#define EachCardNode(it, first) Card *it = (first); it != NULL; it = it->next
#define EachCardNodeReverse(it, last) Card *it = (last); it != NULL; it = it->prev

#endif