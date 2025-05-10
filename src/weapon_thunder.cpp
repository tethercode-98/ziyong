#include "weapon_thunder.h"
#include "world/spell.h"
#include "core/scene.h"
#include "core/actor.h"

WeaponThunder* WeaponThunder::addWeaponThunderChild(Actor* parent, float cool_down,
                                             float mana_cost) {
  auto weapon = new WeaponThunder();
  weapon->init();
  weapon->setParent(parent);
  weapon->setCoolDown(cool_down);
  weapon->setManaCost(mana_cost);
  parent->addChild(weapon);
  return weapon;
}

void  WeaponThunder::init() {
  Weapon::init();
  auto scene = game_.getCurrentScene();
  auto position = glm::vec2(game_.getWindowSize().x - 300.0f, 30.0f);
  hud_skill_ = HUDSkill::addHUDSkillChild(scene, "assets/UI/Electric-Icon.png", position, 0.1f, Anchor::CENTER);
}

void WeaponThunder::update(float delta_time){
  Weapon::update(delta_time);
  if(hud_skill_) hud_skill_->setPercentage(cool_down_timer_ / cool_down_);
}


bool WeaponThunder::handleEvents(SDL_Event& event) {
  if(event.type == SDL_EVENT_MOUSE_BUTTON_DOWN){
    if(event.button.button == SDL_BUTTON_LEFT){
        if (canAttack()) {
          game_.playSound("assets/sound/big-thunder.mp3");
          auto position = game_.getMousePosition() + game_.getCurrentScene()->getWindowPosition();
          auto spell = Spell::addSpellChld(nullptr, "assets/effect/Thunderstrike w blur.png", position, 40.f, 3.0f, Anchor::CENTER);
          attack(position, spell);
          return true;
        }
      }
  }
  return false;
}