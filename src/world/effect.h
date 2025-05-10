#ifndef EFFECT_H
#define EFFECT_H

#include "../core/object_world.h"
#include "../affiliate/sprite_anim.h"
#include <string>

class Effect : public ObjectWorld {
  SpriteAnim* sprite_ = nullptr;
  ObjectWorld* next_object_ = nullptr; // 播放完毕后添加到场景中。

private :
  void checkFinish();

public :
  static Effect* addEffectChild(Object* parent, const std::string& path, glm::vec2 position, float scale = 1.0f, ObjectWorld* next_object = nullptr);
  virtual void update(float delta_time) override;
  // getters and setters
  SpriteAnim* getSprite() { return sprite_; }
  void setSprite(SpriteAnim* sprite) { sprite_ = sprite; }

  ObjectWorld* getNextObject() { return next_object_; }
  void setNextObject(ObjectWorld* next_object) { next_object_ = next_object; }

};

#endif