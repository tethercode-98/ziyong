#ifndef OBJECT_H
#define OBJECT_H

#include "game.h"
#include <vector>
#include "defs.h"
class Object {
protected:
  ObjectType type_ = ObjectType::NONE;
  Game& game_ = Game::GetInstance();
  std::vector<Object*> object_to_add_;
  std::vector<Object*> children_;
  bool is_active_ = true;
  bool need_romove_ = false;
public:
  Object() = default;
  virtual ~Object() = default; // 所有的类不在 con struct 和 de struct or 中 做任何事 // 若使用需要对c++有一定的深刻了解

  virtual void init(); // = 0
  virtual bool handleEvents(SDL_Event& event); // = 0 // 处理事件： 事件如果被处理，则返回真，否则继续向下传递（每次传递的时候检查是否已经被处理）
  virtual void update(float delta_time_); // = 0
  virtual void render(); // = 0
  virtual void clean(); // = 0

  virtual void addChild(Object* child) { children_.push_back(child); }
  //erase(begin(), end());,删除就是删除不加任何，单一职责
  //remove(begin(), end(), value);将相同的value 移至末尾，并返回（迭代器）离末尾最远的那一个的地址 // 单一职责
  virtual void removeChild(Object* child) { children_.erase(std::remove(children_.begin(), children_.end(), child), children_.end()); }
  void safeAddChild(Object* child) { object_to_add_.push_back(child); }

  // getters and setters
  ObjectType getType() { return type_; }
  bool getActive() const {return is_active_;}
  bool getNeedRomve() const {return need_romove_;}
  void setType(ObjectType type) { type_ = type; }
  void setActive(bool active) { is_active_ = active; }
  void setNeedRomve(bool need_romove) { need_romove_ = need_romove; }
};
#endif