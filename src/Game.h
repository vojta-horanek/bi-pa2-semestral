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

class Game {
private:
    GameState gameState;

    std::unique_ptr<Player> player;
    std::unique_ptr<Inventory> inventory;
    std::unique_ptr<Stats> stats;
    std::vector<std::unique_ptr<Entity>> entities;

    Map gameMap;

    int width, height;

    inline static SDL_Renderer *_renderer;

public:

    static SDL_Renderer *getRenderer() {
        assert(_renderer != nullptr);
        return _renderer;
    }

    explicit Game(SDL_Renderer *renderer, int width, int height) {
        _renderer = renderer;
        inventory = std::make_unique<Inventory>(width);
        player = std::make_unique<Player>();
        stats = std::make_unique<Stats>(3);
        this->width = width;
        this->height = height;
    }

    bool loop();

    void onRender();

    void onEvent(SDL_Event event);

    void loadTestEntities();
};


#endif //TPOHB_GAME_H
