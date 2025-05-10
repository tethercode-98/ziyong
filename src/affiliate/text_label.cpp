#include "text_label.h"

TextLabel* TextLabel::addTextLabelChild(ObjectScreen* parent, const std::string& text,
                                        const std::string& font_path,
                                        int font_size,Anchor anchor) {                                          
  auto text_label = new TextLabel();
  text_label-> init();
  text_label->setFont(font_path, font_size);
  text_label->setFontSize(font_size);
  text_label->setTTFText(text);
  text_label->setAnchor(anchor);
  text_label->updateSize();
  if(parent){
    parent->addChild(text_label);
    text_label->setParent(parent);
  }
  return text_label;
}

// void TextLabel::init() {
//   ObjectAffiliate::init();
//   // ttf_text_ = TTF_CreateText();,因为需要引擎，也就是渲染函数，但是我们不想从game中获取，所有我们直接再game中去处理
//   // ttf_text_ = game_.createTTF_Text("", font_path_, font_size_);
// }

void TextLabel::render(){
  ObjectAffiliate::render();
  auto position = parrent_->getRenderPosition() + offset_;
  TTF_DrawRendererText(ttf_text_, position.x, position.y);
}

void TextLabel::clean() {
  if(!ttf_text_) return;
  TTF_DestroyText(ttf_text_);
}

void TextLabel::setFont(const std::string& font_path, int font_size) {
  font_path_ = font_path;
  font_size_ = font_size;
  auto font = game_.getAsserStore()->getFont(font_path_, font_size_);
  if(!ttf_text_) ttf_text_ = game_.createTTF_Text("", font_path_, font_size_);
  TTF_SetTextFont(ttf_text_, font);
  updateSize();
}

void TextLabel::setFontPath(const std::string& font_path) {
  font_path_= font_path;
  // 有可能是新 的ttf_font , 所以从AssetStore 里载入，
  // 然后设置TTF_text里的ttf_font
 auto font = game_.getAsserStore()->getFont(font_path_, font_size_); 
 TTF_SetTextFont(ttf_text_, font);
 updateSize();
}

void TextLabel::setFontSize(int font_size) {
  // 每次更新字体时 ，重新 拿一个出来 ，然后用这个拿出来的字体去更新 ttf_text_
  font_size_ = font_size;
  auto font = game_.getAsserStore()->getFont(font_path_, font_size_);
  TTF_SetTextFont(ttf_text_, font);
  updateSize();
}

void TextLabel::setTTFText(std::string ttf_text) {
   TTF_SetTextString(ttf_text_, ttf_text.c_str(), ttf_text.length()); 
   updateSize();
}

void TextLabel::updateSize() {
  int w, h;
  TTF_GetTextSize(ttf_text_, &w, &h);
  setSize(glm::vec2(w, h));
}
