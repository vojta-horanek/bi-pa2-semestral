#include "Menu.h"
#include "Game.h"
#include "MenuNew.h"
#include "MenuLoad.h"
#include "MenuQuit.h"
#include "Renderer.h"
#include <memory>

Menu::Menu(int width, int height) : Screen(width, height) {
    items.emplace_back(std::make_unique<MenuNew>());
    items.emplace_back(std::make_unique<MenuLoad>());
    items.emplace_back(std::make_unique<MenuQuit>());
}

bool Menu::shouldContinue() {
    return userInMenu;
}

std::unique_ptr<Screen> Menu::getNextScreen() {
    return std::move(nextScreen);
}

void Menu::onEvent(SDL_Event event) {
    if (event.type == SDL_KEYDOWN) {
        switch (event.key.keysym.sym) {
            case SDLK_UP:
                if (activeItem == 0) activeItem = items.size() - 1;
                else activeItem--;
                break;
            case SDLK_DOWN:
                if (activeItem == items.size() - 1) activeItem = 0;
                else activeItem++;
                break;
        }
    } else if (event.type == SDL_KEYUP) {
        switch (event.key.keysym.sym) {
            case SDLK_RETURN:
                onItemSelected();
                break;
        }
    }
}

void Menu::onRender() {
    Renderer::getInstance().selectDrawColor(0x59, 0x59, 0x59, 255);

    for (size_t item = 0; item < items.size(); item++) {
        auto &currentItem = items[item];
        if (item == activeItem) {
            currentItem->renderActive(
                    currentItem->getDestinationPosition((int) item, (int) items.size(), width, height)
            );
        } else {
            currentItem->render(
                    currentItem->getDestinationPosition((int) item, (int) items.size(), width, height)
            );
        }
    }
}

void Menu::onItemSelected() {
    auto type = items[activeItem]->getType();
    switch (type) {
        case MenuItem::Item::NEW:
            nextScreen = std::make_unique<Game>(width, height);
            break;
        case MenuItem::Item::LOAD:
            nextScreen = std::make_unique<Game>(width, height, "examples/save");
            break;
        case MenuItem::Item::QUIT:
            userInMenu = false;
            break;
    }
}
