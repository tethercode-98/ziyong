#include "enemy.h"
// #include "affiliate/sprite_anim.h"
#include "core/scene.h"
#include "affiliate/collider.h"
#include "raw/stats.h"
#include "affiliate/affiliate_bar.h"
#include "spawner.h"
Enemy* Enemy::addEnemyChild(Object* parent, glm::vec2 position, Player* target) {
  auto enemy = new Enemy();
  enemy->init();
  enemy->setPosition(position);
  enemy->setTarget(target);
  if(parent) parent->addChild(enemy);
  return enemy;
}
void Enemy::init() {
  Actor::init();
  anim_normal_ = SpriteAnim::addSpriteAnimChild(this, "assets/sprite/ghost-Sheet.png", 2.0f);
  anim_hurt_ = SpriteAnim::addSpriteAnimChild(this, "assets/sprite/ghostHurt-Sheet.png", 2.0f);
  anim_die_ = SpriteAnim::addSpriteAnimChild(this, "assets/sprite/ghostDead-Sheet.png", 2.0f);
  anim_hurt_->setActive(false);
  anim_die_->setActive(false);
  anim_die_->setLoop(false);
  current_anim_ = anim_normal_;

  collider_ = Collider::addColliderChild(this, current_anim_->getSize());
  stats_ = Stats::addStatsChild(this);
  auto size = anim_normal_->getSize();
  health_bar_ = AffiliateBar::addAffiliateBarChild(this, glm::vec2(size.x, 10), Anchor::BOTTOM_CENTER);
  health_bar_->setOffset(health_bar_->getOffset() + glm::vec2(0, size.y / 2.0f));
  setType(ObjectType::ENEMY);
  SDL_Log("collider_  = %d",collider_);
}

void Enemy::update(float delta_time) {
  Actor::update(delta_time);
  if(target_ ->getActive()) {
    aimTarget(target_);
    move(delta_time);
    attack();
  }
  checkState();
  remove();
// { // 测试 
//   // timer_ += delta_time;
//   // if(timer_ > 1.0f && timer_ < 2.0f) {
//   //   changeState(State::HURT);
//   // } else if(timer_ > 2.0f && timer_ < 3.0f) {
//   //   changeState(State::DIE);
//   // }
//   // remove();
// }
}
void Enemy::aimTarget(Player* target) {
  if(target == nullptr) return;
  auto direction = target->getPosition() - this->getPosition();
  direction = glm::normalize(direction);
  velocity_ = direction * max_speed_ / 4.0f;
}

void Enemy::checkState() {
  State newState;
  if(stats_->getHealth() <= 0) newState = State::DIE;
  else if(stats_->getHealth() < stats_->getMaxHealth()) newState = State::HURT;
  else newState = State::NORMAL;
  if(newState != current_state_) changeState(newState);
}

void Enemy::changeState(State new_state) {
  current_anim_->setActive(false);
  switch(new_state) {
    case State::NORMAL:
      current_anim_ = anim_normal_;
      current_anim_->setActive(true);
      break;
    case State::HURT:
      current_anim_ = anim_hurt_;
      current_anim_->setActive(true);
      break;
    case State::DIE:
      current_anim_ = anim_die_;
      current_anim_->setActive(true);
      game_.addScore(score_);
      exis_ = game_.getEnemyExit();
      game_.setEnemyExit(exis_ - 1);
      break;
  }
  current_state_ = new_state;
}

void Enemy::remove() {
  if(anim_die_->getFinish()) {
    // game_.getCurrentScene()->removeChild(this);
    // clean();
    // delete this;  // 不安全操作
    // SDL_Log("Enemy removed");
    if(anim_die_->getFinish()){
      need_romove_ = true;
    }
  }
}

void Enemy::attack() {
  if(!collider_ || !target_ || target_->getCollider() == nullptr) return;
  if(collider_->isColliding(target_->getCollider())) {
    // TODO: attack
    if (stats_ && target_->getStats() ) {
      target_->takeDamage(stats_->getDamage());
    }
  }
}
