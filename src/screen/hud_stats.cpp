#include "hud_stats.h"
#include "../core/actor.h"
#include "../raw/stats.h"
#include "../affiliate/sprite.h"
HudStats* HudStats::addHudStatsChild(Object* parent, Actor* target,
                                     glm::vec2 render_position) {
  HudStats* hud_stats = new HudStats();
  hud_stats->init();
  hud_stats->setRenderPosition(render_position);
  hud_stats->setTarget(target);
  if(parent) parent->addChild(hud_stats);
  return hud_stats;
}
void HudStats::init() {
  ObjectScreen::init();
  health_bar_bg_ = Sprite::addSpriteAnimChild(this, "assets/UI/bar_bg.png", 3.0f, Anchor::CENTER_LEFT);
  health_bar_bg_ ->setOffset(health_bar_bg_->getOffset() + glm::vec2(30.0, 0));
  health_bar_ = Sprite::addSpriteAnimChild(this, "assets/UI/bar_red.png", 3.0f, Anchor::CENTER_LEFT);
  health_bar_->setOffset(health_bar_->getOffset() + glm::vec2(30.0, 0));
  health_icon_ = Sprite::addSpriteAnimChild(this, "assets/UI/Red Potion.png", 0.5f, Anchor::CENTER_LEFT);

  mana_bar_bg_ = Sprite::addSpriteAnimChild(this, "assets/UI/bar_bg.png", 3.0f, Anchor::CENTER_LEFT);
  mana_bar_bg_->setOffset(mana_bar_bg_->getOffset() + glm::vec2(275.0, 35.0));
  mana_bar_ = Sprite::addSpriteAnimChild(this, "assets/UI/bar_blue.png", 3.0f, Anchor::CENTER_LEFT);
  mana_bar_->setOffset(mana_bar_->getOffset() + glm::vec2(275.0, 35.0));
  mana_icon_ = Sprite::addSpriteAnimChild(this, "assets/UI/Blue Potion.png", 0.5f, Anchor::CENTER_LEFT);
  mana_icon_->setOffset(mana_icon_->getOffset() + glm::vec2(270.0f, 30.0));
}
void HudStats::update(float delta_time) {
  ObjectScreen::update(delta_time);
  updateHealthBar();
  updateManaBar();
}
void  HudStats::updateHealthBar(){
  if(!target_ || !health_bar_ || !target_->getStats()) return;
  health_bar_->setPercentage(glm::vec2(target_->getStats()->getHealth() / target_->getStats()->getMaxHealth(), 1.0f));
};
void  HudStats::updateManaBar(){
  if(!target_ || !mana_bar_ || !target_->getStats()) return;
  mana_bar_->setPercentage(glm::vec2(target_->getStats()->getMana() / target_->getStats()->getMaxMana(), 1.0f));  
};