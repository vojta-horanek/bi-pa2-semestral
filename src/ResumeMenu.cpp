#include "ResumeMenu.h"
#include "MainMenu.h"
#include "MenuMainMenu.h"
#include "MenuResume.h"
#include "MenuSave.h"
#include "SaveManager.h"
#include <iostream>

ResumeMenu::ResumeMenu(int width, int height) : Menu(width, height) {
    items.emplace_back(std::make_unique<MenuResume>());
    items.emplace_back(std::make_unique<MenuMainMenu>());
}

ResumeMenu::ResumeMenu(int width, int height, std::shared_ptr<GameState> gameState)
    : Menu(width, height), gameState(gameState) {
    items.emplace_back(std::make_unique<MenuResume>());
    items.emplace_back(std::make_unique<MenuSave>());
    items.emplace_back(std::make_unique<MenuMainMenu>());
}

void ResumeMenu::onItemSelected(size_t activeIndex) {
    auto type = items[activeIndex]->getType();
    switch (type) {
        case MenuItem::Item::RESUME:
            userInMenu = false;
            break;
        case MenuItem::Item::SAVE:
            saveGame();
            break;
        case MenuItem::Item::MAIN_MENU:
            goToMainMenu = true;
            navigationDestination = std::make_unique<MainMenu>(width, height);
            break;
        default:
            break;
    }
}

bool ResumeMenu::clearBackStack() { return goToMainMenu; }

void ResumeMenu::onEscapePressed() { userInMenu = false; }

void ResumeMenu::saveGame() {
    SaveManager manager;
    std::string saveFilePath = SaveManager::getSaveFilePath() + "_manual";
    Result saveResult = manager.saveGame(saveFilePath, saveFilePath + "_map", gameState);
    if (saveResult.isError)
        std::cerr << "Failed while saving the game: " << saveResult.errorText << std::endl;
}
