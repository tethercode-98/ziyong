#include "hud_button.h"


HUDButton* HUDButton::addHUDButtonChild(Object* parent, glm::vec2 render_position,
                                        const std::string& sprite_press_path,
                                        const std::string& sprite_normal_path,
                                        const std::string& sprite_hover_path,
                                        float scale, Anchor anchor) {
  auto hud_button = new HUDButton();
  hud_button->init();
  hud_button->setRenderPosition(render_position);
  hud_button->sprite_press_ = Sprite::addSpriteAnimChild(hud_button, sprite_press_path, scale, anchor);
  hud_button->sprite_normal_ = Sprite::addSpriteAnimChild(hud_button, sprite_normal_path, scale, anchor);
  hud_button->sprite_hover_ = Sprite::addSpriteAnimChild(hud_button, sprite_hover_path, scale, anchor);
  hud_button->sprite_hover_->setActive(false);
  hud_button->sprite_press_->setActive(false);
  if(parent) parent->addChild(hud_button);
  return hud_button;
}

bool HUDButton::handleEvents(SDL_Event& event) {
  if((event.type == SDL_EVENT_MOUSE_BUTTON_DOWN)) {
    if(event.button.button == SDL_BUTTON_LEFT) {
      if(is_hover_) {
        is_press_ = true;
        game_.playSound("assets/sound/UI_button08.wav");
        return true;
      }
    }
  } else if (event.type == SDL_EVENT_MOUSE_BUTTON_UP) {
    if(event.button.button == SDL_BUTTON_LEFT) {
      is_press_ = false;
      if(is_hover_) {
        is_trigger_ = true;
        return true;
      }
    }
  }
  return false;
};

void HUDButton::update(float delta_time) {
  checkHover();
  checkState();
}

// 判断 鼠标是否在图片区域之内
void HUDButton::checkHover(){
  bool new_hover_;
  auto position = render_position_ + sprite_normal_->getOffset();
  auto size = sprite_normal_->getSize();
  if(game_.isMouseInRect(position, position + size)) {
    new_hover_ = true;
  } else {
    new_hover_ = false;
  }
  if(new_hover_ != is_hover_) {
    is_hover_ = new_hover_;
    if(is_hover_ && !is_press_) {
      game_.playSound("assets/sound/UI_button12.wav");
      sprite_normal_->setActive(false);
      sprite_hover_->setActive(true);
      sprite_press_->setActive(false);
    }
  }
}



void HUDButton::checkState() {
  if(!is_press_ && !is_hover_) {
    sprite_normal_->setActive(true);
    sprite_hover_->setActive(false);
    sprite_press_->setActive(false);
  } else if (!is_press_ && is_hover_) {
    sprite_normal_->setActive(false);
    sprite_hover_->setActive(true);
    sprite_press_->setActive(false);
  } else if(is_hover_ && is_press_  ) {
    sprite_normal_->setActive(false);
    sprite_hover_->setActive(false);
    sprite_press_->setActive(true);
  }
}

bool HUDButton::getIsTrigger() { 
  if(is_trigger_) {
    is_trigger_ = false;
    return true;
  }
  return false; 
}

void HUDButton::setScale(float scale) {
  sprite_normal_->setScale(scale);
  sprite_hover_->setScale(scale);
  sprite_press_->setScale(scale);
}
