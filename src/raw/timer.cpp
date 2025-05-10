#include "timer.h"

Timer* Timer::addTimerChild(Object* parent, float interval) { 
  Timer* timer = new Timer();
  timer->setInterval(interval);
  if(parent) parent->addChild(timer);
  timer->setActive(false);
  return timer;
}

void Timer::update(float delta_time) {
  timer_ += delta_time;
  if (timer_ >= interval_) { 
    timer_ = 0;
    time_out_ = true;
  }
}

bool Timer::timeOut() { 
  if(time_out_) {
    time_out_ = false;
    return true;
  }
  return false; 
}
