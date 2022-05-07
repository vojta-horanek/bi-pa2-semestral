#include "MainMenu.h"
#include "Game.h"
#include "MenuNew.h"
#include "MenuLoad.h"
#include "MenuQuit.h"
#include "resources/strings/Paths.h"

MainMenu::MainMenu(int width, int height) : Menu(width, height) {
    items.emplace_back(std::make_unique<MenuNew>());
    items.emplace_back(std::make_unique<MenuLoad>());
    items.emplace_back(std::make_unique<MenuQuit>());
    title = Texture(Paths::Bitmaps::title, true);
}

void MainMenu::onItemSelected(size_t activeIndex) {
    auto type = items[activeIndex]->getType();
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
        default:
            break;
    }
}

void MainMenu::onEscapePressed() {
    // Do Nothing
}

void MainMenu::onRender() {
    Menu::onRender();
    // Render game title
    title.render(Vec(width / 2 - title.getWidth() * 2, title.getHeight() * 2), 4);
}
