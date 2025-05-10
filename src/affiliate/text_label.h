#ifndef TEXT_LABEL_H
#define TEXT_LABEL_H

#include "../core/object_affiliate.h"
#include <string>

class TextLabel : public ObjectAffiliate {
protected:
  TTF_Text* ttf_text_ = nullptr;
  std::string font_path_;
  int font_size_ = 16; //问了能够 让其接收这种打双引号的文字 需要 const 和 & = const std::string &text
public:
  virtual void clean() override;
  static TextLabel* addTextLabelChild(ObjectScreen *parent, const std::string &text, const std::string &font_path, int font_size, Anchor anchor = Anchor::CENTER);
  // virtual void init() override;
  virtual void render() override;
  // setters and getters
  void setFont(const std::string& font_path, int font_size); // init() 之后需要立刻调用
  void setFontPath(const std::string &font_path);
  std::string getFontPath() const { return font_path_; };

  void setFontSize(int font_size);
  int getFontSize() const { return font_size_; };

  // void setTTFText(TTF_Text* ttf_text){ this->ttf_text = ttf_text; };
  // TTF_Text* getTTFText() const { return ttf_text_; };
  void setTTFText(std::string ttf_text);
  std::string getTTFText() const { return ttf_text_->text; };
private:
  void updateSize(); // 根据文字内容决定所占区块大小// 默认的时一行
};

#endif