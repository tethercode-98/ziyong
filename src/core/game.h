#ifndef GAME_H
#define GAME_H

#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <SDL3_mixer/SDL_mixer.h>
#include <SDL3_ttf/SDL_ttf.h>

#include <glm/glm.hpp>
#include <string>

#include "asset_store.h"
#include <random>

struct Texture;
class Scene;
// 单例 Game 03
class Game {
  // 私有构造 03
  Game() {};
  // 禁止拷贝构造 赋值构造 03
  Game(const Game&) = delete;
  Game& operator=(const Game&) = delete;

  AssetStore* asset_store_ = nullptr;  // 资源管理器 06
  glm::vec2 window_size_ = glm::vec2(0);  // 窗口大小 03

  glm::vec2 mouse_position_ = glm::vec2(0);  // 鼠标位置 18
  SDL_MouseButtonFlags mouse_button_ = 0;  // 鼠标按键 18

  bool is_running_ = true;                // 游戏是否运行 03
  Scene* current_scene_ = nullptr;        // 当前场景 04
  Scene* next_scene_ = nullptr;        // 下一个场景 028

  Uint64 FPS_ = 60;            // 帧率 04
  Uint64 frame_duration_ = 0;  // 预设的每帧目标时长（纳秒） 04
  float delta_time_ = 0.0f;    // 实际一帧帧展示时间 04

  int score_ = 0;
  int high_score_ = 0;

  int enemy_exit_ = 0; // 场景当前 敌人数量

  SDL_Window* window_ = nullptr;      // 窗口 03
  SDL_Renderer* renderer_ = nullptr;  // 渲染器 03
  TTF_TextEngine* ttf_engine_ = nullptr; // 创建字体引擎 024
  std::mt19937 gen_ = std::mt19937(std::random_device{}());

 public:
  // 单例模式 03
  static Game& GetInstance() {
    static Game instance;
    return instance;
  }
  void run();  // 运行Game ,执行Game主循环 03
  void init(std::string title, int width, int height);  // Game 初始化 03
  void handleEvents();                                  // 事件处理 03
  void update(float delta_time_);                       // 更新Game状态 03
  void render();                                        // 渲染Game 03
  void clean();                                         // 清理Game资源 03

  glm::vec2 getWindowSize() const { return window_size_; };  // 获取窗口大小 03
  Scene* getCurrentScene() const { return current_scene_; };  // 获取当前场景 06
  AssetStore* getAsserStore() const { return asset_store_; };  // 获取资源管理器 07
  glm::vec2 getMousePosition() const { return mouse_position_; };  // 获取鼠标位置 18
  SDL_MouseButtonFlags getMouseButton() const { return mouse_button_; };  // 获取鼠标按钮状态 18
  void setScore(int score);  // 设置得分 19
  int getScore() const { return score_; };  // 获取得分 19
  void setHighScore(int high_score) { high_score_ = high_score; };  // 设置最高分 19
  int getHighScore() const { return high_score_; };  // 获取最高分 19
  int getEnemyExit() const { return enemy_exit_; };  // 获取敌人数量 19
  void setEnemyExit(int enemy_exit) { enemy_exit_ = enemy_exit; };  // 设置敌人数量 19

  void addScore(int score);
  void quit(){is_running_ = false;  };
  void safeChangeScene(Scene* scene){next_scene_ = scene;}
  void changeScene(Scene* scene);

  // 音频函数
  void palyMusic(const std::string& music_path, bool loop = true);  // 播放音乐 025
  void playSound(const std::string& sound_path);  // 播放音效 025
  void stopMusic();  // 停止音乐 025
  void stopSound();  // 停止所有音效 025
  void pauseMusic();  // 暂停音乐 025
  void pauseSound();  // 暂停音效 025
  void resumeMusic();  // 恢复音乐 025
  void resumeSound();  // 恢复音效 025


  // 随机数函数
  float randomFloat(float min, float max) { return std::uniform_real_distribution<float>(min, max)(gen_); }  // 生成随机浮点数 17
  int randomInt(int min, int max) { return std::uniform_int_distribution<int>(min, max)(gen_); }  // 生成随机整数 17
  glm::vec2 randomVec2(const glm::vec2& min, const glm::vec2& max) { return glm::vec2(randomFloat(min.x, max.x), randomFloat(min.y, max.y)); }  // 生成随机向量 17
  glm::ivec2 randomIVec2(const glm::vec2& min, const glm::vec2& max) { return glm::ivec2(randomInt(min.x, max.x), randomInt(min.y, max.y)); }  // 生成随机向量 17
  // 渲染函数
  void renderTexture(const Texture& texture, const glm::vec2& position, const glm::vec2& size, const glm::vec2 &mask = glm::vec2(1.0f)); // 绘制纹理 08点 05
  void renderFillCircle(const glm::vec2& position, const glm::vec2& size, float alpha);  // 绘制填充圆  // 测试
  void renderHBar(const glm::vec2& position, const glm::vec2& size, float percent, SDL_FColor color);  // 绘制水平条形图 09
  void drawGrid(const glm::vec2& start, const glm::vec2& end, const glm::vec2& step, SDL_FColor fcolor);  // 绘制网格 05
  void drawBorder(const glm::vec2& start, const glm::vec2& end, const glm::vec2& step, SDL_FColor fcolor); // 绘制边框 05
  void drowPoints(const std::vector<glm::vec2 >& points, glm::vec2 render_position, SDL_FColor fcolor );

  // 文字函数
  TTF_Text* createTTF_Text(const std::string &text, const std::string &font_path, int font_size = 16);

  // 工具 函数
  bool isMouseInRect(const glm::vec2& top_left, const glm::vec2& bottom_right);  // 判断鼠标是否在矩形内 027
  std::string loadTextFile(const std::string& file_path);  // 加载文本文件 028

private:
  void updateMouse();
};
#endif  // GAME_H