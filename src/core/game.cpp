#include "game.h"

#include "../affiliate/sprite.h"
#include "../player.h"
#include "../scene_main.h"
#include "actor.h"
#include "object_screen.h"
#include "object_world.h"
#include "../scene_title.h"
#include <fstream>

void Game::run() {
  while (is_running_) {
    auto start = SDL_GetTicksNS();
    if(next_scene_) {
      changeScene(next_scene_);
      next_scene_ = nullptr;
      // current_scene_->clean();
      // delete current_scene_;
      // current_scene_ = next_scene_;
      // next_scene_ = nullptr;
      // current_scene_->init();
    }
    handleEvents();
    update(delta_time_);
    render();
    auto end = SDL_GetTicksNS();
    auto elapsed = end - start;  // 得到实际帧处理时间。
    if (elapsed < frame_duration_) {
      SDL_DelayNS(frame_duration_ -
                  elapsed);  // 延迟补偿：// 若帧处理快于目标时间，调用
                             // SDL_DelayNS() 等待剩余时间，确保稳定帧率
      delta_time_ = frame_duration_ / 1.0e9;
    } else {
      delta_time_ =
          elapsed /
          1.0e9;  // 自适应时间差： // 处理超时帧时，直接使用实际耗时计算//
                  // delta_time_，避免游戏逻辑滞后。
    }
    // SDL_Log("FPS %f\n", 1.0/delta_time_);
  }
}

void Game::init(std::string title, int width, int height) {
  window_size_ = glm::vec2{width, height};
  // SDL3 初始化 03
  if (!SDL_Init(SDL_INIT_AUDIO | SDL_INIT_VIDEO)) {
    SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, u8"SDL初始化失败 %s\n",
                 SDL_GetError());
  }
  // 不需要进行SDL_image 初始化 03
  // SDL_Mixer 初始化 03
  if (!Mix_Init(MIX_INIT_MP3 | MIX_INIT_OGG) != (MIX_INIT_MP3 | MIX_INIT_OGG)) {
    SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, u8"SDL_Mixer初始化失败 %s\n",
                 SDL_GetError());
  }
  if (!Mix_OpenAudio(0, NULL)) {
    SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, u8"SDL_Mixer打开音频失败 %s\n",
                 SDL_GetError());
  }
  Mix_AllocateChannels(16);             // 分配16个音频通道 03
  Mix_VolumeMusic(MIX_MAX_VOLUME / 5);  // 设置音乐音量 03
  Mix_Volume(-1, MIX_MAX_VOLUME / 5);   // 设置所有音效音量 03
  // SDL3_TTF 初始化 03
  if (!TTF_Init()) {
    SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, u8"SDL_TTF初始化失败 %s\n",
                 SDL_GetError());
  }

  // 创建窗口 与 渲染器 03
  SDL_CreateWindowAndRenderer(title.c_str(), width, height,
                              SDL_WINDOW_RESIZABLE, &window_, &renderer_);
  if (!window_ || !renderer_) {
    SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,
                 u8"SDL_CreateWindowAndRenderer失败 %s\n", SDL_GetError());
  }
  // 设置窗口逻辑分辨率 03
  SDL_SetRenderLogicalPresentation(renderer_, width, height,
                                   SDL_LOGICAL_PRESENTATION_LETTERBOX);

  // 创建文本引擎
  ttf_engine_ =TTF_CreateRendererTextEngine(renderer_);

  // 计算帧持续时间/帧延迟 04
  frame_duration_ = 1.0e9 / FPS_;

  // 创建资源管理器
  asset_store_ = new AssetStore(renderer_);

  // 创建 场景
  current_scene_ = new SceneTitle();
  current_scene_->init();
}

void Game::handleEvents() {
  SDL_Event event;
  while (SDL_PollEvent(&event)) {
    switch (event.type) {
      case SDL_EVENT_QUIT:
        is_running_ = false;
        break;
      default:
        current_scene_->handleEvents(event);
        // break;
    }
  }
}

void Game::update(float delta_Time_) { 
  updateMouse();
  current_scene_->update(delta_time_); 
}

