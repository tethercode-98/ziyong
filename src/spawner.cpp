#include "spawner.h"

#include "enemy.h"
#include "world/effect.h"
#include "core/scene.h"

void Spawner::update(float delta_time) {
  exis_ = game_.getEnemyExit();
  if(!target_ || !target_->getActive()) return;
  if(exis_ > max_exis_) return;
  timer_ += delta_time;
  if (timer_ >= interval_) {
    timer_ = 0.0f;
    game_.playSound("assets/sound/silly-ghost-sound-242342.mp3");

    for (int i = 0; i < num_; i++) {
      // spawn enemy
      auto position = game_.randomVec2(game_.getCurrentScene()->getWindowPosition(), game_.getCurrentScene()->getWindowPosition() + game_.getWindowSize());
      Enemy* enemy = Enemy::addEnemyChild(nullptr, position, target_);
      Effect::addEffectChild(game_.getCurrentScene(), "assets/effect/184_3.png" , position, 1.0f , enemy);
    }
    game_.setEnemyExit( exis_ + num_);
  }
}