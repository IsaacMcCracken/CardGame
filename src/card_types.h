#ifndef CARD_TYPES_H
#define CARD_TYPES_H

#include "world.h"

typedef void (*CardFn)(World *, WorldCoord*, Entity *, Entity *);

typedef struct CardData CardData;
struct CardData {
  const char *name;
  const char *description;
  CardCostType cost_type;
  // CardFn method;
};

#define MAX_CARD_ARCHETYPES 2
const CardData card_archetypes[MAX_CARD_ARCHETYPES];

#endif