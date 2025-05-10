#ifndef COLLIDER_H
#define COLLIDER_H

#include "../core/object_affiliate.h"

class Spell;

class Collider : public ObjectAffiliate {
protected:
  friend Spell;
  enum class Type {
    CIRCLE,  // size_ 的 x 轴 为半径
    RECTANGLE,
  };
  Type type_ = Type::CIRCLE;

  public:
  virtual void render() override; 

  static Collider* addColliderChild(ObjectScreen* parent,  glm::vec2 size, Type type = Type::CIRCLE, Anchor anchor = Anchor::CENTER);
  bool isColliding(Collider* other);

  // gertters and stetters
  Type getType() const {return type_;};
  void setType(Type type) {type_ = type;};
};
#endif 