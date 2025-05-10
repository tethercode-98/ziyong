#include "effect.h"
#include "../core/scene.h"

Effect* Effect::addEffectChild(Object* parent, const std::string& path,
                               glm::vec2 position, float scale,
                               ObjectWorld* next_object) {
  auto effect = new Effect();
  effect->init();
  effect->sprite_ = SpriteAnim::addSpriteAnimChild(effect, path, scale);
  effect->sprite_->setLoop(false);
  effect->setPosition(position);
  effect->setNextObject(next_object);
  if(parent) parent->addChild(effect); // 注意咯
  return effect;
}

void Effect::update(float delta_time) {
  ObjectWorld::update(delta_time);
  checkFinish();
}

void Effect::checkFinish() {
  if (sprite_->getFinish()) {
    // TODO
    need_romove_ = true;
    if (next_object_) {
      game_.getCurrentScene()->safeAddChild(next_object_);
    }
  }
}
