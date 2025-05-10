#include "actor.h"
#include "scene.h"
#include "../raw/stats.h"
#include "../affiliate/affiliate_bar.h"


void Actor::update(float delta_time) {
  ObjectWorld::update(delta_time);
  updateHealthBar();
}

void Actor::move(float delta_time_) {
  // position_ += velocity_ * delta_time_;
  setPosition(position_ + velocity_ * delta_time_);
  position_ = glm::clamp(position_, glm::vec2(0.0f), game_.getCurrentScene()->getMapSize());

}

void Actor::takeDamage(float damage) {
  if(!stats_) return;
  stats_->takeDamage(damage);
}

bool Actor::getisAlive() const { 
  if (!stats_) return true;
  return stats_->getisAlive(); }

void Actor::updateHealthBar() {
  if(!stats_ || !health_bar_) return;
  health_bar_ -> setParcentage(stats_->getHealth() / stats_->getMaxHealth());
}

