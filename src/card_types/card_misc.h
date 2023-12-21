#include "../card_types.h"

void CardFnSex(World *world, WorldCoord *coord, Entity *selected, Entity *target) {
  TextCopy(selected->name_buffer, "sex");
  selected->name_buffer[0] = 'S';
}