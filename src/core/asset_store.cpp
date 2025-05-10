#include "asset_store.h"

void AssetStore::clean() {
  for(auto& [key, texture] : textures_) {
    SDL_DestroyTexture(texture);
  }
  textures_.clear();
  for(auto& [key, font] : fonts_) {
    TTF_CloseFont(font);
  }
  fonts_.clear();
  for(auto& [key, music] : musics_) {
    Mix_FreeMusic(music);
  }
  musics_.clear();
  for(auto& [key, sound] : sounds_) {
    Mix_FreeChunk(sound);
  }
  sounds_.clear();
  
}

void AssetStore::loadTexture(const std::string& path) {
  SDL_Texture* texture = IMG_LoadTexture(renderer_, path.c_str());
  if(texture == nullptr) {
    SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, u8"Failed to load texture(纹理加载失败): %s", path.c_str());
    return;
  }
  // textures_.[path] = texture; // 如果已存在，则会被覆盖
  textures_.emplace(path, texture); // 如果已存在，则不会插入
}
void AssetStore::loadMusic(const std::string& path) {
  Mix_Music* music = Mix_LoadMUS(path.c_str());
  if(music == nullptr) {
    SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, u8"Failed to load music(音乐加载失败): %s", path.c_str());
    return;
  }
  // musics_.[path] = music; // 如果已存在，则会被覆盖
  musics_.emplace(path, music); // 如果已存在，则不会插入
}

void AssetStore::loadSound(const std::string& path) {
  Mix_Chunk* sound = Mix_LoadWAV(path.c_str());
  if(sound == nullptr) {
    SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, u8"Failed to load sound(音效加载失败): %s", path.c_str());
    return;
  }
  // sounds_.[path] = sound; // 如果已存在，则会被覆盖
  sounds_.emplace(path, sound); // 如果已存在，则不会插入
}

void AssetStore::loadFont(const std::string& path, int size) {
  TTF_Font* font = TTF_OpenFont(path.c_str(), size);
  if(font == nullptr) {
    SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, u8"Failed to load font(字体加载失败): %s", path.c_str());
    return;
  }
  // fonts_.[path] = font; // 如果已存在，则会被覆盖
  fonts_.emplace(path + std::to_string(size), font); // 如果已存在，则不会插入
}

SDL_Texture* AssetStore::getTexture(const std::string& path) { 
  auto it = textures_.find(path);
  if(it == textures_.end()) {
    loadTexture(path);
    it = textures_.find(path);
  }
  if(it == textures_.end()) {
    SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, u8"Failed to get texture(纹理读取失败): %s", path.c_str());
    return nullptr; 
  }
  return it->second;
}

Mix_Music* AssetStore::getMusic(const std::string& path) { 
  auto it = musics_.find(path);
  if(it == musics_.end()) {
    loadMusic(path);
    it = musics_.find(path); 
  }
  if(it == musics_.end()) {
    SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, u8"Failed to get music(音乐读取失败): %s", path.c_str());
    return nullptr;
  }
  return it->second;
}

Mix_Chunk* AssetStore::getSound(const std::string& path) { 
  auto it = sounds_.find(path);
  if(it == sounds_.end()) {
    loadSound(path);
    it = sounds_.find(path);
  }
  if(it == sounds_.end()) {
    SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, u8"Failed to get sound(音效读取失败): %s", path.c_str());
    return nullptr;
 }
  return it->second;
}

TTF_Font* AssetStore::getFont(const std::string& path, int size) { 
  auto it = fonts_.find(path + std::to_string(size));
  if(it == fonts_.end()) {
    loadFont(path,size);
    it = fonts_.find(path + std::to_string(size));
  }
  if(it == fonts_.end()) {
    SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, u8"Failed to get font(字体读取失败): %s", path.c_str());
    return nullptr;
  }
  return it->second;
 }
