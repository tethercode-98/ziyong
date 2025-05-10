#include "weapon.h"
#include "../core/actor.h"
#include "stats.h"
#include "../world/spell.h"
#include "../core/scene.h"

void Weapon::update(float delta_time){
  Object::update(delta_time);
  cool_down_timer_ += delta_time;
}

void Weapon::attack(glm::vec2 position, Spell* spell ) {
  if(spell == nullptr) return;
  parent_->getStats()->useMana(mana_cost_);
  cool_down_timer_ = 0.0f;
  spell->setPosition(position);
  game_.getCurrentScene()->safeAddChild(spell);
}

bool Weapon::canAttack() const { 
  if(cool_down_timer_ < cool_down_) return false;
  if(!parent_->getStats()->canUseMana(mana_cost_)) return false;
  return true; 
}
