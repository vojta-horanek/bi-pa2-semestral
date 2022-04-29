#include <iostream>
#include <SDL2/SDL.h>
#include "resources/strings/L10n.h"

#include "Application.h"

int main() {

    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS | SDL_INIT_TIMER) != 0) {
        SDL_LogCritical(SDL_LOG_CATEGORY_APPLICATION, L10n::cannotInitializeSDL, SDL_GetError());
        return EXIT_FAILURE;
    }

    int retCode;
    {
        Application app;
        retCode = app.run();
    } // Call app destructor before SDL_Quit

    SDL_Quit();

    return retCode;
}
