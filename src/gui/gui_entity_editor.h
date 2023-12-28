/*******************************************************************************************
*
*   EntityEditor v0.01 - Tool Description
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

#include "raylib.h"

#include <raygui.h>
#include <string.h>     // Required for: strcpy()

#ifndef GUI_ENTITY_EDITOR_H
#define GUI_ENTITY_EDITOR_H

typedef struct {
    bool EntityEditorBoxActive;
    bool EntityNameTextBoxEditMode;
    char EntityNameTextBoxText[128];
    bool HealthSpinnerEditMode;
    int HealthSpinnerValue;
    bool MovementSpinnerEditMode;
    int MovementSpinnerValue;

    Rectangle layoutRecs[6];

    // Custom state variables (depend on development software)
    // NOTE: This variables should be added manually if required

} GuiEntityEditorState;

#ifdef __cplusplus
extern "C" {            // Prevents name mangling of functions
#endif

//----------------------------------------------------------------------------------
// Defines and Macros
//----------------------------------------------------------------------------------
//...

//----------------------------------------------------------------------------------
// Types and Structures Definition
//----------------------------------------------------------------------------------
// ...

//----------------------------------------------------------------------------------
// Module Functions Declaration
//----------------------------------------------------------------------------------
GuiEntityEditorState InitGuiEntityEditor(void);
void GuiEntityEditor(GuiEntityEditorState *state);
static void EntityEditorSaveButton();

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

#include "raygui.h"

//----------------------------------------------------------------------------------
// Global Variables Definition
//----------------------------------------------------------------------------------
//...

//----------------------------------------------------------------------------------
// Internal Module Functions Definition
//----------------------------------------------------------------------------------
//...

//----------------------------------------------------------------------------------
// Module Functions Definition
//----------------------------------------------------------------------------------
GuiEntityEditorState InitGuiEntityEditor(void)
{
    GuiEntityEditorState state = { 0 };

    state.EntityEditorBoxActive = true;
    state.EntityNameTextBoxEditMode = false;
    strcpy(state.EntityNameTextBoxText, "Entity Name");
    state.HealthSpinnerEditMode = false;
    state.HealthSpinnerValue = 0;
    state.MovementSpinnerEditMode = false;
    state.MovementSpinnerValue = 0;

    state.layoutRecs[0] = (Rectangle){ 0, 0, 280, 584 };
    state.layoutRecs[1] = (Rectangle){ 8, 32, 32, 24 };
    state.layoutRecs[2] = (Rectangle){ 56, 32, 216, 24 };
    state.layoutRecs[3] = (Rectangle){ 56, 64, 216, 24 };
    state.layoutRecs[4] = (Rectangle){ 56, 96, 216, 24 };
    state.layoutRecs[5] = (Rectangle){ 232, 552, 40, 24 };

    // Custom variables initialization

    return state;
}


void GuiEntityEditor(GuiEntityEditorState *state)
{
    if (state->EntityEditorBoxActive)
    {
        state->EntityEditorBoxActive = !GuiWindowBox(state->layoutRecs[0], "Entity Editor");
        if (GuiTextBox(state->layoutRecs[2], state->EntityNameTextBoxText, 128, state->EntityNameTextBoxEditMode)) state->EntityNameTextBoxEditMode = !state->EntityNameTextBoxEditMode;
        if (GuiSpinner(state->layoutRecs[3], "Health    ", &state->HealthSpinnerValue, 0, 100, state->HealthSpinnerEditMode)) state->HealthSpinnerEditMode = !state->HealthSpinnerEditMode;
        if (GuiSpinner(state->layoutRecs[4], "Movement", &state->MovementSpinnerValue, 0, 100, state->MovementSpinnerEditMode)) state->MovementSpinnerEditMode = !state->MovementSpinnerEditMode;
        if (GuiButton(state->layoutRecs[5], "Save")) EntityEditorSaveButton(); 
    }
    GuiLabel(state->layoutRecs[1], "Name");
}

#endif // GUI_ENTITY_EDITOR_IMPLEMENTATION
