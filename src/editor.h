#ifndef EDITOR_H
#define EDITOR_H

#include "world.h"

void EditorUpdateFrame(
  World *world,
  Arena *perm_arena, 
  Arena *turn_arena, 
  Arena *temp_arena
);
void EditorDraw(void);

#endif