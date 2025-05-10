#ifndef SCENE_TITLE_H
#define SCENE_TITLE_H

#include "core/scene.h"

class HUDButton;
class HUDText;
class SceneTitle : public Scene {

protected:
  SDL_FColor boundary_color_ = {0.5, 0.5, 0.5, 1};
  float color_timer_ = 0 ; // 计时器
  HUDButton* button_start_ = nullptr;
  HUDButton* button_credits_ = nullptr;
  HUDButton* button_quit_ = nullptr;
  HUDText* credits_text_ = nullptr;

public:
  void init() override;
  // void handleEvent(SDL_Event *event) override;
  virtual bool handleEvents(SDL_Event& event) override;
  void update(float delta_time) override;
  void render() override;
  void clean() override;

  virtual void loadData(const std::string& file_path) override;

private:
  void renderBackground();
  void updateColor();
  void checkButtonQuit();
  void checkButtonStart();
  void checkButtonCredits();
};

#endif