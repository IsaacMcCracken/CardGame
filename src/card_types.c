#include "card_types.h"
#include "card_types/card_misc.h"

#include "card_types/card_misc.h"
const CardData card_archetypes[MAX_CARD_ARCHETYPES] =  {
  {
    .name = "Battle Inspiration",
    .cost_type = CardCostType_no_cost,
    .description = "Target one of your characters to gain another action.",
  },
  {
    .name = "Sex",
    .cost_type = CardCostType_action,
    .description = "character is sex",
    .method = CardFnSex,
  },
  {
    .name = "Health Potion",
    .cost_type = CardCostType_bonus_action,
    .description = "Give player more health",
    .method = CardFnHealthPotion
  }
};