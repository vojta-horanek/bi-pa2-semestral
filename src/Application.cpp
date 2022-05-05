#include "Application.h"

#include "Game.h"
#include "Window.h"
#include "resources/strings/L10n.h"
#include "Renderer.h"

Application::Application() : window(Window(L10n::appName)) {
    Renderer::getInstance().createRenderer(window);
}

int Application::run(const std::vector<std::string> & args) {
    window.show();

    Game game(GAME_WIDTH, GAME_HEIGHT);

    if (!game.loadMap(args[0])) {
        return EXIT_FAILURE;
    } else {
        while (game.loop());
        return EXIT_SUCCESS;
    }
}