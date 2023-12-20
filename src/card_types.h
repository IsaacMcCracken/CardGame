#ifndef CARD_TYPES_H
#define CARD_TYPES_H

#include "card.h"
#include "world.h"

// World is the world The first entity is your entity and the other is the target
typedef void (*CardFn)(World *, WorldCoord*, Entity *, Entity *);

typedef struct CardData CardData;
struct CardData {
  const char *name;
  const char *description;
  CardCostType cost_type;
  CardFn method;
};

#define MAX_CARD_ARCHETYPES 2
const CardData card_archetypes[MAX_CARD_ARCHETYPES];

#endif