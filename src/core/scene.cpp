#include "scene.h"

bool Scene::handleEvents(SDL_Event& event) {
  for(auto & child : children_screen_) {
    if(child->getActive()) {
      if(child->handleEvents(event)) return true;
    }
  }
  if(is_pause_) return false;
  Object::handleEvents(event);
  for (auto& child : children_world_) {
    if(child->getActive()) {
      if(child->handleEvents(event)) return true;
    }
  }
  return false;
}
// 判断容器的active 而不是父级的（当前的）
void Scene::update(float delta_time_) {
  if(!is_pause_) {

    Object::update(delta_time_);
    // for (auto& child : children_world_) {
    //   if(child->getActive()) {
    //     child->update(delta_time_);
    //   }
    // }
    for(auto it = children_world_.begin(); it != children_world_.end();) {
      auto child = *it;
      if(child->getNeedRomve()) {
        it = children_world_.erase(it);
        child->clean();
        delete child;
        child = nullptr;
        SDL_Log(u8"删除了这个地图元素");
      } else {
        if(child->getActive()) {
          child->update(delta_time_);
        }
        ++it;
      }
    }
  }
  // for(auto & child : children_screen_) {
  //   if(child->getActive()) {
  //     child->update(delta_time_);
  //   }
  // }
  for(auto it = children_screen_.begin(); it != children_screen_.end();) {
    auto child = *it;
    if(child->getNeedRomve()) {
      it = children_screen_.erase(it);
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
}

void Scene::render() {
  Object::render();
  for (auto& child : children_world_) {
    if(child->getActive()) {
      child->render();
    }
  }
  for(auto & child : children_screen_) {
    if(child->getActive()) {
      child->render();
    }
  }
}

void Scene::clean() {
  Object::clean();
  for(auto & child : children_screen_) {
    child->clean();
  }
  children_screen_.clear();
  for (auto& child : children_world_) {
    child->clean();
  }
  children_world_.clear();
}

void Scene::addChild(Object* object) {
  switch(object->getType()) {
    case ObjectType::OBJECT_WORLD:
    case ObjectType::ENEMY:
      children_world_.push_back(dynamic_cast<ObjectWorld*>(object));
      break;
    case ObjectType::OBJECT_SCREEN:
      children_screen_.push_back(dynamic_cast<ObjectScreen*>(object));
      break;
      default:
        children_.push_back(object);  
      break;
  }
}

void Scene::removeChild(Object* object) {
  switch(object->getType()) {
    case ObjectType::OBJECT_WORLD:
    case ObjectType::ENEMY:
      children_world_.erase(std::remove(children_world_.begin(), children_world_.end(), dynamic_cast<ObjectWorld*>(object)), children_world_.end());
      break;
    case ObjectType::OBJECT_SCREEN:
      children_screen_.erase(std::remove(children_screen_.begin(), children_screen_.end(), dynamic_cast<ObjectScreen*>(object)), children_screen_.end());
      break;
      default:
        children_.erase(std::remove(children_.begin(), children_.end(), object), children_.end());  
      break;
  }
}

void Scene::pause() {
  is_pause_ = true;
  game_.pauseSound();
  game_.pauseMusic();
}

void Scene::resume() {
  is_pause_ = false;
  game_.resumeSound();
  game_.resumeMusic();
}

void Scene::setWindowPosition(const glm::vec2& window_position) {
  window_position_ = window_position;
  window_position_ = glm::clamp(window_position, glm::vec2(-30.0f), map_size_ - game_.getWindowSize() + glm::vec2(30.0f));
}