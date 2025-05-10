#ifndef OBJECT_SCENE_H
#define OBJECT_SCENE_H

#include "object.h"

class ObjectScreen : public Object {
protected:
  glm::vec2 render_position_ = glm::vec2(0, 0); // 渲染(屏幕)位置
public:
  virtual void init() override {type_ = ObjectType::OBJECT_SCREEN;}
  // getters and stters
  glm::vec2 getRenderPosition() const { return render_position_; };
  virtual void setRenderPosition(const glm::vec2& render_position) { render_position_ = render_position;};
  virtual glm::vec2 getPosition() const {return glm::vec2(0);};
  virtual void takeDamage(float damage) {return ;};
};

#endif