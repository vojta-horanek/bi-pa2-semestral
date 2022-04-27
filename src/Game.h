#ifndef TPOHB_GAME_H
#define TPOHB_GAME_H

#include "Window.h"
#include "GameState.h"

class Game {
private:
    Window &window;
    GameState gameState;

    SDL_Renderer * getRenderer() const {
        return window.getRenderer();
    }

public:
    explicit Game(Window &window) : window(window) {}

    bool render();
    void onRender();
    void onUpdate();
    void onEvent(SDL_Event event);
};


#endif //TPOHB_GAME_H
