#ifndef HUD_BUTTON_H
#define HUD_BUTTON_H

#include "../core/object_screen.h"
#include "../affiliate/sprite.h"

class HUDButton : public ObjectScreen {
protected:
  Sprite* sprite_normal_ = nullptr;  // 通常状态
  Sprite* sprite_hover_ = nullptr;   // 鼠标在上方悬停状态
  Sprite* sprite_press_ = nullptr;   // 鼠标在上方按下状态
  bool is_hover_ = false;  // 是否获得鼠标
  bool is_press_ = false;  // 是否按下鼠标
  bool is_trigger_ = false;  // 是否触发 （鼠标在上方，且松开鼠标）

public:
  // static HUDButton* addHUDButtonChild(ObjectScreen* parent, Sprite* sprite_normal, Sprite* sprite_hover, Sprite* sprite_press);
  static HUDButton* addHUDButtonChild(Object* parent, glm::vec2 render_position, const std::string& sprite_normal_path, const std::string& sprite_hover_path, const std::string& sprite_press_path, float scale = 1.0f, Anchor anchor = Anchor::CENTER);
  virtual bool handleEvents(SDL_Event& event) override;
  virtual void update(float delta_time) override;
  void checkHover();
  void checkState();

  // setters and getters
  // void setSpriteNormal(Sprite* sprite_normal) { sprite_normal_ = sprite_normal; } // 需要检查节点再那
  // void setSpriteHover(Sprite* sprite_hover) { sorite_hover_ = sprite_hover; }
  // void setSpritePress(Sprite* sprite_press) { sprite_press_ = sprite_press; }
  void setHover(bool is_hover) { is_hover_ = is_hover; }
  void setPress(bool is_press) { is_press_ = is_press; }
  void setTrigger(bool is_trigger) { is_trigger_ = is_trigger; }

  Sprite* getSpriteNormal() { return sprite_normal_; }
  Sprite* getSpriteHover() { return sprite_hover_; }
  Sprite* getSpritePress() { return sprite_press_; }
  bool getIsHover() { return is_hover_; }
  bool getIsPress() { return is_press_; }
  // bool getIsTrigger() { return is_trigger_; } // 是否触发 ，触发后重置按钮状态
  bool getIsTrigger(); // 是否触发 ，触发就会重置 is_ttigger_ 状态

  void setScale(float scale);
};

#endif