void Game::render() {
  SDL_SetRenderDrawColor(renderer_, 0, 0, 0, 255);
  SDL_RenderClear(renderer_);
  current_scene_->render();
  SDL_RenderPresent(renderer_);
}

void Game::clean() {
  if (current_scene_) {
    current_scene_->clean();
    delete current_scene_;
  }
  // 释放资源管理器
  if (asset_store_) {
    asset_store_->clean();
    delete asset_store_;
  }
  // 释放文本渲染引擎
  if(ttf_engine_) {
    TTF_DestroyRendererTextEngine(ttf_engine_);
  }
  // 释放窗口与渲染器 03
  if (renderer_) {
    SDL_DestroyRenderer(renderer_);
  }
  if (window_) {
    SDL_DestroyWindow(window_);
  }
  // 退出 SDL Mixer
  Mix_CloseAudio();
  Mix_Quit();
  // 释放SDL_TTF 03
  TTF_Quit();
  // 释放SDL 03
  SDL_Quit();
}

void Game::setScore(int score) {
  score_ = score;
  if(score_ > high_score_) high_score_ = score_;
}

void Game::addScore(int score) {
  setScore(score_ + score);
}

void Game::changeScene(Scene* scene) {
  if(current_scene_) {
    current_scene_->clean();
    delete current_scene_; 
  }
  current_scene_ = scene;
  current_scene_->init();
}

void Game::palyMusic(const std::string& music_path, bool loop) {
  // Mix_PlayMusic(music_path.c_str(), loop ? -1 : 0);
  Mix_PlayMusic(asset_store_->getMusic(music_path), loop ? -1 : 0); // -1 代表无限循环
}

void Game::playSound(const std::string& sound_path) {
  Mix_PlayChannel(-1, asset_store_->getSound(sound_path), 0);
}

void Game::stopMusic() {
  Mix_HaltMusic();
}

void Game::stopSound() {
  Mix_HaltChannel(-1);
}

void Game::pauseMusic() {
  Mix_PauseMusic();
}

void Game::pauseSound() {
  Mix_Pause(-1);
}

void Game::resumeMusic() {
  Mix_ResumeMusic();
}

void Game::resumeSound() {
  Mix_Resume(-1);
}

void Game::renderTexture(const Texture& texture, const glm::vec2& position, const glm::vec2& size, const glm::vec2 &mask) {
  SDL_FRect src_rect = {
    texture.src_rect.x, 
    texture.src_rect.y + texture.src_rect.h * (1 - mask.y), 
    texture.src_rect.w * mask.x, 
    texture.src_rect.h * mask.y,
  };
  SDL_FRect dst_rect = {
    position.x, 
    position.y + size.y * (1 - mask.y), 
    size.x * mask.x, 
    size.y * mask.y,
  };
  SDL_RenderTextureRotated(
      renderer_, texture.texture, &src_rect, &dst_rect, texture.angle,
      nullptr, texture.is_flip ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE);
}// 重点

void Game::renderFillCircle(const glm::vec2& position, const glm::vec2& size,
                            float alpha) {
  auto texture = asset_store_->getTexture("assets/UI/circle.png");
  SDL_FRect dst_rect = {position.x, position.y, size.x, size.y};
  SDL_SetTextureAlphaModFloat(texture, alpha);
  SDL_RenderTexture(renderer_, texture, NULL , &dst_rect);
}

void Game::renderHBar(const glm::vec2& position, const glm::vec2& size,
                      float percent, SDL_FColor color) {
  SDL_SetRenderDrawColorFloat(renderer_, color.r, color.g, color.b, color.a);
  SDL_FRect boundry_rect = {
    position.x,
    position.y,
    size.x,
    size.y
  };
  SDL_FRect fill_rect = {
    position.x,
    position.y,
    size.x * percent,
    size.y
  };
  SDL_RenderRect(renderer_, &boundry_rect);
  SDL_RenderFillRect(renderer_, &fill_rect);
  SDL_SetRenderDrawColorFloat(renderer_, 0, 0, 0, 1);
}

