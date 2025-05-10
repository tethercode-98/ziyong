#include "hud_skill.h"
#include "../affiliate/sprite.h"

HUDSkill* HUDSkill::addHUDSkillChild(Object* parent, const std::string& path,
                                glm::vec2 position, float scale,
                                Anchor anchor) {
  auto hud_skill = new HUDSkill();
  hud_skill->init();
  hud_skill->icon_ = Sprite::addSpriteAnimChild(hud_skill, path, scale, anchor);
  hud_skill->setRenderPosition(position);
  if(parent) parent->addChild(hud_skill);
  return hud_skill;
}

void HUDSkill::render() {
  SDL_SetTextureColorModFloat(icon_->getTexture().texture, 0.3f, 0.3f, 0.3f);
  auto position = getRenderPosition() + icon_->getOffset();
  auto size = icon_->getSize();
  game_.renderTexture(icon_->getTexture(), position, size);
  SDL_SetTextureColorModFloat(icon_->getTexture().texture,1.0f,1.0f,1.0f);
  ObjectScreen::render();
}

void HUDSkill::setPercentage(float percentage) {
  percentage = glm::clamp(percentage, 0.0f, 1.0f);
  percentage_ = percentage;
  if(icon_) {
    icon_->setPercentage(glm::vec2(1.0f, percentage)); 
  }
}
