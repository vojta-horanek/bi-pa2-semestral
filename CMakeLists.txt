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
        src/entity/Inventory.cpp src/entity/Inventory.h src/entity/Sword.h)
target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARIES})

