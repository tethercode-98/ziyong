#ifndef OBJECT_WORLD_H
#define OBJECT_WORLD_H

#include "object_screen.h"
#include "../affiliate/collider.h"

class ObjectWorld : public ObjectScreen {
 protected:
  glm::vec2 position_ = glm::vec2(0, 0);  // 世界坐标
  Collider* collider_ = nullptr;

  public:
  virtual void init() override {type_ = ObjectType::OBJECT_WORLD;}
  virtual void update(float delta_time) override;
  // getters and stters
  virtual glm::vec2 getPosition() const override { return position_; };
  void setPosition(const glm::vec2& position);
  virtual void setRenderPosition(const glm::vec2& render_position) override;

  Collider *getCollider() const {return collider_;}
  void setCollider(Collider* collider)  {collider_ = collider;};
};
#endif