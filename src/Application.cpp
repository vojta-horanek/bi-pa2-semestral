#include "Application.h"

#include "Constants.h"
#include "MainMenu.h"
#include "Renderer.h"
#include "Text.h"
#include "Window.h"
#include "resources/strings/L10n.h"
#include <iostream>
#include <stack>
#include <stdexcept>

Application::Application() : window(Window(L10n::appName)) {

    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS | SDL_INIT_TIMER) != 0) {
        SDL_LogCritical(SDL_LOG_CATEGORY_APPLICATION, L10n::cannotInitializeSDL,
                        SDL_GetError());
        return;
    }

    Renderer::getInstance().createRenderer(window);

    if (!Text::initTTF()) {
        std::cerr << "Error initializing TTF, quiting..." << std::endl;
        return;
    }

    backstack.emplace(std::make_unique<MainMenu>(GAME_WIDTH * BLOCK_PIXELS,
                                                 GAME_HEIGHT * BLOCK_PIXELS));
}

Application::~Application() {
    Text::destroyTTF();
    SDL_Quit();
}

int Application::run() {
    window.show();

    while (!backstack.empty()) {

        backstack.top()->onLoop();

        if (backstack.top()->applicationQuitRequested)
            break;

        auto nextScreen = backstack.top()->getNavigationDestination();

        if (backstack.top()->clearBackStack()) {
            clearBackStack();
        } else if (backstack.top()->popSelf()) {
            popBackStack();
            if (!backstack.empty())
                backstack.top()->onResume();
        }

        if (nextScreen != nullptr) {
            navigateTo(std::move(nextScreen));
        }
    }

    return EXIT_SUCCESS;
}

void Application::popBackStack() { backstack.pop(); }

void Application::navigateTo(std::unique_ptr<Screen> destination) {
    backstack.push(std::move(destination));
    backstack.top()->onCreate();
}

void Application::clearBackStack() {
    while (!backstack.empty())
        backstack.pop();
}
