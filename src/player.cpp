#include "player.h"
#include "core/scene.h"
#include "affiliate/sprite_anim.h"
#include "affiliate/collider.h"
#include "raw/stats.h"

#include "affiliate/text_label.h"
#include "raw/timer.h"
void Player::init() {
  Actor::init();
  flash_timer_ = Timer::addTimerChild(this, 0.3f);
  flash_timer_->start();
  max_speed_ = 500.0f;
  // auto sprite_anim = new SpriteAnim();
  // sprite_anim->setTexture(Texture("assets/sprite/ghost-idle.png"));
  // sprite_anim->setScale(2.0f);
  // sprite_anim->setParent(this);
  // addChild(sprite_anim);
  sprite_idle_ = SpriteAnim::addSpriteAnimChild(this ,"assets/sprite/ghost-idle.png", 2.0f);
  sprite_move_ = SpriteAnim::addSpriteAnimChild(this ,"assets/sprite/ghost-move.png", 2.0f);
  sprite_move_->setActive(false);

  collider_ = Collider::addColliderChild(this, sprite_idle_->getSize() / 2.0f);
  stats_ = Stats::addStatsChild(this);
  effect_ = Effect::addEffectChild(nullptr, "assets/effect/1764.png", glm::vec2(0.0f), 2.0f); 
  // effect_ = Effect::addEffectChild(this, "assets/effect/1764.png", glm::vec2(0.0f), 2.0f); // 参考 P16: 23:00
  // removeChild(effect_);// 这里可以解决异常终止

  weapon_thunder_ = WeaponThunder::addWeaponThunderChild(this, 2.0f, 40.0f);
  // 测试 字体
  // TextLabel::addTextLabelChild(this, u8"这是字体", "assets/font/VonwaonBitmap-16px.ttf", 16);

}
bool Player::handleEvents(SDL_Event& event) {
  if(Actor::handleEvents(event)) return true;
  return false;
}

void Player::update(float delta_time_) {
  Actor::update(delta_time_);
  velocity_ *= 0.9f;
  keyboardControl();
  checkState();
  move(delta_time_);
  syncCamera();
  // getisAlive();
  checkIsDead();
}

void Player::render() {
  if(stats_->getInvincible() && flash_timer_ -> getProgerss() < 0.5f) {
    return;
  }
  Actor::render();
  // game_.drawBorder(render_position_, render_position_ + glm::vec2(20.0f), glm::vec2(5.0f), {1.0, 0.0, 0.0, 1.0,});
}
void Player::clean() {
  Actor::clean();
}

void Player::takeDamage(float damage) {
  if(!stats_ || stats_->getInvincible()) return;
  Actor::takeDamage(damage);
  game_.playSound("assets/sound/hit-flesh-02-266309.mp3");
}

void Player::keyboardControl() {
  auto currentKeyStates = SDL_GetKeyboardState(nullptr);

  if (currentKeyStates[SDL_SCANCODE_W]) {
    velocity_.y = -max_speed_;
  }
 if (currentKeyStates[SDL_SCANCODE_S]) {
    velocity_.y = max_speed_;
  }
  if (currentKeyStates[SDL_SCANCODE_A]) {
    velocity_.x = -max_speed_;
  }
  if (currentKeyStates[SDL_SCANCODE_D]) {
    velocity_.x = max_speed_;
  }
}



void Player::syncCamera() {
  game_.getCurrentScene()->setWindowPosition(position_ - game_.getWindowSize() / 2.0f);
}

void Player::checkState() {
  
  if(velocity_.x < 0) {
    sprite_move_->setFilp(true);
    sprite_idle_->setFilp(true);
  } else {
    sprite_move_->setFilp(false);
    sprite_idle_->setFilp(false); 
  }
  bool new_is_moving = (glm::length(velocity_) > 0.1f);
  if(new_is_moving != is_moving_) {
    is_moving_ = new_is_moving;
    changeState(is_moving_);
  }
}

void Player::changeState(bool is_moving) {
  if(is_moving) {
    sprite_idle_->setActive(false);
    sprite_move_->setActive(true);
    sprite_move_->setCueerntFrame(sprite_idle_->getCurrentFrame());
    sprite_move_->setFrameTimer(sprite_idle_->getFrameTimer());
  } else {
    sprite_idle_->setActive(true);
    sprite_move_->setActive(false);
    sprite_idle_->setCueerntFrame(sprite_move_->getCurrentFrame());
    sprite_idle_->setFrameTimer(sprite_move_->getFrameTimer());
  }
}

void Player::checkIsDead() {
  if(!stats_->getisAlive()) {
    game_.getCurrentScene()->safeAddChild(effect_);
    effect_->setPosition(getPosition());
    // setNeedRomve(true);  // 可以后续实例提升那个
    setActive(false);
    game_.playSound("assets/sound/female-scream-02-89290.mp3");
  }
}
