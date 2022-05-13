#include "Application.h"

#include "Window.h"
#include "resources/strings/L10n.h"
#include "Renderer.h"
#include "Constants.h"
#include "MainMenu.h"
#include <stack>

Application::Application() : window(Window(L10n::appName)) {
    Renderer::getInstance().createRenderer(window);
    backstack.emplace(
            std::make_unique<MainMenu>(GAME_WIDTH * BLOCK_PIXELS,
                                       GAME_HEIGHT * BLOCK_PIXELS));
}

int Application::run(const std::vector<std::string> &args) {
    window.show();

    while (!backstack.empty()) {

        backstack.top()->onLoop();

        if (backstack.top()->applicationQuitRequested) break;

        auto nextScreen = backstack.top()->getNavigationDestination();

        if (backstack.top()->clearBackStack()) {
            clearBackStack();
        } else if (backstack.top()->popSelf()) {
            popBackStack();
            if (!backstack.empty()) backstack.top()->onResume();
        }

        if (nextScreen != nullptr) {
            navigateTo(std::move(nextScreen), args);
        }
    }

    return EXIT_SUCCESS;
}

void Application::popBackStack() {
    backstack.pop();
}

void Application::navigateTo(std::unique_ptr<Screen> destination,
                             const std::vector<std::string> &args) {
    backstack.push(std::move(destination));
    backstack.top()->setArgs(args);
    backstack.top()->onCreate();
}

void Application::clearBackStack() {
    while (!backstack.empty()) backstack.pop();
}
