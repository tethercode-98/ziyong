#ifndef UI_MOUSE_H
#define UI_MOUSE_H

#include "../core/object_screen.h"
#include "../affiliate/sprite.h"

class UIMouse : public ObjectScreen {

protected:
  Sprite* sprite1_ = nullptr;
  Sprite* sprite2_ = nullptr;
  float timer_ = 0;
public:
  static UIMouse* addUIMouseChild(Object* parent, const std::string& path1, const std::string& path2, float scale = 1.0f, Anchor anchor = Anchor::CENTER); 
  virtual void update(float delta_time);
  // setters and getters
  void setSprite1(Sprite* sprite) { sprite1_ = sprite; }
  Sprite* getSprite1() const { return sprite1_; }
  void setSprite2(Sprite* sprite) { sprite2_ = sprite; }
  Sprite* getSprite2() const { return sprite2_; }

};


#endif