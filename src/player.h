#ifndef PLAYER_H
#define PLAYER_H

#include "core/actor.h"
#include "affiliate/sprite_anim.h"
#include "world/effect.h"
#include "weapon_thunder.h"


class Timer;
class Player : public Actor {
  SpriteAnim* sprite_idle_ = nullptr;
  SpriteAnim* sprite_move_ = nullptr;
  Effect* effect_ = nullptr;
  bool is_moving_ = false;
  WeaponThunder* weapon_thunder_ = nullptr;

  Timer* flash_timer_ = nullptr;
 public:
  virtual void init() override;
  virtual bool handleEvents(SDL_Event& event) override;
  virtual void update(float delta_time_) override;
  virtual void render() override;
  virtual void clean() override;

  virtual void takeDamage(float damage) override;

  void keyboardControl();
  void syncCamera();
  void checkState();
  void changeState(bool is_moving);
  void checkIsDead();
};

#endif