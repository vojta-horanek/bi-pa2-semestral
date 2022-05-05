#include <SDL2/SDL.h>
#include "resources/strings/L10n.h"

#include "Application.h"
#include <vector>
#include <iostream>
#include <string>

int main(int argc, char **argv) {
    if (argc < 2) {
        std::cerr << "Cannot run without a map file!" << std::endl;
        return EXIT_FAILURE;
    }
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS | SDL_INIT_TIMER) != 0) {
        SDL_LogCritical(SDL_LOG_CATEGORY_APPLICATION, L10n::cannotInitializeSDL, SDL_GetError());
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
