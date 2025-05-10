#ifndef BG_STAR_H
#define BG_STAR_H

#include "../core/object.h"

class BgStar : public Object {
protected:
  std::vector<glm::vec2> star_far_; // 远
  std::vector<glm::vec2> star_mid_; // 中
  std::vector<glm::vec2> star_near_; // 近
  float scale_far_ = 0.2f; // 远 比例系数
  float scale_mid_ = 0.5f; // 中 比例系数
  float scale_near_ = 0.7f; // 近 比例系数
  SDL_FColor color_far_ = {0, 0, 0, 1}; // 远 颜色
  SDL_FColor color_mid_ = {0, 0, 0, 1}; // 中 颜色
  SDL_FColor color_near_ = {0, 0, 0, 1}; // 近 颜色
  float timer_ = 0; // 计时器
  int num_ = 2000;              // 每一层星星的数量 (远、中、近)简单
public:
  static BgStar* addBgStarChild(Object* parent, int num, float scale_far, float scale_mid, float scale_near);
  virtual void update(float delta_time) override;
  virtual void render() override;
  // setters and getters 
  void setScaleFar(float scale_far) { scale_far_ = scale_far; }
  void setScaleMid(float scale_mid) { scale_mid_ = scale_mid; }
  void setScaleNear(float scale_near) { scale_near_ = scale_near; }
  void setColorFar(SDL_FColor color_far) { color_far_ = color_far; }
  void setColorMid(SDL_FColor color_mid) { color_mid_ = color_mid; }
  void setColorNear(SDL_FColor color_near) { color_near_ = color_near; }
  void setNum(int num) { num_ = num; }
  float getScaleFar() { return scale_far_; }
  float getScaleMid() { return scale_mid_; }
  float getScaleNear() { return scale_near_; }
  SDL_FColor getColorFar() { return color_far_; }
  SDL_FColor getColorMid() { return color_mid_; }
  SDL_FColor getColorNear() { return color_near_; }
  int getNum() { return num_; }

};

#endif