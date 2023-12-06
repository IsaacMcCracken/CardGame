#ifndef ENTITY_H
#define ENTITY_H

#include <basetypes.h>
#include "arena.h"

#define ENTITY_NAME_SIZE 64

typedef struct Entity Entity;
struct Entity {
  Entity *next;
  Entity *prev;

  char name_buffer[ENTITY_NAME_SIZE];
  U8 name_len;
  U32 health;
  U32 health_cap;

  


};


#endif // ENTITY_H