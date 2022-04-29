#ifndef TPOHB_GAME_H
#define TPOHB_GAME_H

#include "Window.h"
#include "GameState.h"
#include "enitity/Player.h"
#include <vector>
#include <memory>
#include <cassert>

class Game {
private:
    GameState gameState;

    Player *player;
    std::vector<std::unique_ptr<Entity>> entities;

    inline static SDL_Renderer *_renderer;

public:

    static SDL_Renderer *getRenderer() {
        assert(_renderer != nullptr);
        return _renderer;
    }

    explicit Game(SDL_Renderer *renderer) {
        _renderer = renderer;
        player = new Player();
    }

    bool render();

    void onRender();

    void onEvent(SDL_Event event);

    void loadTestEntities();
};


#endif //TPOHB_GAME_H
