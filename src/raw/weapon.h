#ifndef WEAPON_H
#define WEAPON_H

#include "../core/object.h"

class Spell;
class Actor;
class Weapon : public Object {

protected:
  Actor* parent_ = nullptr;
  Spell* spell_ = nullptr;
  float cool_down_ = 1.0f;
  float mana_cost_ = 0.0f;
  float cool_down_timer_ = 0.0f;
public:
  virtual void update(float delta_time) override;

  void attack(glm::vec2 position, Spell* spell);
  bool canAttack() const;
  // getters and setters
  Spell* getSpell() const { return spell_; }
  void setSpell(Spell* spell) { spell_ = spell; }
  float getCoolDown() const { return cool_down_; }
  void setCoolDown(float cool_down) { cool_down_ = cool_down; }
  float getManaCost() const { return mana_cost_; }
  void setManaCost(float mana_cost) { mana_cost_ = mana_cost; }
  float getCoolDownTimer() const { return cool_down_timer_; }
  void setCoolDownTimer(float cool_down_timer) { cool_down_timer_ = cool_down_timer; }
  Actor* getParent() const { return parent_; }
  void setParent(Actor* parent) { parent_ = parent; }
};

#endif