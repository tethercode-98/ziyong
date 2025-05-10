#ifndef SPRITE_ANIM_H
#define SPRITE_ANIM_H

#include "sprite.h"

class SpriteAnim : public Sprite {
  int current_frame_ = 0; // 当前帧
  int frame_count_ = 0; // 总帧数
  int fps_ = 10; // 帧率
  float frame_timer_ = 0.0f; // 帧计时器
  bool is_loop_ = true; // 是否循环播放
public:
  // SpriteAnim() = default;
  // SpriteAnim(const SpriteAnim&) = delete;
  // SpriteAnim& operator=(const SpriteAnim&) = delete;
  // SpriteAnim(SpriteAnim&&) = delete;
  // SpriteAnim& operator=(SpriteAnim&&) = delete;
  // ~SpriteAnim() = default;
  static SpriteAnim* addSpriteAnimChild(ObjectScreen* parret, const std::string& path, float scalae = 1.0f, Anchor anchor = Anchor::CENTER);
  virtual void update(float delta_time) override;
  // getters and setters
  virtual void setTexture(const Texture &texture) override;

  int getCurrentFrame() const { return current_frame_; };
  int getFrameCount() const { return frame_count_; };
  int getFps() const { return fps_; };
  float getFrameTimer() const { return frame_timer_; };
  bool getLoop() const { return is_loop_; };
  void setCueerntFrame(int current_frame) { current_frame_ = current_frame; };
  void setFrameCount(int frame_count) { frame_count_ = frame_count; };
  void setFps(int fps) { fps_ = fps; };
  void setFrameTimer(float frame_timer) { frame_timer_ = frame_timer; };
  void setLoop(bool is_loop) { is_loop_ = is_loop; };
};
#endif