#ifndef TPOHB_GAME_H
#define TPOHB_GAME_H

#include "GameState.h"
#include "Map.h"
#include "Screen.h"
#include "Window.h"
#include "entity/Inventory.h"
#include "entity/Player.h"
#include "entity/Stats.h"
#include <cassert>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>
#include <vector>

class Game : public Screen {
  private:
    std::shared_ptr<Player> player;
    std::unique_ptr<Inventory> inventory;
    std::unique_ptr<Stats> stats;
    std::shared_ptr<GameState> gameState;
    std::shared_ptr<Map> gameMap;

    int gameWidth, gameHeight;

    std::string saveFilePath;

    void onRender() override;

    void onEvent(SDL_Event event) override;

    void nextTurn();

    void avoidPlayerCollision();

    bool loadSave();

    bool loadMap(const std::string &file);

  public:
    Game(int width, int height, int damage, int health);

    Game(int width, int height, const std::string &saveFile);

    bool popSelf() override;

    bool clearBackStack() override;

    void onResume() override;

    void onCreate() override;
};

#endif // TPOHB_GAME_H
