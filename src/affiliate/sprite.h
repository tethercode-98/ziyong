#ifndef SPRITE_H
#define SPRITE_H

#include "../core/object_affiliate.h"
#include <string>

struct Texture {
  SDL_Texture* texture = nullptr;
  SDL_FRect src_rect = {0, 0, 0, 0};
  float angle = 0; // 翻转角度
  bool is_flip = false; // 是否翻转
  Texture() = default;
  Texture(const std::string& path);
};

class Sprite : public ObjectAffiliate {
protected:
  Texture texture_;
  bool is_finish_ = false; // 是否播放完毕
  bool need_remove = false; // 是否需要移除
  glm::vec2 percentage_ = glm::vec2(1.0f); // 决定图片原始区域百分比
public:
  // Sprite() = default;
  static Sprite* addSpriteAnimChild(ObjectScreen* parret, const std::string& path, float scalae = 1.0f, Anchor anchor = Anchor::CENTER);
  virtual void render() override;



  // getters and setters
  Texture getTexture() const { return texture_; };
  virtual void setTexture(const Texture &texture);
  bool getFilp() const { return texture_.is_flip; };
  float getAngle() const { return texture_.angle; };
  bool getFinish() const { return is_finish_; };
  void setFilp(bool is_flip) { texture_.is_flip = is_flip; };
  void setAngle(float angle) { texture_.angle = angle; };
  void setFinish(bool is_finish) { is_finish_ = is_finish; };
  void setPercentage(glm::vec2 percentage) { percentage_ = percentage; };
  glm::vec2 getPercentage() const { return percentage_; };
};

#endif