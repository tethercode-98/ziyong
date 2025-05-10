#ifndef HUD_SKILL_H
#define HUD_SKILL_H

#include "../core/object_screen.h"

class Sprite;
class HUDSkill : public ObjectScreen {

protected:
  Sprite* icon_ = nullptr;
  float percentage_ = 1.0f;
public:
  static HUDSkill* addHUDSkillChild(Object* parent, const std::string& path, glm::vec2 position, float scale = 1.0f, Anchor anchor = Anchor::CENTER );

  virtual void render() override; // 可以不需要，只是加了个背景板
  
  // virtual void update(float delta_time) override;
  // getters and setters
  void setIcon(Sprite* icon) { icon_ = icon; }
  void setPercentage(float percentage);
  float getPercentage() const { return percentage_; }
  Sprite* getIcon() const { return icon_; }
};

#endif