#include "entity.h"
#include <string.h>

void EntityListAppend(EntityList *list, Entity *entity) {
  Entity *last = list->last; 
  if (list->last) {
    last->next = entity;
    entity->prev = last;
    list->last = entity;
    list->count += 1;
  } else {
    list->count = 1;
    list->first = entity;
    list->last = entity;
  }
}

Entity *EntityAlloc(Arena *arena, EntityList *list, const char *name) {
  Entity *entity = NULL;

  if (list->free_list) {
    // If we have a free spot we allocate reuse memory
    entity = list->free_list;
    list->free_list = list->free_list->next;  
    memset(entity, 0, sizeof(Entity));
  } else {
    // Otherwise we just allocate new memory from a arena
    entity = ArenaPush(arena, sizeof(entity));
  }
  
  EntityListAppend(list, entity);

  // set up the entity
  entity->name_len = strlen(name);
  strcpy(entity->name_buffer, name);

  return entity;
}

void EntityFree(EntityList *list, Entity *entity) {
  Entity *next = entity->next;
  Entity *prev = entity->prev;

  if (prev && next) {
    next->prev = prev;
    prev->next = next;
  } else if (prev) {
    prev->next = NULL;
    list->last = prev;
  } else if (next) {
    next->prev = NULL;
    list->first = next;
  } else {
    list->last = NULL;
    list->first = NULL;
  }

  list->count -= 1;

  entity->next = list->free_list;
  list->free_list = entity;
}
