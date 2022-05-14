#include "EndScreen.h"

#include "MainMenu.h"
#include "resources/strings/Paths.h"

EndScreen::EndScreen(bool won, int width, int height) : Screen(width, height) {
    if (won) {
        background = Texture(Paths::Bitmaps::screen_won);
    } else {
        background = Texture(Paths::Bitmaps::screen_lost);
    }
}

void EndScreen::onEvent(SDL_Event event) {
    if (event.type == SDL_KEYUP) {
        hide = true;
        navigationDestination = std::make_unique<MainMenu>(width, height);
    }
}

void EndScreen::onRender() { background.renderFullscreen(); }

bool EndScreen::clearBackStack() { return hide; }