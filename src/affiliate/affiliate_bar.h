#ifndef AFFILIATE_BAR_H
#define AFFILIATE_BAR_H

#include "../core/object_affiliate.h"

class AffiliateBar : public ObjectAffiliate {

protected:
  float percentage_ = 1.0f;
  SDL_FColor color_high_ = {0, 1, 0, 1}; // green
  SDL_FColor color_mid_ = {1, 0.65, 0, 1}; // 橙色
  SDL_FColor color_low_ = {1, 0, 0, 1}; // head

public:
  static AffiliateBar* addAffiliateBarChild(ObjectScreen* parrent, glm::vec2 size, Anchor anchor = Anchor::CENTER);
  virtual void render() override;

  // getters and setters
  float getParcentage() const { return percentage_; }
  void setParcentage(float parcentage) { percentage_ = parcentage; }

  SDL_FColor getColorHigh() const { return color_high_; }
  void setColorHigh(SDL_FColor color) { color_high_ = color; }

  SDL_FColor getColorMid() const { return color_mid_; }
  void setColorMid(SDL_FColor color) { color_mid_ = color; }

  SDL_FColor getColorLow() const { return color_low_; }
  void setColorLow(SDL_FColor color) { color_low_ = color; }

};

#endif