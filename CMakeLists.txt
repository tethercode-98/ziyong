# 标题
cmake_minimum_required(VERSION 3.10.0)
project(SDLShooter VERSION 0.1.0 LANGUAGES C CXX)

# 设置C++标准
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# 设置编译选项
if (MSVC)
    add_compile_options(/W4)
else()
    add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# 设置编译输出目录
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_SOURCE_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_SOURCE_DIR})

set(TARGET ${PROJECT_NAME}-${CMAKE_SYSTEM_NAME})

# 查找并载入Cmake预设
find_package(SDL3 REQUIRED)
find_package(SDL3_image REQUIRED)
find_package(SDL3_mixer REQUIRED)
find_package(SDL3_ttf REQUIRED)
find_package(glm REQUIRED)
# 添加可执行文件
add_executable(${TARGET} 
                src/main.cpp
                src/core/game.cpp
                src/scene_main.cpp
                src/core/object_world.cpp
                src/player.cpp
                src/core/scene.cpp
                src/core/asset_store.cpp
                src/core/object.cpp
                src/core/object_affiliate.cpp
                src/affiliate/sprite.cpp
                src/affiliate/sprite_anim.cpp
                src/enemy.cpp
                src/core/actor.cpp
                src/affiliate/collider.cpp
                src/raw/stats.cpp
                src/world/effect.cpp
                src/spawner.cpp
                src/screen/ui_mouse.cpp
                src/world/spell.cpp
                src/raw/weapon.cpp
                src/weapon_thunder.cpp
                src/affiliate/affiliate_bar.cpp
                src/screen/hud_stats.cpp
                src/screen/hud_skill.cpp
                src/affiliate/text_label.cpp
                src/screen/hud_text.cpp
                src/scene_title.cpp
                src/screen/hud_button.cpp
                src/raw/timer.cpp
                src/raw/bg_star.cpp
                )

# 链接库
target_link_libraries(${TARGET}
                        ${SDL3_LIBRARIES}
                        SDL3_image::SDL3_image
                        SDL3_mixer::SDL3_mixer
                        SDL3_ttf::SDL3_ttf
                        glm::glm
                        )