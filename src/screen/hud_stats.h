#ifndef HUD_STATS_H
#define HUD_STATS_H

#include "../core/object_screen.h"
class Sprite;
class Actor;
class HudStats : public ObjectScreen {
protected:
  Actor* target_ = nullptr;
  Sprite* health_bar_ = nullptr;
  Sprite* health_bar_bg_ = nullptr;
  Sprite* health_icon_ = nullptr;
  Sprite* mana_bar_ = nullptr;
  Sprite* mana_bar_bg_ = nullptr;
  Sprite* mana_icon_ = nullptr;

  float health_percentage_ = 1.0f;
  float mana_percentage_ = 1.0f;

  // TODO ：更加细致的设置大小、位置变量

public:
  static HudStats* addHudStatsChild(Object* parent, Actor* target, glm::vec2 render_position);
  virtual void init() override;
  virtual void update(float delta_time) override;
  // getters and setters
  Sprite* getHealthBar() { return health_bar_; }
  Sprite* getHealthBarBg() { return health_bar_bg_; }
  Sprite* getHealthIcon() { return health_icon_; }
  Sprite* getManaBar() { return mana_bar_; }
  Sprite* getManaBarBg() { return mana_bar_bg_; }
  Sprite* getManaIcon() { return mana_icon_; }
  Actor* getTarget() { return target_; }

  void setTarget(Actor* target) { target_ = target; }
  float getHealthPercentage() { return health_percentage_; }
  float getManaPercentage() { return mana_percentage_; }

  void setHealthPercentage(float percentage) { health_percentage_ = percentage; }
  void setManaPercentage(float percentage) { mana_percentage_ = percentage; }

private:
  void updateHealthBar();
  void updateManaBar();
};

#endif