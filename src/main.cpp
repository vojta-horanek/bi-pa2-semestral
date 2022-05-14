#include "resources/strings/L10n.h"
#include <SDL2/SDL.h>

#include "Application.h"
#include <iostream>
#include <string>
#include <vector>

int main(int argc, char **argv) {

    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS | SDL_INIT_TIMER) != 0) {
        SDL_LogCritical(SDL_LOG_CATEGORY_APPLICATION, L10n::cannotInitializeSDL,
                        SDL_GetError());
        return EXIT_FAILURE;
    }

    std::vector<std::string> args;

    for (int arg = 1; arg < argc; arg++) {
        args.emplace_back(argv[arg]);
    }

    int retCode;
    {
        Application app;
        retCode = app.run(args);
    } // Call app destructor before SDL_Quit

    SDL_Quit();

    return retCode;
}
