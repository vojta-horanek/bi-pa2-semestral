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
            std::make_unique<MainMenu>(GAME_WIDTH * REAL_PIXEL_SIZE * BLOCK_SIZE,
                                       GAME_HEIGHT * REAL_PIXEL_SIZE * BLOCK_SIZE));
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
        }

        if (nextScreen != nullptr) {
            navigateTo(std::move(nextScreen));
        }
    }

    return EXIT_SUCCESS;
}

void Application::popBackStack() {
    backstack.pop();
}

void Application::navigateTo(std::unique_ptr<Screen> destination) {
    backstack.push(std::move(destination));
}

void Application::clearBackStack() {
    while (!backstack.empty()) backstack.pop();
}
