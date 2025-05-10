#ifndef SCENE_MAIN_H
#define SCENE_MAIN_H
#include "core/scene.h"

class Spawner;
class Player;
class UIMouse;
class HudStats;
class HUDText;
class HUDButton;
class Timer;
class SceneMain : public Scene {


  Player* player_ = nullptr;
  Spawner* spawner_ = nullptr;
  UIMouse* uimouse_ = nullptr;
  HudStats* hudstats_ = nullptr;
  HUDText* hudtext_score_ = nullptr;

  HUDButton* button_pause_ = nullptr;
  HUDButton* button_restart_ = nullptr;
  HUDButton* button_back_ = nullptr;

  Timer* end_timer_ = nullptr;

 public:
  SceneMain() = default;
  virtual ~SceneMain() =
      default;  // 所有的类不在 con struct 和 de struct or 中
                // 做任何事 // 若使用需要对c++有一定的深刻了解

  virtual void init() override;
  virtual bool handleEvents(SDL_Event& event) override;
  virtual void update(float delta_time_) override;
  virtual void render() override;
  virtual void clean() override;

  virtual void saveData(const std::string& file_path) override;

private:
  void renderBackground();
  void updateScore();

  void checkButtonPause();
  void checkButtonRestart();
  void checkButtonBack();
  void checkEndTimer();

  void checkSlowDown(float& delta_time);
};
#endif