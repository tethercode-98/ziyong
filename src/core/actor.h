#ifndef ACTOR_H
#define ACTOR_H

#include "object_world.h"

class Stats;
class AffiliateBar;
class Actor : public ObjectWorld {
 protected:
  Stats * stats_ = nullptr;  // 状态
  AffiliateBar* health_bar_ = nullptr; // 生命显示条
  glm::vec2 velocity_ = glm::vec2(0, 0);  // 速度
  float max_speed_ = 600.0f;              // 最大速度

 public:
  virtual void update(float delta_time) override;

  void move(float delta_time_);  // 移动 
  virtual void takeDamage(float damage) override;
  // getters and setters
  glm::vec2 getVelocity() const { return velocity_; }
  void setVelocity(const glm::vec2& velocity) { velocity_ = velocity; }
  float getMaxSpeed() const { return max_speed_; }
  void setMaxSpeed(float max_speed) { max_speed_ = max_speed; }
  Stats *getStats() const { return stats_; }
  void setStats(Stats *stats) { stats_ = stats; }
  bool getisAlive() const;
  AffiliateBar* getHelthBar() const { return health_bar_; }
  void setHelthBar(AffiliateBar* helth_bar) { health_bar_ = helth_bar; }

private:
  void updateHealthBar();
};

#endif