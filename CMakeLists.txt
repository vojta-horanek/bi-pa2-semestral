cmake_minimum_required(VERSION 3.22)
project(TPOHB)

set(CMAKE_CXX_STANDARD 17)

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

add_executable(${PROJECT_NAME}
        src/main.cpp
        src/Vec.cpp
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
        src/entity/Inventory.cpp src/entity/Inventory.h src/entity/Sword.h src/entity/Sword.cpp src/entity/Axe.cpp src/entity/Axe.h src/entity/Weapon.h src/entity/Weapon.cpp src/entity/Weapon.fwd.h src/entity/Hearth.h src/entity/Stats.cpp src/entity/Stats.h src/entity/AnimatedEntity.cpp src/entity/AnimatedEntity.h src/MapFileParser.cpp src/MapFileParser.h src/MapSection.cpp src/MapSection.h src/StringUtils.cpp src/StringUtils.h src/Result.cpp src/Result.h src/entity/MovingEntity.cpp src/entity/MovingEntity.h src/entity/Monster.cpp src/entity/Monster.h src/MapSection.fwd.h src/resources/strings/Paths.h src/entity/Apple.cpp src/entity/Hearth.cpp src/Renderer.cpp src/Renderer.h src/Rect.cpp src/Rect.h src/Screen.cpp src/Screen.h src/Menu.cpp src/Menu.h src/MenuItem.cpp src/MenuItem.h src/MenuNew.cpp src/MenuNew.h src/MenuLoad.cpp src/MenuLoad.h src/MenuQuit.cpp src/MenuQuit.h src/entity/Zombie.cpp src/entity/Zombie.h src/entity/PickupEntity.cpp src/entity/PickupEntity.h src/entity/BlockEntity.cpp src/entity/BlockEntity.h src/entity/Monster.fwd.h src/FightScreen.cpp src/FightScreen.h src/MainMenu.cpp src/MainMenu.h src/ResumeMenu.cpp src/ResumeMenu.h src/MenuResume.cpp src/MenuResume.h src/MenuMainMenu.cpp src/MenuMainMenu.h src/MenuSave.cpp src/MenuSave.h)
target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARIES})

