#ifndef TPOHB_GAME_H
#define TPOHB_GAME_H

#include "Window.h"
#include "GameState.h"
#include "entity/Player.h"
#include "Map.h"
#include "entity/Inventory.h"
#include <vector>
#include <memory>
#include <cassert>

class Game {
private:
    GameState gameState;

    std::unique_ptr<Player> player;
    std::unique_ptr<Inventory> inventory;
    std::vector<std::unique_ptr<Entity>> entities;

    Map gameMap;

    inline static SDL_Renderer *_renderer;

public:

    static SDL_Renderer *getRenderer() {
        assert(_renderer != nullptr);
        return _renderer;
    }

    explicit Game(SDL_Renderer *renderer) {
        _renderer = renderer;
        inventory = std::make_unique<Inventory>(SCREEN_WIDTH);
        player = std::make_unique<Player>();
    }

    bool loop();

    void onRender();

    void onEvent(SDL_Event event);

    void loadTestEntities();
};


#endif //TPOHB_GAME_H
