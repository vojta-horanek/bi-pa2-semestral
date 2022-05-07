#include "EndScreen.h"

#include "resources/strings/Paths.h"
#include "MainMenu.h"

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
        navigateTo = std::make_unique<MainMenu>(width, height);
    }
}

void EndScreen::onRender() {
    background.renderFullscreen();
}

bool EndScreen::clearBackStack() {
    return hide;
}

std::unique_ptr<Screen> EndScreen::getNavigationDestination() {
    return std::move(navigateTo);
}
