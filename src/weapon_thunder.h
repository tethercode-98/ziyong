#ifndef WEAPON_THUNDER_H
#define WEAPON_THUNDER_H

#include "raw/weapon.h"
#include "screen/hud_skill.h"
class WeaponThunder : public Weapon {
protected:
  HUDSkill* hud_skill_ = nullptr;
public: 
  virtual void init() override;
  virtual void update(float delta_time) override;
  static WeaponThunder* addWeaponThunderChild (Actor* parent, float cool_down, float mana_cost); 
  virtual bool handleEvents(SDL_Event& event) override;

};


#endif