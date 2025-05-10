#ifndef SPAWNER_H
#define SPAWNER_H

#include "core/object.h"

class Player;

class Spawner : public Object {
protected:
  int num_ = 15;  // 创建的数量
  int max_exis_ = 60;  // 场内最大数量
  int exis_ = 0;  // 当前数量
  float timer_ = 0.0f; // 计时器
  float interval_ = 3.0f; // 创建的时间间隔
  Player* target_ = nullptr;
public:
    void update(float delta_time);

    // setters and getters 
    void setNum(int num) { num_ = num; };
    int getNum() const { return num_;};
    void setTimer(int timer) { timer_ = timer;};
    int getTimer() const { return timer_;};
    void setInterval(float interval) { interval_ = interval; };
    float getInterval() { return interval_; };
    void setTarget(Player * target) { target_ = target; };
    Player * getTarget() const { return target_; };
    // int getExis() const { return exis_; };
};

#endif