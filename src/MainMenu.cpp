#include "MainMenu.h"
#include "Game.h"
#include "MenuLoad.h"
#include "MenuNew.h"
#include "MenuQuit.h"
#include "SaveManager.h"
#include "GameCreationScreen.h"
#include "resources/strings/L10n.h"

MainMenu::MainMenu(int width, int height)
    : Menu(width, height), m_Title(L10n::appNameShort, 128) {
    m_Title.setColor(0, 0, 0);
    items.emplace_back(std::make_unique<MenuNew>());

    if (!SaveManager::getSaveFilePath().empty())
        items.emplace_back(std::make_unique<MenuLoad>());

    items.emplace_back(std::make_unique<MenuQuit>());
}

void MainMenu::onItemSelected(size_t activeIndex) {
    auto type = items[activeIndex]->getType();
    switch (type) {
        case MenuItem::Item::NEW:
            navigationDestination = std::make_unique<GameCreationScreen>(width, height);
            break;
        case MenuItem::Item::LOAD:
            navigationDestination = std::make_unique<Game>(
                width, height, SaveManager::getSaveFilePath());
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
    m_Title.render(Vec(width / 2 - m_Title.getBoxSize().x / 2,
                       m_Title.getBoxSize().y / 2));
}

int MainMenu::getItemsTopPadding() const { return m_Title.getBoxSize().y / 2; }