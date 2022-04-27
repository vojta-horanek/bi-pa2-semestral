#include <iostream>
#include <SDL2/SDL.h>
#include "Window.h"
#include "resources/strings/L10n.h"
#include "Texture.h"
#include "State.h"

int main() {

    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS | SDL_INIT_TIMER) != 0) {
        SDL_LogCritical(SDL_LOG_CATEGORY_APPLICATION, L10n::cannotInitializeSDL, SDL_GetError());
        return EXIT_FAILURE;
    }

    State gameState;

    Window window("Test");
    window.attachRenderer();
    window.show();

    Texture texture("resources/bitmaps/bricks.bmp", window.getRenderer());

    while (gameState.running) {
        SDL_Event event;
        while(SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT:
                    gameState.running = false;
                    break;
            }
        }

        SDL_RenderClear(window.getRenderer());
        SDL_RenderCopy(window.getRenderer(), texture.get(), nullptr, nullptr);
        SDL_RenderPresent(window.getRenderer());
    }

    SDL_Quit();

    return 0;
}
