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

    static SDL_Renderer *renderer;

    void onRender();

    void onEvent(SDL_Event event);

    void nextTurn();

    void avoidPlayerCollision();

public:

    static SDL_Renderer *getRenderer();

    explicit Game(SDL_Renderer *renderer, int width, int height);

    ~Game();

    bool loadMap(const std::string &file);

    bool loop();

};


#endif //TPOHB_GAME_H