TTF_Text* Game::createTTF_Text(const std::string& text,
                               const std::string& font_path, int font_size) {
  auto font = asset_store_->getFont(font_path, font_size);
  auto ttf_text = TTF_CreateText(ttf_engine_, font,text.c_str(), 0);
  return ttf_text;
}

bool Game::isMouseInRect(const glm::vec2& top_left,
                         const glm::vec2& bottom_right) {
  if(mouse_position_.x >= top_left.x && mouse_position_.x <= bottom_right.x && mouse_position_.y >= top_left.y && mouse_position_.y <= bottom_right.y) {
    return true;
  }
  return false;
}

std::string Game::loadTextFile(const std::string& file_path) {
  std::ifstream file(file_path);
  std::string line;
  std::string text;
  while(std::getline(file, line)) {
    text += line + "\n";
  }
  return text;
}

void Game::updateMouse() {
  mouse_button_ = SDL_GetMouseState(&mouse_position_.x, &mouse_position_.y);
  // // 游戏鼠标位置 = 系统鼠标位置 * 缩放比例: 缩放比例 = 逻辑分辨率 / 窗口大小;
  // // 限制比例。不要出现黑边的做法
  // int w, h;
  // SDL_GetWindowSize(window_, &w, &h);
  // mouse_position_ = mouse_position_ * window_size_ / glm::vec2(w, h);

  // 游戏鼠标位置 = (系统鼠标位置-偏移量） * 缩放比例: 缩放比例 = 逻辑分辨率 / 窗口大小;
  SDL_SetWindowAspectRatio(window_, window_size_.x / window_size_.y, window_size_.x / window_size_.y); // 限制比例不出现黑边
  SDL_FRect rect;
  SDL_GetRenderLogicalPresentationRect(renderer_, &rect);
  mouse_position_ = (mouse_position_ - glm::vec2(rect.x, rect.y)) * window_size_ / glm::vec2(rect.w, rect.h);
}

void Game::drawGrid(const glm::vec2& start, const glm::vec2& end,
                    const glm::vec2& step, SDL_FColor fcolor) {
  SDL_SetRenderDrawColorFloat(renderer_, fcolor.r, fcolor.g, fcolor.b,
                              fcolor.a);
  for (float x = start.x; x <= end.x; x += step.x) {
    SDL_RenderLine(renderer_, x, start.y, x, end.y);
  }
  for (float y = start.y; y <= end.y; y += step.x) {
    SDL_RenderLine(renderer_, start.x, y, end.x, y);
  }
  SDL_SetRenderDrawColorFloat(renderer_, 0, 0, 0, 255);
  // for (float x = start.x; x <= end.x; x += step.x) {
  //   for (float y = start.y; y <= end.y; y += step.y)
  //   {
  //     drawLine(glm::vec2(x, y), glm::vec2(x, y +
  //     step.y),
  //              SDL_FColor{255, 255, 255, 255});
  //   };
  // }
}

void Game::drawBorder(const glm::vec2& start, const glm::vec2& end,
                      const glm::vec2& step, SDL_FColor fcolor) {
  SDL_SetRenderDrawColorFloat(renderer_, fcolor.r, fcolor.g, fcolor.b,
                              fcolor.a);
  for (float i = 0; i < step.y; i++) {
    SDL_FRect rect = {
        start.x - i,
        start.y - i,
        end.x - start.x + 2 * i,
        end.y - start.y + 2 * i,
    };
    SDL_RenderRect(renderer_, &rect);
  }
  SDL_SetRenderDrawColorFloat(renderer_, 0, 0, 0, 255);
}

void Game::drowPoints(const std::vector<glm::vec2>& points,
                      glm::vec2 render_position, SDL_FColor fcolor ) {
  SDL_SetRenderDrawColorFloat(renderer_, fcolor.r, fcolor.g, fcolor.b, fcolor.a);
  for (auto point : points) {
    auto x = point.x + render_position.x;
    auto y = point.y + render_position.y;
    SDL_RenderPoint(renderer_, x, y);
  }
  SDL_SetRenderDrawColorFloat(renderer_, 0, 0, 0, 255);
                      }
