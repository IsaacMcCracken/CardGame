#ifndef CARD_TYPES_H
#define CARD_TYPES_H

#include "world.h"


typedef U16 CardIndex;
enum {
  CardIndex_sex = 1,
  CardIndex_array_of_arrows = 3,
};


typedef U16 CardFlags;
enum {
  CardFlags_heal_self = 1 << 0,
  CardFlags_heal_target = 1 << 1,
  CardFlags_damage_target = 1 << 2,
  CardFlags_damage_self = 1 << 3,
};

typedef U16 CardType;
enum {
  CardType_attack,
  CardType_item,
  CardTypes_kill,
  CardTypes_skill,
};

typedef struct CardData CardData;
struct CardData {
  const char *name;
  const char *description;
  U16 cost;
  U16 range;
  U16 heal_self_amount;
  U16 heal_target_amount;
  U16 damage_self_amount;
  U16 damage_target_amount;
  CardType card_type;
  CardFlags flags;
};

#define MAX_CARD_ARCHETYPES 4
extern const CardData card_archetypes[MAX_CARD_ARCHETYPES];


void PlayCard(World *world, Entity *target);


#endif