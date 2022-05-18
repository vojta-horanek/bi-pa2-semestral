#include "Menu.h"
#include "../render/Renderer.h"
#include "../resources/strings/Paths.h"
#include <memory>

Menu::Menu(int screenWidth, int screenHeight) : Screen(screenWidth, screenHeight) {
    m_BackdropTexture = Texture(Paths::Bitmaps::menu_backdrop);
}

void Menu::onEvent(SDL_Event event) {
    if (event.type == SDL_KEYDOWN) {
        switch (event.key.keysym.sym) {
            case SDLK_UP:
                if (m_ActiveItemIndex == 0)
                    m_ActiveItemIndex = (int)m_MenuItems.size() - 1;
                else
                    m_ActiveItemIndex--;
                break;
            case SDLK_DOWN:
                if (m_ActiveItemIndex == (int)m_MenuItems.size() - 1)
                    m_ActiveItemIndex = 0;
                else
                    m_ActiveItemIndex++;
                break;
        }
    } else if (event.type == SDL_KEYUP) {
        switch (event.key.keysym.sym) {
            case SDLK_RETURN:
                onItemSelected(m_ActiveItemIndex);
                break;
            case SDLK_ESCAPE:
                onEscapePressed();
        }
    }
}

void Menu::onRender() {
    m_BackdropTexture.renderFullscreen();
    for (int item = 0; item < (int)m_MenuItems.size(); item++) {
        auto &currentItem = m_MenuItems[item];
        if (item == m_ActiveItemIndex) {
            currentItem->renderActive(
                currentItem
                    ->getDestinationPosition(item, (int)m_MenuItems.size(),
                                             m_ScreenWidth, m_ScreenHeight)
                    .withY(getItemsTopPadding()));
        } else {
            currentItem->render(
                currentItem
                    ->getDestinationPosition(item, (int)m_MenuItems.size(),
                                             m_ScreenWidth, m_ScreenHeight)
                    .withY(getItemsTopPadding()));
        }
    }
}

bool Menu::shouldPopSelf() { return !m_IsUserInMenu; }

int Menu::getItemsTopPadding() const { return 0; }
