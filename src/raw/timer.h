#ifndef TIMER_H
#define TIMER_H

#include "../core/object.h"

class Timer : public Object {     // 创建时 ， 默认为！active (非活动)
protected:
  float timer_ = 0; // 计时器
  float interval_ = 3; // 时间间隔
  bool time_out_ = false;
public:
  static Timer* addTimerChild(Object* parent, float interval = 3.0f);
  virtual void update(float delta_time) override;
  void start() {is_active_ = true;}
  void stop() {is_active_ = false;}
  bool timeOut();

  float getProgerss() {return timer_ / interval_;}

  // setters and getters
  float getInterval() {return interval_;}
  void setInterval(float interval) {interval_ = interval;}
  float getTimer() {return timer_;}
  void setTimer(float timer) {timer_ = timer;}
};

#endif