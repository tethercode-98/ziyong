#include "sprite_anim.h"

SpriteAnim* SpriteAnim::addSpriteAnimChild(ObjectScreen* parret, const std::string& path, float scalae, Anchor anchor) {
  auto sprite_anim = new SpriteAnim();
  sprite_anim->init();
  sprite_anim->setAnchor(anchor);
  sprite_anim->setTexture(Texture(path));
  sprite_anim->setScale(scalae);
  sprite_anim->setParent(parret); 
  // sprite_anim->setOffsetByAnchor(anchor);
  parret->addChild(sprite_anim);
  return sprite_anim;
}

void SpriteAnim::update(float delta_time) {
  if (is_finish_) {return;};
  frame_timer_ += delta_time;
  if (frame_timer_ >= 1.0 / fps_) {
    current_frame_++;
    if (current_frame_ >= frame_count_) {
      current_frame_ = 0;
      if(!is_loop_) is_finish_ = true; //
    }
    frame_timer_ = 0.0f;
  }
  texture_.src_rect.x = current_frame_ * texture_.src_rect.w;
}

void SpriteAnim::setTexture(const Texture& texture) {
  texture_ = texture;
  frame_count_ = texture_.src_rect.w / texture_.src_rect.h;
  texture_.src_rect.w = texture_.src_rect.h;
  size_ = glm::vec2(texture_.src_rect.w, texture_.src_rect.h);
}
