#include "hud_text.h"


HUDText* HUDText::addHUDTextChild(Object* parent, const std::string& text, glm::vec2 render_position,
                                  glm::vec2 size, const std::string& font_path,
                                  int font_size, const std::string& bg_path,
                                  Anchor anchor) {
  auto hud_text = new HUDText();
  hud_text->init();
  hud_text->setRenderPosition(render_position);
  hud_text->setSpriteBg(Sprite::addSpriteAnimChild(hud_text, bg_path, 1, anchor));
  hud_text->setSizeBg(size);
  hud_text->setTextLabel(TextLabel::addTextLabelChild(hud_text, text, font_path, font_size, anchor));
  if(parent) {
    parent->addChild(hud_text);
  }
  return hud_text;
}

void HUDText::setBgSizeByText(float margin) {
  auto text_size = text_label_->getSize();
  setSizeBg(text_size + glm::vec2(margin, margin));
}

void HUDText::setBackgroud(const std::string& file_path) {
  if(sprite_bg_) sprite_bg_-> setTexture(file_path);
  else sprite_bg_ = Sprite::addSpriteAnimChild(this, file_path, 1, Anchor::CENTER);
}


void HUDText::setSizeBg(const glm::vec2& size_bg) {
  size_bg_ = size_bg;
  // text_label_->setSize(size_bg);// 错误
  sprite_bg_->setSize(size_bg);
}

