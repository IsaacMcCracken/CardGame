#include "card.h"

#include <string.h>
#include <raylib.h>
#include <raymath.h>

#define EachNode(node) void *__next__ = node; node; node = __next__, __next__ = node->next 



// this function needs lots of testing
void CardListPopAppend(CardList *destination_list, CardList *source_list, U16 count) {

  Card *first = source_list->last;
  Card *last = source_list->last;
  int i = 0;

  while (first && i < count) {

    // I am reset the screen coords to the bottom right 
    // because I dont really know where else to do that
    first->screen_position = (Vector2){
      .x = GetScreenWidth(),
      .y = GetScreenHeight(),
    };

    i += 1;
    if (i < count)
    first = first->prev;
  }



  // TODO what if the card is the first item;
  Card *prev = first->prev;
  prev->next = NULL;
  first->prev = NULL;

  source_list->last = prev;


  if (destination_list->last) {
    Card *previous_last = destination_list->last;
    previous_last->next = first;
    first->prev = previous_last;
  } else {
    destination_list->first = first;
  }
  
  destination_list->last = last;

  destination_list->count += i + 1;
  source_list->count -= i + 1;

}


void CardDraw(Card *card) {
  Rectangle rect = (Rectangle){
    .width  = DefaultCardSize.x,
    .height = DefaultCardSize.y,
    .x  = card->screen_position.x,
    .y = card->screen_position.y,
  };
  DrawRectangleRec(rect, RAYWHITE);
  DrawRectangleLinesEx(rect, 2, BLACK);
  DrawText(TextFormat("Data: %u", card->data), card->screen_position.x + 10, card->screen_position.y + 10, 20, BLACK);
}



void CardListHandDraw(CardList *hand) {
  Card *node = hand->first;
  const I32 count = hand->count;
  const I32 hand_layout_width = (GetScreenWidth())/3;
  const I32 hand_layout_x = GetScreenWidth()/6;

  U32 hand_position = 0;
  // for (EachNode(node)) {
  while (node) {
    CardDraw(node);
    
    node->screen_position = Vector2Lerp(
      node->screen_position,
      (Vector2){hand_layout_x + (hand_layout_width/count) * hand_position, GetScreenHeight() - 200},
      2.0 * GetFrameTime()
    );

    hand_position++;
    node = node->next;
  }
  
};

CardList *CardListInit(Arena *arena, U32 count) {
  char *names[] = {
    "Hungry Boy",
    "Use Weapon",
    "Fucky Wucky",        
    "Piece of shit",
    "Acerola",
    "Anime Girl",
    "Ethan Cum"
  };

  CardList *deck = ArenaPush(arena, sizeof(CardList));
  if (count == 0) {
    memset(deck, 0, sizeof(CardList));
    return deck;
  }

  Card *cards = ArenaPush(arena, sizeof(Card) * count);

  deck->count = count;
  deck->first = &cards[0];
  deck->last = &cards[count - 1];
  for (size_t i = 0; i < count; i++) 
  {
    U32 name_index = GetRandomValue(0, 6);


    cards[i].data = i + 1;
    strcpy(cards[i].name, names[name_index]);
     

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