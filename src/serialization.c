#include "serialization.h"
#include "rayutil.h"

#include <string.h>
#include <stdio.h>



// there gonna be a bug in here when you serialize and a entity is deleted 
// it will not save the deleted entity in game play;

// maybe we can rectify with a pop up and we reset the room state to 
// the begining before modifying the level

// returns the number of entities serialized
U32 SerializeEntities(Arena *arena, EntityList *list) {
  U32 count = 0;
  for (EachEntity(entity, list->first)) {
    SerializeEnity *s = ArenaPush(arena, sizeof(SerializeEnity));

    s->faction = entity->faction;
    s->flags = entity->flags;
    s->h_flip = entity->h_flip;
    s->health = entity->health_cap;
    s->movement = entity->movement_cap;
    strcpy(s->name_buffer, entity->name_buffer);
    s->name_len = entity->name_len;

    s->texture = entity->texture;
    
    count += 1;
  }

  return count;
}

void SerializeWorld(Arena *temp_arena, World *world, const char *filename) {
  U32 file_size = 0;

  TempArena pop = TempArenaInit(temp_arena);

  WorldFileHeader *file_header = ArenaPush(temp_arena, sizeof(WorldFileHeader));
  file_size += sizeof(WorldFileHeader);

  file_header->entity_count = SerializeEntities(temp_arena, world->entities);
  file_size += file_header->entity_count * sizeof(SerializeEnity);


  bool file_saved = SaveFileData(filename, file_header, file_size);

  if (!file_saved) {
    TraceLog(LOG_ERROR, "Could not save %s.", filename);
  }

  TempArenaDeinit(pop);
}

void LoadWorld(Arena *perm_arena, World *world, const char *filename) {
  // ArenaReset(perm_arena); // we need to get everthing right here
  U32 bytes_read = 0;
  U8 *file_data = LoadFileDataArena(perm_arena, filename, &bytes_read);

  WorldFileHeader *file_header = (WorldFileHeader*)file_data;
  SerializeEnity *serialized_entities = (SerializeEnity*)(file_data + sizeof(WorldFileHeader));

  for (U32 i = 0; i < file_header->entity_count; i++) {
    TraceLog(LOG_INFO, "ENTITY: [%s]", serialized_entities[i].name_buffer);
  }
  

}