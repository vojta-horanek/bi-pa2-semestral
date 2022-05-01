#include "Application.h"

#include "Game.h"
#include "Window.h"
#include "resources/strings/L10n.h"

Application::Application() : window(Window(L10n::appName)) {
    window.createRenderer();
}

int Application::run() {
    window.show();

    Game game(window.getRenderer(), SCREEN_WIDTH, SCREEN_HEIGHT);

    game.loadTestEntities();
    while (game.loop());

    return EXIT_SUCCESS;
}