/*
I'm just going to put all the battle related
stuff in here because idk where else
*/

#ifndef BATTLE_H
#define BATTLE_H

#include "entity.h"




typedef TurnData TurnData;
struct TurnData {
  Entity **entities; // player and enemy characters only
  U32 entities_current_index;
  U32 entities_current_len;
  U32 entities_capacity;
};


void EndTurn(Entity *entity);

#endif