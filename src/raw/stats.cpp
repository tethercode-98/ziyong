#include "stats.h"

Stats* Stats::addStatsChild(Actor* parent, float max_health, float max_mana,
                            float damage, float mana_regen) {
  Stats * stats = new Stats();   
  stats->parent_ = parent;
  stats->max_health_ = max_health;
  stats->health_ = max_health;
  stats->max_mana_ = max_mana;
  stats->mana_ = max_mana;
  stats->damage_ = damage;
  stats->mana_regen_ = mana_regen;
  parent->addChild(stats);
  return stats;
}

void Stats::update(float delta_time) {
  Object::update(delta_time);
  regenMana(delta_time);
  if(is_invincible_) {
    invincible_timer_ += delta_time;
    if (invincible_timer_ > invincible_time_) {
      is_invincible_ = false;
      invincible_timer_ = 0.0f;
    }
  }
}

bool Stats::canUseMana(float mana_cost) { return mana_ >= mana_cost; }

void Stats::useMana(float mana_cost) {
  mana_ -= mana_cost;
  if (mana_ < 0) { mana_ = 0; }
}

void Stats::regenMana(float delta_time) {
  mana_ += mana_regen_ * delta_time;
  if (mana_ > max_mana_) { mana_ = max_mana_ ;}
}

void Stats::takeDamage(float damage) {
  if(is_invincible_) return;
  health_ -= damage;
  if (health_ < 0) { 
    health_ = 0; 
    is_alive_ = false;
  }
  SDL_Log(u8"受击 %f", health_);
  is_invincible_ = true;
  invincible_timer_ = 0.0f;
}
