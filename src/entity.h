#ifndef ENTITY_H
#define ENTITY_H

#include <basetypes.h>
#include "arena.h"

typedef struct Entity Entity;
struct Entity {
  Entity *next;
  Entity *prev;

  U32 health;
  U32 health_cap;


};


#endif // ENTITY_H