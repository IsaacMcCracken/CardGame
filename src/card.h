#include "arena.h"

typedef struct Card Card;
typedef void (*Attack)(Card* card, Card* enemy);
struct Card {
  Card *next;
  Card *prev;
  char name[256];
  char nameLen;
  int health;
  int healthCapacity;
  int attackDamage[4];
  Attack attacks[4];
  int attackCount;
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

void DrawHand(Hand hand);
void DrawBattle(CardList list);
Deck *InitDeck(int num);
void CardListShuffle(Arena *temp_arena, CardList *list);
