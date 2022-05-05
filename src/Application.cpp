#include "Application.h"

#include "Window.h"
#include "resources/strings/L10n.h"
#include "Renderer.h"
#include "Constants.h"
#include "Menu.h"

Application::Application() : window(Window(L10n::appName)) {
    Renderer::getInstance().createRenderer(window);
    currentScreen = std::make_unique<Menu>(GAME_WIDTH * REAL_PIXEL_SIZE * BLOCK_SIZE, GAME_HEIGHT * REAL_PIXEL_SIZE * BLOCK_SIZE);
}

int Application::run(const std::vector<std::string> &args) {
    window.show();

    while (currentScreen != nullptr && currentScreen->loop()) {
        auto nextScreen = currentScreen->getNextScreen();
        if (nextScreen != nullptr) {
            currentScreen = std::move(nextScreen);
        }
    }
    return EXIT_SUCCESS;
}