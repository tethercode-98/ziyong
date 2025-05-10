#ifndef STATS_H
#define STATS_H

# include "../core/actor.h"

class Stats : public Object {
  protected:
  Actor * parent_ = nullptr; // 拥有者
  float health_ = 100.0f ; // 生命值
  float max_health_ = 100.0f ; // 最大生命值
  float mana_ = 100.0f ; // 魔力值
  float max_mana_ = 100.0f ; // 最大魔力值
  float damage_ = 40.0f ; // 伤害
  float mana_regen_ = 10.0f ; // 自动恢复value

  float invincible_time_ = 1.5f; // 无敌时间
  float invincible_timer_ = 0.0f; // 无敌时间计时器
  bool is_alive_ = true;
  bool is_invincible_ = false;

  public:
  static Stats*addStatsChild(Actor* parent, float max_health = 100.0f, float max_mana = 100.0f, float damage = 40.0f, float mana_regen = 10.0f);
  virtual void update(float delta_time) override;

  bool canUseMana(float mana_cost);
  void useMana(float mana_cost);
  void regenMana(float delta_time);
  void takeDamage(float damage);

  // getters and setters
  float getHealth() { return health_; }
  float getMaxHealth() { return max_health_; }
  float getMana() { return mana_; }
  float getMaxMana() { return max_mana_; }
  float getDamage() { return damage_; }
  float getManaRegen() { return mana_regen_; }

  bool getisAlive() { return is_alive_; }

  void setHealth(float health) { health_ = health; }
  void setMaxHealth(float max_health) { max_health_ = max_health; }
  void setMana(float mana) { mana_ = mana; }
  void setMaxMana(float max_mana) { max_mana_ = max_mana; }
  void setDamage(float damage) { damage_ = damage; }
  void setManaRegen(float mana_regen) { mana_regen_ = mana_regen; }

  void setAlive(bool alive) { is_alive_ = alive; }

  Actor * getTarget() { return parent_; }
  void setTarget(Actor* target) { parent_ = target; }

  bool getInvincible() const { return is_invincible_; }
};

#endif