#include "scene_main.h"
#include "player.h"
#include "enemy.h"
#include "world/effect.h"
#include "spawner.h"
#include "screen/ui_mouse.h"
#include "world/spell.h"
#include "screen/hud_stats.h"
#include "screen/hud_text.h"
#include "screen/hud_button.h"
#include "scene_title.h"
#include "raw/timer.h"
#include <fstream>
#include "raw/bg_star.h"

void SceneMain::init() {
  Scene::init();
  SDL_HideCursor();
  game_.palyMusic("assets/bgm/OhMyGhost.ogg");
  map_size_ = game_.getWindowSize() * 3.0f;
  window_position_ = map_size_ / 2.0f - game_.getWindowSize() / 2.0f;
  // window_position_ = map_size_ / 2.0f - window_position_ / 2.0f;

  player_ = new Player();
  player_->init();
  player_->setPosition(map_size_ / 2.0f );
  addChild(player_);
  
  BgStar::addBgStarChild(this, 2000, 0.2f, 0.5f, 0.7f);

  end_timer_ = Timer::addTimerChild(this);

  spawner_ = new Spawner();
  spawner_->init();
  spawner_->setTarget(player_);
  addChild(spawner_);

  button_pause_ = HUDButton::addHUDButtonChild(this, game_.getWindowSize() - glm::vec2(230.0f, 30.0f), "assets/UI/A_Start3.png","assets/UI/A_Start1.png","assets/UI/A_Start2.png");
  button_restart_ = HUDButton::addHUDButtonChild(this, game_.getWindowSize() - glm::vec2(140.0f, 30.0f), "assets/UI/A_Restart3.png","assets/UI/A_Restart1.png","assets/UI/A_Restart2.png");
  button_back_ = HUDButton::addHUDButtonChild(this, game_.getWindowSize() - glm::vec2(50.0f, 30.0f), "assets/UI/A_Back3.png","assets/UI/A_Back1.png","assets/UI/A_Back2.png");

  hudstats_ = HudStats::addHudStatsChild(this, player_, glm::vec2(30.0f) );
  
  hudtext_score_ = HUDText::addHUDTextChild(this, "Score: 0", glm::vec2(game_.getWindowSize().x - 120.0f, 30.0f), glm::vec2(200.0f, 50.0f));
  uimouse_ = UIMouse::addUIMouseChild(this, "assets/UI/29.png", "assets/UI/30.png", 1.0f, Anchor::CENTER);
  // auto enemy = new Enemy();
  // enemy->init();
  // enemy->setTarget(player_);
  // enemy->setPosition(map_size_ / 2.0f + glm::vec2(200.0f));
  
  // // addChild(enemy);
  // Effect::addEffectChild(this, "assets/effect/184_3_.png" ,map_size_ / 2.0f + glm::vec2(200.0f), 1.0f, enemy);
}

bool SceneMain::handleEvents(SDL_Event& event) {
  if(Scene::handleEvents(event)) return true;
  return false;
  // 測試
  // if(event.type == SDL_EVENT_MOUSE_BUTTON_DOWN) {
  //   if(event.button.button == SDL_BUTTON_LEFT){
  //     auto position = game_.getMousePosition() + window_position_;
  //     Spell::addSpellChld(this, "assets/effect/Thunderstrike w blur.png", position, 120.f ,3.0f, Anchor::CENTER);
  //   }
  // }
}

void SceneMain::update(float delta_time_) {
  checkSlowDown(delta_time_);
  Scene::update(delta_time_);
  // window_position_ += glm::vec2(20.0f, 20.0f) * delta_time_;
  // player_->update(delta_time_);
  updateScore();

  checkButtonBack();
  checkButtonPause();
  checkButtonRestart();

  if(player_ &&!player_->getActive()){
    end_timer_->start();
    saveData("assets/score.dat");
  } 
  checkEndTimer();
}

void SceneMain::render() {
  renderBackground();
  Scene::render();
  // player_->render();
}

void SceneMain::clean() {
  Scene::clean();
  // player_->clean();
  // delete player_;

}

void SceneMain::saveData(const std::string& file_path) {
  auto score = game_.getHighScore();
  std::ofstream file(file_path, std::ios::binary); // 以二进制形式保存
  if(file.is_open()) {
    file.write(reinterpret_cast<char*>(&score), sizeof(score));
    file.close();
  }
}

void SceneMain::renderBackground() {
  // 可以优化下
  auto start = - window_position_;
  auto end = map_size_ - window_position_;
  auto gap = glm::vec2(560.0f, 5.0f);
  // auto rgba = ;
  game_.drawGrid(start, end, gap, {0.5, 0.5, 0.5, 1.0});
  game_.drawBorder(start, end, gap, {1.0, 1.0, 1.0, 1.0});
}

void SceneMain::updateScore() {
  hudtext_score_ ->steText("Score: " + std::to_string(game_.getScore()));
}

void SceneMain::checkButtonPause() {
  if(!button_pause_->getIsTrigger()) return;
  saveData("assets/score.dat");
  if(is_pause_) resume();
  else pause();
}

void SceneMain::checkButtonRestart() {
  if (!button_restart_->getIsTrigger()) return;
  saveData("assets/score.dat");
  game_.setScore(0);
  auto scene = new SceneMain();
  game_.safeChangeScene(scene); // 或者 当前场景 先clean（） 再 initial（）
  game_.setEnemyExit(0);
}

void SceneMain::checkButtonBack() {
  if(!button_back_->getIsTrigger()) return;
  saveData("assets/score.dat");
  game_.setScore(0);
  auto scene = new SceneTitle();
  game_.safeChangeScene(scene);
  game_.setEnemyExit(0);
}

void SceneMain::checkEndTimer() {
  if (!end_timer_->timeOut() )return;
  pause();
  button_restart_->setRenderPosition(game_.getWindowSize() / 2.0f - glm::vec2(200.0f, 0.0f));
  button_restart_->setScale(4.0f);
  button_back_->setRenderPosition(game_.getWindowSize() / 2.0f + glm::vec2(200.0f, 0.0f));
  button_back_->setScale(4.0f);
  button_pause_->setActive(false);
  end_timer_->stop();
}

void SceneMain::checkSlowDown(float& delta_time) {
  if(game_.getMouseButton() & SDL_BUTTON_RMASK) {
    delta_time *= 0.1f;
  }
}
