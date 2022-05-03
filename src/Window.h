#ifndef TPOHB_WINDOW_H
#define TPOHB_WINDOW_H

#include <SDL2/SDL.h>
#include <string>
#include "Constants.h"

class Window {
private:
    SDL_Window *window = nullptr;
    SDL_Renderer *renderer = nullptr;
public:
    explicit Window(const std::string &title) {
        window = SDL_CreateWindow(
                title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                GAME_WIDTH * BLOCK_SIZE * REAL_PIXEL_SIZE,
                (GAME_HEIGHT + 1) * BLOCK_SIZE * REAL_PIXEL_SIZE, 0
        );
    }

    ~Window() {
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);

        window = nullptr;
        renderer = nullptr;
    }

    void createRenderer();

    void show();

    SDL_Renderer *getRenderer() const;
};


#endif //TPOHB_WINDOW_H
