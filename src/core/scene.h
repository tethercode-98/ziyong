#ifndef SCENE_H
#define SCENE_H

#include <glm/glm.hpp>
#include <vector>

#include "object.h"
#include "object_world.h"
#include <string>

class Scene : public Object {
protected:
  glm::vec2 window_position_ = glm::vec2(0.0);  // 视窗位置，点
  glm::vec2 map_size_ = glm::vec2(0.0f); // 地图大小 长
  std::vector<ObjectWorld*> children_world_;        //  地图中的物体 
  std::vector<ObjectScreen*> children_screen_;       //  视窗元素
  bool is_pause_ = false; // 是否暂停， 地图元素停止，屏幕元素依旧

 public:
  Scene() = default;
  virtual ~Scene() = default;  // 所有的类不在 con struct 和 de struct or 中//
                               // 做任何事 // 若使用需要对c++有一定的深刻了解

  virtual void init() override {};
  virtual bool handleEvents(SDL_Event& event) override;
  virtual void update(float delta_time_) override;
  virtual void render() override;
  virtual void clean() override;

  virtual void addChild(Object* object) override; 
  virtual void removeChild(Object* object) override; // 只是把容器中的元素移除容器， 并没有delete该对象

  virtual void saveData( const std::string& file_path){};
  virtual void loadData(const std::string& file_path){};

  glm::vec2 mapToScreen(const glm::vec2 & map_position) const { return map_position - window_position_; };
  glm::vec2 screenToMap(const glm::vec2 & screen_position) const { return screen_position + window_position_; };

  void pause();
  void resume();

  // gatters and setters
  glm::vec2 getWindowPosition() const { return window_position_; };
  void setWindowPosition(const glm::vec2 & window_position);
  glm::vec2 getMapSize() const { return map_size_; };
  void setMapSize(const glm::vec2 & map_size) { map_size_ = map_size; };
  std::vector<ObjectScreen*>& getChildrenScreen() { return children_screen_; };
  std::vector<ObjectWorld*>& getChildrenWorld() { return children_world_; };
};
#endif