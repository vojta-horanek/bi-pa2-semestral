#ifndef TPOHB_GAME_H
#define TPOHB_GAME_H

#include "Window.h"
#include "GameState.h"
#include "entity/Player.h"
#include "Map.h"
#include "entity/Inventory.h"
#include "entity/Stats.h"
#include <vector>
#include <memory>
#include <cassert>
#include <stdexcept>
#include <iostream>

class Game {
private:
    GameState gameState;

    std::unique_ptr<Player> player;
    std::unique_ptr<Inventory> inventory;
    std::unique_ptr<Stats> stats;

    Map gameMap;

    int width, height;

    void onRender();

    void onEvent(SDL_Event event);

    void nextTurn();

    void avoidPlayerCollision();

public:

    explicit Game(int width, int height);

    ~Game();

    bool loadMap(const std::string &file);

    bool loop();

};


#endif //TPOHB_GAME_H
