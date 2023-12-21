#include "card_types.h"
#include "card_types/card_misc.h"

const CardData card_archetypes[MAX_CARD_ARCHETYPES] =  {
  {
    .name = "Battle Inspiration",
    .cost_type = CardCostType_no_cost,
    .description = "Target one of your characters to gain another action.",
    .method = CardFnBattleInspiration
  },
  {
    .name = "Array of Arrows",
    .cost_type = CardCostType_action,
    .description = "Use a character to target a foe to shoot an many arrows.",
    .method = CardFnArrayOfArrows
  },
  {
    .name = "Health Potion",
    .cost_type = CardCostType_bonus_action,
    .description = "Give player more health",
    .method = CardFnHealthPotion
  }
};