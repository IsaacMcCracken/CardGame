#include "../card_types.h"

void CardFnSex(World *world, WorldCoord *coord, Entity *selected, Entity *target) {
  TextCopy(selected->name_buffer, "Sex");
}

void CardFnHealthPotion(World *world, WorldCoord *coord, Entity *selected, Entity *target) {
  selected->health += 20;
  if (selected->health > selected->health_cap)
        selected->health = selected->health_cap;
}

// idk i want something that does self inflicting damage for testing
void CardFnArrayOfArrows(World *world, WorldCoord *coord, Entity *selected, Entity *target) {
  if (selected->health <= 20)
      selected->health = 0;
  else
      selected->health -= 20;
}

void CardFnBattleInspiration(World *world, WorldCoord *coord, Entity *selected, Entity *target) {
  selected->action_count += 1;
  CardListPopAppend(world->hand, world->deck, 1);
}