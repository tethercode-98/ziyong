#include "spell.h"
#include "../core/scene.h"
class Object;

Spell* Spell::addSpellChld(Object* parent, const std::string& path,
                           glm::vec2 position, float damage, float scale, Anchor anchor) {
  auto spell = new Spell();
  spell->init();
  spell->setDamage(damage);
  spell->sprite_ = SpriteAnim::addSpriteAnimChild(spell, path, scale, anchor);
  auto size = spell->sprite_->getSize();
  spell->collider_ = Collider::addColliderChild(spell, size, Collider::Type::CIRCLE, anchor);
  spell->sprite_->setLoop(false);
  spell->setPosition(position);
  if(parent) parent->addChild(spell);
  return spell;
}

void Spell::update(float delta_time) {
  ObjectWorld::update(delta_time);
  if(sprite_->getFinish()) need_romove_ = true;
  attack();
}

void Spell::attack () {
  auto objects = game_.getCurrentScene()->getChildrenWorld();
  for (auto & object : objects) {
    if(object->getType() != ObjectType::ENEMY) continue;
    if(collider_ && object->getCollider() && collider_->isColliding(object->getCollider())) {
      object->takeDamage(damage_);
    }
  }
}