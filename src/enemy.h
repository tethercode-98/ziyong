#ifndef ENEMY_H
#define ENEMY_H

#include "player.h"
#include "affiliate/sprite_anim.h"
// class Palyer;
// class Spawner;
class Enemy : public Actor {

  enum class State {
    NORMAL,
    HURT,
    DIE
  };

  State current_state_ = State::NORMAL; 

  Player* target_ = nullptr;
  SpriteAnim* anim_normal_ = nullptr;
  SpriteAnim* anim_hurt_ = nullptr;
  SpriteAnim* anim_die_ = nullptr;

  SpriteAnim* current_anim_ = nullptr;
  // Spawner * exis_ = new Spawner();
  // float  timer_ = 0; // 测试
  int score_ = 10;
  int exis_ = 0;
public:
  static Enemy* addEnemyChild(Object* parent, glm::vec2 position, Player* target);

  virtual void init() override;
  virtual void update(float delta_time) override;

  void aimTarget(Player* target);

  void checkState();
  void changeState(State new_state);
  void remove();
  void attack();

  Player* getTarget() {return target_;};
  void setTarget(Player* target){ target_ = target; };



};

#endif