#include "object.h"

void Object::init() {}

bool Object::handleEvents(SDL_Event& event) {

  for(auto& child : children_) {
    if(child->getActive()) {
      if(child->handleEvents(event)) return true;
    }
  }
  return false;
}

void Object::update(float delta_time_) {
  // for(auto& child : children_) {
  //   if(child->getActive()) {
  //     child->update(delta_time_);
  //   }
  // }
  for(auto it = children_.begin(); it != children_.end();) {
    auto child = *it;
    if(child->getNeedRomve()) {
      it = children_.erase(it);
      child->clean();
      delete child;
      child = nullptr;
    } else {
      if(child->getActive()) {
        child->update(delta_time_);
      }
      ++it;
    }
  }

  for(auto& child : object_to_add_) {
    addChild(child);
  }
  object_to_add_.clear();
}

void Object::render() {
  for(auto& child : children_) {
    if(child->getActive()) {
      child->render();
    }
  }
}

void Object::clean() {
  for(auto& child : children_) {
    child->clean();
  }
  children_.clear();
}
