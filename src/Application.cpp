#include "Application.h"

#include "Texture.h"
#include "GameState.h"
#include "Game.h"
#include "Window.h"
#include "resources/strings/L10n.h"

Application::Application() : window(Window(L10n::appName)) {
    window.createRenderer();
}

int Application::run() {
    window.show();

    Game game(window.getRenderer());

    game.loadTestEntities();
    while (game.render());

    return EXIT_SUCCESS;
}