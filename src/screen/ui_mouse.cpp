#include "ui_mouse.h"

UIMouse* UIMouse::addUIMouseChild(Object* parent,
                                  const std::string& path1,
                                  const std::string& path2, float scale,
                                  Anchor anchor) {
  auto uiMouse = new UIMouse();
  uiMouse->init();
  uiMouse->sprite1_ = Sprite::addSpriteAnimChild(uiMouse, path1, scale, anchor);
  uiMouse->sprite2_ = Sprite::addSpriteAnimChild(uiMouse, path2, scale, anchor);
  if(parent) parent->addChild(uiMouse);
  return uiMouse;
}

void UIMouse::update(float delta_time) {
  timer_ += delta_time;
  if (timer_ < 0.3f) {
    sprite1_->setActive(true);
    sprite2_->setActive(false);
  } else if (timer_ < 0.6f) {
    sprite1_->setActive(false);
    sprite2_->setActive(true);
  } else {
    timer_ = 0.0f;
  }
  setRenderPosition(game_.getMousePosition());
}
