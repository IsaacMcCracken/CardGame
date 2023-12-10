#include "arena.h"
#include <raylib.h>

#define DefaultCardSize (Vector2){200, 300}

typedef U8 CardCostType;
enum {
  CardCostType_no_cost
  CardCostType_action;
  CardCostType_bonus_action;
  CardCostType_full_action;
}

typedef struct Card Card;
struct Card {
  Card *next;
  Card *prev;
  Vector2 screen_position;
  U16 data;
};



typedef struct CardData CardData;
struct CardData {
  const char *name;
  const char *description;
  CardCostType cost_type;

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
void CardListPopAppend(CardList *destination_list, CardList *source_list, U16 count);
void CardDraw(Card *card);
void CardListHandDraw(CardList *hand);