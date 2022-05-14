#include "Menu.h"
#include "Renderer.h"
#include "resources/strings/Paths.h"
#include <memory>

Menu::Menu(int width, int height) : Screen(width, height) {
    backdrop = Texture(Paths::Bitmaps::menu_backdrop);
}

void Menu::onEvent(SDL_Event event) {
    if (event.type == SDL_KEYDOWN) {
        switch (event.key.keysym.sym) {
            case SDLK_UP:
                if (activeItem == 0)
                    activeItem = items.size() - 1;
                else
                    activeItem--;
                break;
            case SDLK_DOWN:
                if (activeItem == items.size() - 1)
                    activeItem = 0;
                else
                    activeItem++;
                break;
        }
    } else if (event.type == SDL_KEYUP) {
        switch (event.key.keysym.sym) {
            case SDLK_RETURN:
                onItemSelected(activeItem);
                break;
            case SDLK_ESCAPE:
                onEscapePressed();
        }
    }
}

void Menu::onRender() {
    backdrop.renderFullscreen();
    for (size_t item = 0; item < items.size(); item++) {
        auto &currentItem = items[item];
        if (item == activeItem) {
            currentItem->renderActive(currentItem->getDestinationPosition(
                (int)item, (int)items.size(), width, height));
        } else {
            currentItem->render(currentItem->getDestinationPosition(
                (int)item, (int)items.size(), width, height));
        }
    }
}

bool Menu::popSelf() { return !userInMenu; }
