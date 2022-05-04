cmake_minimum_required(VERSION 3.22)
project(TPOHB)

set(CMAKE_CXX_STANDARD 17)

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

add_executable(${PROJECT_NAME}
        src/main.cpp
        src/Window.cpp
        src/Texture.cpp
        src/GameState.cpp
        src/Game.cpp
        src/Application.cpp
        src/Map.cpp

        src/entity/Entity.cpp
        src/entity/Player.cpp
        src/FPSController.cpp
        src/entity/Grass.cpp
        src/entity/Tree.cpp
        src/entity/Bricks.cpp
        src/entity/Inventory.cpp src/entity/Inventory.h src/entity/Sword.h src/entity/Sword.cpp src/entity/Axe.cpp src/entity/Axe.h src/entity/Weapon.h src/entity/Weapon.cpp src/entity/Weapon.fwd.h src/entity/Hearth.h src/entity/Stats.cpp src/entity/Stats.h src/SDL_Helper.cpp src/SDL_Helper.h src/entity/AnimatedEntity.cpp src/entity/AnimatedEntity.h src/MapFileParser.cpp src/MapFileParser.h src/MapSection.cpp src/MapSection.h src/StringUtils.cpp src/StringUtils.h src/Result.cpp src/Result.h src/entity/MovingEntity.cpp src/entity/MovingEntity.h src/entity/Monster.cpp src/entity/Monster.h)
target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARIES})

