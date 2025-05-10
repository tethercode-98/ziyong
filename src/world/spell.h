#ifndef SPELL_H
#define SPELL_H

#include "../core/object_world.h"
#include "../affiliate/sprite_anim.h"

class Spell : public ObjectWorld {
protected:
  SpriteAnim* sprite_ = nullptr;
  float damage_ = 60.0f;
public:
  static Spell* addSpellChld(Object* parent, const std::string& path, glm::vec2 position, float damage, float scale = 1.0f, Anchor anchor = Anchor::CENTER);
  void update(float delta_time) override;
  void setSpriteAnim(SpriteAnim* sprite) {sprite_ = sprite;}

  // getters and setters
  float getDamage() const {return damage_;}
  void setDamage(float damage) {damage_ = damage;}
  SpriteAnim* getSpriteAnim() const {return sprite_;}
  
private:
  void attack();
};
#endif