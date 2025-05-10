#include "scene_title.h"
#include "screen/hud_text.h"
#include <cmath>
#include "screen/hud_button.h"
#include "scene_main.h"
#include "screen/ui_mouse.h"
#include <fstream>

void SceneTitle::init() {
  Scene::init();
  loadData("assets/score.dat");
  SDL_ShowCursor();
  // SDL_HideCursor();
  game_.palyMusic("assets/bgm/Spooky music.mp3");
  auto size = glm::vec2(game_.getWindowSize().x / 2.0f, game_.getWindowSize().y / 3.0f);
  HUDText::addHUDTextChild(this, u8"幽 灵 逃 生", game_.getWindowSize() / 2.0f - glm::vec2(0, 100.0f), size, "assets/font/VonwaonBitmap-16px.ttf", 64);
  auto score_text = u8"最高分：" + std::to_string(game_.getHighScore());
  HUDText::addHUDTextChild(this, score_text, game_.getWindowSize() / 2.0f - glm::vec2(0, -100.0f), glm::vec2(200.0f, 50.0f), "assets/font/VonwaonBitmap-16px.ttf", 32);
  
  button_start_ = HUDButton::addHUDButtonChild(this, game_.getWindowSize() / 2.0f + glm::vec2(-200.0f, 200.0f) ,"assets/UI/A_Start3.png", "assets/UI/A_Start1.png", "assets/UI/A_Start2.png", 2.0f);
  button_credits_ = HUDButton::addHUDButtonChild(this, game_.getWindowSize() / 2.0f + glm::vec2(0.0f, 200.0f) ,"assets/UI/A_Credits3.png", "assets/UI/A_Credits1.png", "assets/UI/A_Credits2.png", 2.0f);
  button_quit_ = HUDButton::addHUDButtonChild(this, game_.getWindowSize() / 2.0f + glm::vec2(200.0f, 200.0f) ,"assets/UI/A_Quit3.png", "assets/UI/A_Quit1.png", "assets/UI/A_Quit2.png", 2.0f);

  auto text = game_.loadTextFile("assets/credits.txt");
  credits_text_ = HUDText::addHUDTextChild(this, text, game_.getWindowSize() / 2.0f, glm::vec2(500.0f, 500.0f), "assets/font/VonwaonBitmap-16px.ttf", 18);
  credits_text_->setBgSizeByText(100.0f);
  credits_text_->setActive(false);

  UIMouse::addUIMouseChild(this, "assets/UI/pointer_c_shaded.png", "assets/UI/pointer_c_shaded.png", 1.0f, Anchor::TOP_LEFT);
}

bool SceneTitle::handleEvents(SDL_Event& event){
  if(credits_text_->getActive())  {
    if(event.type == SDL_EVENT_MOUSE_BUTTON_UP) {
      credits_text_->setActive(false);
      return true;
    }
    // return;
  }
  if(Scene::handleEvents(event))return true;
  return false;
}

void SceneTitle::update(float delta_time){

  color_timer_ += delta_time;
  updateColor();
  if(credits_text_->getActive()) {
    return;
  }
  Scene::update(delta_time);
  checkButtonQuit();
  checkButtonStart();
  checkButtonCredits();
}

void SceneTitle::render(){
  renderBackground();
  Scene::render();
}

void SceneTitle::clean(){
  Scene::clean();
}

void SceneTitle::loadData(const std::string& file_path){
  int score = 0;
  std::ifstream file(file_path, std::ios::binary); // 以二进制形式保存
  if(file.is_open()) {
    file.read(reinterpret_cast<char*>(&score), sizeof(score));
    file.close();
  }
  game_.setHighScore(score);
}

void SceneTitle::renderBackground(){
  game_.drawBorder(glm::vec2(30.0f), game_.getWindowSize() - glm::vec2(30.0f), glm::vec2(0, 10.0f), boundary_color_);
}

void SceneTitle::updateColor() {
  // boundary_color_.r = 0.5f + 0.5f * std::sinf(SDL_GetTicks() / 1000.0f);
  // boundary_color_.g = 0.5f + 0.5f * std::sinf(SDL_GetTicks() / 1000.0f);
  // boundary_color_.b = 0.5f + 0.5f * std::sinf(SDL_GetTicks() / 1000.0f);
  boundary_color_.r = 0.5f + 0.5f * std::sinf(color_timer_ * 0.8);
  boundary_color_.g = 0.5f + 0.5f * std::sinf(color_timer_ * 0.7);
  boundary_color_.b = 0.5f + 0.5f * std::sinf(color_timer_ * 0.6);
}

void SceneTitle::checkButtonQuit() {
  if(button_quit_->getIsTrigger()) {
    game_.quit();
  }
}

void SceneTitle::checkButtonStart() {
  if(button_start_->getIsTrigger()) {
    auto scene = new SceneMain();
    // game_.changeScene(scene);
    game_.safeChangeScene(scene);
  }
}

void SceneTitle::checkButtonCredits() {
  if(button_credits_->getIsTrigger()) {
    // credits_text_->setActive(!credits_text_->getActive());
    credits_text_->setActive(true);
  }
}
