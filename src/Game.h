#ifndef TPOHB_GAME_H
#define TPOHB_GAME_H

#include "Window.h"
#include "GameState.h"
#include "entity/Player.h"
#include "Map.h"
#include "entity/Inventory.h"
#include "entity/Stats.h"
#include "Screen.h"
#include <vector>
#include <memory>
#include <cassert>
#include <stdexcept>
#include <iostream>

class Game : public Screen {
private:
    GameState gameState;

    std::unique_ptr<Player> player;
    std::unique_ptr<Inventory> inventory;
    std::unique_ptr<Stats> stats;
    std::unique_ptr<Screen> nextScreen = nullptr;

    Map gameMap;

    int gameWidth, gameHeight;

    void onRender() override;

    void onEvent(SDL_Event event) override;

    void nextTurn();

    void avoidPlayerCollision();
protected:
    bool shouldContinue() override;

public:

    explicit Game(int width, int height);

    explicit Game(int width, int height, const std::string & saveFile);

    ~Game() override;

    std::unique_ptr<Screen> getNextScreen() override;

    bool loadMap(const std::string &file);

};


#endif //TPOHB_GAME_H
