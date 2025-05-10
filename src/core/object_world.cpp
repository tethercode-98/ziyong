#include "object_world.h"
#include "scene.h"

void ObjectWorld::update(float delta_time) {
  ObjectScreen::update( delta_time );
  render_position_ = game_.getCurrentScene()->mapToScreen(position_);
}

void ObjectWorld::setPosition(const glm::vec2& position) {
  position_ = position;
  render_position_ = game_.getCurrentScene()->mapToScreen(position_);
}

void ObjectWorld::setRenderPosition(const glm::vec2& render_position) {
  render_position_ = render_position;
  position_ = game_.getCurrentScene()->screenToMap(render_position_);
}

