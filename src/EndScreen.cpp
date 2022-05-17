#include "EndScreen.h"

#include "menu/MainMenu.h"
#include "resources/strings/Paths.h"

EndScreen::EndScreen(bool hasWon, int screenWidth, int screenHeight)
    : Screen(screenWidth, screenHeight) {
    if (hasWon) {
        m_BackgroundTexture = Texture(Paths::Bitmaps::screen_won);
    } else {
        m_BackgroundTexture = Texture(Paths::Bitmaps::screen_lost);
    }
}

void EndScreen::onEvent(SDL_Event event) {
    if (event.type == SDL_KEYUP) {
        m_IsVisible = false;
        m_NavigationDestination =
            std::make_unique<MainMenu>(m_ScreenWidth, m_ScreenHeight);
    }
}

void EndScreen::onRender() { m_BackgroundTexture.renderFullscreen(); }

bool EndScreen::shouldClearBackStack() { return !m_IsVisible; }