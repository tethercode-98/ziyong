#include "bg_star.h"
#include "../core/scene.h"
BgStar* BgStar::addBgStarChild(Object* parent, int num, float scale_far,
                               float scale_mid, float scale_near) {
  BgStar * bg_star = new BgStar();
  bg_star->init();
  bg_star->num_ = num;
  bg_star->scale_far_ = scale_far;
  bg_star->scale_mid_ = scale_mid;
  bg_star->scale_near_ = scale_near;
  bg_star->star_far_.reserve(num); //  预先把内存分配好，以免 后续重新分配
  bg_star->star_mid_.reserve(num);  // 预先把内存分配好，以免 后续重新分配
  bg_star->star_near_.reserve(num);  // 预先把内存分配好，以免 后续重新分配
  auto extra = Game::GetInstance().getCurrentScene()->getMapSize() - Game::GetInstance().getWindowSize(); // 获取在视窗外的地图大小，用于生成星星
  for(auto i = 0; i < num; i++) {
    bg_star->star_far_.push_back(Game::GetInstance().randomVec2(glm::vec2(0), Game::GetInstance().getWindowSize() + extra * scale_far ));
    bg_star->star_mid_.push_back(Game::GetInstance().randomVec2(glm::vec2(0), Game::GetInstance().getWindowSize() + extra * scale_mid ));
    bg_star->star_near_.push_back(Game::GetInstance().randomVec2(glm::vec2(0), Game::GetInstance().getWindowSize() + extra * scale_near ));
  }
  if(parent) parent->addChild(bg_star);
  SDL_Log("a");
  return bg_star;
}

void BgStar::update(float delta_time) {
  timer_ += delta_time;
  color_far_ = {0.5f + 0.5f*sinf(timer_*0.9f), 0.5f + 0.5f*sinf(timer_*0.8f), 0.5f + 0.5f*sinf(timer_*0.7f)};
  color_mid_ = {0.5f + 0.5f*sinf(timer_*0.7f), 0.5f + 0.5f*sinf(timer_*0.8f), 0.5f + 0.5f*sinf(timer_*0.9f)};
  color_near_ = {0.5f + 0.5f*sinf(timer_*0.8f), 0.5f + 0.5f*sinf(timer_*0.9f), 0.5f + 0.5f*sinf(timer_*1.0f)};
}

void BgStar::render(){

  auto position = -game_.getCurrentScene()->getWindowPosition();
  game_.drowPoints(star_far_, position * scale_far_,color_far_ );
  game_.drowPoints(star_mid_, position * scale_mid_,color_mid_ );
  game_.drowPoints(star_near_, position * scale_near_,color_near_ );
}