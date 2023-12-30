
/*******************************************************************************************
*   EntityEditor v1.0.0 - Tool Description
*
*   MODULE USAGE:
*       #define GUI_ENTITY_EDITOR_IMPLEMENTATION
*       #include "gui_entity_editor.h"
*
*       INIT: GuiEntityEditorState state = InitGuiEntityEditor();
*       DRAW: GuiEntityEditor(&state);
*
*   LICENSE: Propietary License
*
*   Copyright (c) 2022 raylib technologies. All Rights Reserved.
*
*   Unauthorized copying of this file, via any medium is strictly prohibited
*   This project is proprietary and confidential unless the owner allows
*   usage in any other form by expresely written permission.
*
**********************************************************************************************/

#include <raylib.h>
#include <raygui.h>

#include <string.h>     // Required for: strcpy()

#ifndef GUI_ENTITY_EDITOR_H
#define GUI_ENTITY_EDITOR_H

typedef struct {
    // Define anchors
    Vector2 anchor;            // ANCHOR ID:1
    
    // Define controls variables
    bool EntityEditorWindowBoxActive;            // WindowBox: EntityEditorWindowBox
    bool NameTextBoxEditMode;
    char NameTextBoxText[128];            // TextBox: NameTextBox
    bool HealthSpinnerEditMode;
    int HealthSpinnerValue;            // Spinner: HealthSpinner
    bool MovementSpinnerEditMode;
    int MovementSpinnerValue;            // Spinner: MovementSpinner
    int EntityFactionToggleGroupActive;            // ToggleGroup: EntityFactionToggleGroup
    bool PlayableCheckBoxExChecked;            // CheckBoxEx: PlayableCheckBoxEx
    bool EnemyableCheckBoxExChecked;            // CheckBoxEx: EnemyableCheckBoxEx
    bool FlamableCheckBoxExChecked;            // CheckBoxEx: FlamableCheckBoxEx
    bool FreezableCheckBoxExChecked;            // CheckBoxEx: FreezableCheckBoxEx
    bool WetableCheckBoxExChecked;            // CheckBoxEx: WetableCheckBoxEx

    // Custom state variables (depend on development software)
    // NOTE: This variables should be added manually if required

} GuiEntityEditorState;
#ifdef __cplusplus
extern "C" {            // Prevents name mangling of functions
#endif

//----------------------------------------------------------------------------------
// Module Functions Declaration\n\
//----------------------------------------------------------------------------------
GuiEntityEditorState InitGuiEntityEditor(void);
void GuiEntityEditor(GuiEntityEditorState *state);
static void EntitySaveButton();                // Button: EntitySaveButton logic

#ifdef __cplusplus
}
#endif

#endif // GUI_ENTITY_EDITOR_H

/***********************************************************************************
*
*   GUI_ENTITY_EDITOR IMPLEMENTATION
*
************************************************************************************/
#if defined(GUI_ENTITY_EDITOR_IMPLEMENTATION)


GuiEntityEditorState InitGuiEntityEditor(void)
{
    GuiEntityEditorState state = { 0 };

    // Init anchors
    state.anchor = (Vector2){ 0, 0 };            // ANCHOR ID:1
    
    // Initilize controls variables
    state.EntityEditorWindowBoxActive = true;            // WindowBox: EntityEditorWindowBox
    state.NameTextBoxEditMode = false;
    strcpy(state.NameTextBoxText, "Name");            // TextBox: NameTextBox
    state.HealthSpinnerEditMode = false;
    state.HealthSpinnerValue = 0;            // Spinner: HealthSpinner
    state.MovementSpinnerEditMode = false;
    state.MovementSpinnerValue = 0;            // Spinner: MovementSpinner
    state.EntityFactionToggleGroupActive = 0;            // ToggleGroup: EntityFactionToggleGroup
    state.PlayableCheckBoxExChecked = false;            // CheckBoxEx: PlayableCheckBoxEx
    state.EnemyableCheckBoxExChecked = false;            // CheckBoxEx: EnemyableCheckBoxEx
    state.FlamableCheckBoxExChecked = false;            // CheckBoxEx: FlamableCheckBoxEx
    state.FreezableCheckBoxExChecked = false;            // CheckBoxEx: FreezableCheckBoxEx
    state.WetableCheckBoxExChecked = false;            // CheckBoxEx: WetableCheckBoxEx

    // Custom variables initialization

    return state;
}

void GuiEntityEditor(GuiEntityEditorState *state)
{
    // Draw controls
    if (state->EntityEditorWindowBoxActive)
    {
        state->EntityEditorWindowBoxActive = !GuiWindowBox((Rectangle){ state->anchor.x + 0, state->anchor.y + 0, 272, 480 }, "Entity Editor");
        GuiLabel((Rectangle){ state->anchor.x + 8, state->anchor.y + 32, 32, 24 }, "Name");
        if (GuiTextBox((Rectangle){ state->anchor.x + 40, state->anchor.y + 32, 224, 24 }, state->NameTextBoxText, 128, state->NameTextBoxEditMode)) state->NameTextBoxEditMode = !state->NameTextBoxEditMode;
        if (GuiSpinner((Rectangle){ state->anchor.x + 104, state->anchor.y + 64, 160, 24 }, "Health Capacity    ", &state->HealthSpinnerValue, 0, 100, state->HealthSpinnerEditMode)) state->HealthSpinnerEditMode = !state->HealthSpinnerEditMode;
        if (GuiSpinner((Rectangle){ state->anchor.x + 104, state->anchor.y + 96, 160, 24 }, "Movement Capacity", &state->MovementSpinnerValue, 0, 100, state->MovementSpinnerEditMode)) state->MovementSpinnerEditMode = !state->MovementSpinnerEditMode;
        if (GuiButton((Rectangle){ state->anchor.x + 144, state->anchor.y + 448, 120, 24 }, "Save")) EntitySaveButton(); 
        GuiToggleGroup((Rectangle){ state->anchor.x + 16, state->anchor.y + 144, 80, 24 }, "Neutral;Player;Enemy", &state->EntityFactionToggleGroupActive);
        GuiLabel((Rectangle){ state->anchor.x + 96, state->anchor.y + 184, 64, 16 }, "Entity Flags");
        GuiCheckBox((Rectangle){ state->anchor.x + 8, state->anchor.y + 200, 24, 24 }, "Playable", &state->PlayableCheckBoxExChecked);
        GuiLabel((Rectangle){ state->anchor.x + 112, state->anchor.y + 128, 40, 16 }, "Faction");
        GuiCheckBox((Rectangle){ state->anchor.x + 96, state->anchor.y + 200, 24, 24 }, "Enemyable", &state->EnemyableCheckBoxExChecked);
        GuiCheckBox((Rectangle){ state->anchor.x + 184, state->anchor.y + 200, 24, 24 }, "Flamable", &state->FlamableCheckBoxExChecked);
        GuiLine((Rectangle){ state->anchor.x + 8, state->anchor.y + 168, 256, 16 }, NULL);
        GuiCheckBox((Rectangle){ state->anchor.x + 8, state->anchor.y + 232, 24, 24 }, "Freezeable", &state->FreezableCheckBoxExChecked);
        GuiCheckBox((Rectangle){ state->anchor.x + 96, state->anchor.y + 232, 24, 24 }, "Wetable", &state->WetableCheckBoxExChecked);
    }
}

#endif // GUI_ENTITY_EDITOR_IMPLEMENTATION
