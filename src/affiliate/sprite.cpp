#include "sprite.h"

Texture::Texture(const std::string& path) {
  texture = Game::GetInstance().getAsserStore()->getTexture(path);
  SDL_GetTextureSize(texture, &src_rect.w, &src_rect.h);
}

Sprite* Sprite::addSpriteAnimChild(ObjectScreen* parret, const std::string& path, float scalae, Anchor anchor) {
  auto sprite = new Sprite();
  sprite->init();
  sprite->setAnchor(anchor);
  sprite->setTexture(path);
  sprite->setScale(scalae);
  sprite->setParent(parret);
  // sprite->setOffsetByAnchor(anchor);
  parret->addChild(sprite);
  return sprite;

}

void Sprite::render() {
  if(!texture_.texture || !parrent_ || is_finish_) {return;}
 
  auto pos = parrent_->getRenderPosition() + offset_;
  game_.renderTexture(texture_, pos, size_, percentage_); // 解耦
}

void Sprite::setTexture(const Texture& texture) {
  texture_ = texture;
  size_ = glm::vec2(texture.src_rect.w, texture.src_rect.h);
}
