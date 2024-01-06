#include "card_types.h"


const CardData card_archetypes[MAX_CARD_ARCHETYPES] =  {
  {
    .name = "Battle Inspiration",
    .cost = 0,
    .description = "Target one of your characters to gain another action.",
    .card_type = CardTypes_skill,
  },
  {
    .name = "Health Potion",
    .cost = 1,
    .description = "Give player more health",
    .card_type = CardType_item,
    .heal_self_amount = 10,
    .flags = CardFlags_heal_self,
  },
  {
    .name = "Array of arrows",
    .cost = 2,
    .description = "shoot shott array",
    .card_type = CardType_attack,
  },
  {
    .name = "Melee Attack",
    .cost = 1,
    .range = 1,
    .card_type = CardType_attack,
    .description = "Basic Attack",
    .flags = CardFlags_damage_target,
    .damage_target_amount = 7,
  }
};


void PlayCard(World *world, Entity *target) {
  /*
  CardFlags_heals_self = 1 << 0,
  CardFlags_heals_target = 1 << 1,
  CardFlags_damages_target = 1 << 2,
  CardFlags_damages_self = 1 << 3,
  */
  CardData card_data = card_archetypes[world->grabbing_card->data];

  if (card_data.flags & CardFlags_heal_self) {
    world->grabbing_entity->health += card_data.heal_self_amount;
    if (world->grabbing_entity->health > world->grabbing_entity->health_cap)
      world->grabbing_entity->health = world->grabbing_entity->health_cap;
  }
  if (card_data.flags & CardFlags_heal_target) {
    target->health += card_data.heal_self_amount;
    if (target->health > target->health_cap)
      target->health = target->health_cap;
  }
  if (card_data.flags & CardFlags_damage_self) {
    if (world->grabbing_entity->health < card_data.damage_self_amount)
      world->grabbing_entity->health -= card_data.damage_self_amount;
    else world->grabbing_entity->health = 0;
  }
  if (card_data.flags & CardFlags_damage_target) {
    if (target->health < card_data.damage_self_amount)
      target->health -= card_data.damage_self_amount;
    else target->health = 0;
  }
}