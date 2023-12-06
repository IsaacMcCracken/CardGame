#include "arena.h"

typedef struct Card Card;
typedef void (*Attack)(Card* card, Card* enemy);
struct Card {
  Card *next;
  Card *prev;
  char name[256];
  char name_len;
  U8 data;
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
