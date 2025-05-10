#ifndef HUD_TEXT_H
#define HUD_TEXT_H

#include "../core/object_screen.h"
#include "../affiliate/text_label.h"
#include "../affiliate/sprite.h"

class HUDText : public ObjectScreen {
protected:
  TextLabel* text_label_ = nullptr;
  Sprite* sprite_bg_ = nullptr;
  glm::vec2 size_bg_ = glm::vec2(0,0); // 背景图片的大小
public:
  static HUDText* addHUDTextChild(Object* parent, const std::string& text, glm::vec2 render_position,glm::vec2 size, const std::string& font_path = "assets/font/VonwaonBitmap-16px.ttf", int font_size = 24, const std::string& bg_path = "assets/UI/Textfield_01.png", Anchor anchor = Anchor::CENTER);
  void setBgSizeByText(float margin = 10.0f);
  // steters and getters
  void setTextLabel(TextLabel* text_label) { text_label_ = text_label; }
  TextLabel* getTextLabel() { return text_label_; }

  void setSpriteBg(Sprite* sprite_bg) { sprite_bg_ = sprite_bg; }
  Sprite* getSpriteBg() { return sprite_bg_; }

  void steText(const std::string &text) {text_label_->setTTFText(text); }
  std::string getText() const {return text_label_->getTTFText(); }

  void setBackgroud(const std::string & file_path);
  void setSizeBg(const glm::vec2& size_bg);
    

};

#endif