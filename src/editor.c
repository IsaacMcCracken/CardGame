#include "editor.h"

#define GUI_ENTITY_EDITOR_IMPLEMENTATION
#include "gui/gui_entity_editor.h"

// Entity Editor GUI
GuiEntityEditorState entity_editor_state;
Entity *editing_entity = NULL;

void EntityEditorUpdateFrame(World *world) {
  if (IsKeyPressed(KEY_E) && world->grabbing_entity && !entity_editor_state.EntityEditorBoxActive) {
    entity_editor_state = InitGuiEntityEditor();
    TraceLog(LOG_INFO, "bool: %d", entity_editor_state.EntityEditorBoxActive);
    // set screen position;

    for (U32 i = 0; i < sizeof(entity_editor_state.layoutRecs)/sizeof(Rectangle); i++) {
      entity_editor_state.layoutRecs[i].x = GetScreenWidth() - (entity_editor_state.layoutRecs[i].width + 10);
      entity_editor_state.layoutRecs[i].y += 10;

    }
    

    entity_editor_state.layoutRecs[0] = (Rectangle){ GetScreenWidth() - (280 + 10), 10, 280, 584 };
    // Get Variables in there
    editing_entity = world->grabbing_entity;
    entity_editor_state.HealthSpinnerValue = editing_entity->health_cap;
    entity_editor_state.MovementSpinnerValue = editing_entity->movement_cap;
    strcpy(entity_editor_state.EntityNameTextBoxText, editing_entity->name_buffer);
  } 
}

static void EntityEditorSaveButton() {
  editing_entity->health_cap = entity_editor_state.HealthSpinnerValue;
  editing_entity->movement_cap = entity_editor_state.MovementSpinnerValue;
  strcpy(editing_entity->name_buffer, entity_editor_state.EntityNameTextBoxText);
}

void EditorUpdateFrame(
  World *world,
  Arena *perm_arena, 
  Arena *turn_arena, 
  Arena *temp_arena
) {
  Vector2 mouse_pos = GetMousePosition();
  Vector2 mouse_world_pos = GetScreenToWorld2D(mouse_pos, world->camera);
  WorldCoord mouse_world_coord = WorldCoordFromVector2(mouse_world_pos);
  
  EntityEditorUpdateFrame(world);
  if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
      const U32 index = WorldIndexFromVector2(world, mouse_world_pos);
      world->tiles[index] = Tile_wall;
  }

  if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT)) {
      const U32 index = WorldIndexFromVector2(world, mouse_world_pos);
      world->tiles[index] = Tile_void;
    }
}

void EditorDraw(void) {
  DrawText("Editing", 0, 0, 20, WHITE);
  GuiEntityEditor(&entity_editor_state);
}