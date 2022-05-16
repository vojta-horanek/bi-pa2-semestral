#include "ResumeMenu.h"
#include "MainMenu.h"
#include "MenuMainMenu.h"
#include "MenuResume.h"
#include "MenuSave.h"
#include "MessageDialog.h"
#include "SaveManager.h"
#include <iostream>

ResumeMenu::ResumeMenu(int width, int height) : Menu(width, height) {
    items.emplace_back(std::make_unique<MenuResume>());
    items.emplace_back(std::make_unique<MenuMainMenu>());
}

ResumeMenu::ResumeMenu(int width, int height,
                       std::shared_ptr<GameState> gameState,
                       std::shared_ptr<Map> map)
    : Menu(width, height), gameState(gameState), map(map) {
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
    std::string saveFilePath = SaveManager::getSaveFilePath();
    std::string mapFilePath = saveFilePath + "_map";
    Result saveResult = manager.saveGame(saveFilePath, mapFilePath, *gameState);
    if (saveResult.isError) {
        std::cerr << "Failed while saving the game: " << saveResult.errorText
                  << std::endl;
        showDialog(std::make_unique<MessageDialog>(
            width, height,
            "Failed while saving the game: " + saveResult.errorText));

        return;
    }

    Result mapResult = map->saveToFile(mapFilePath, *gameState);
    if (mapResult.isError) {
        std::cerr << "Failed while saving the game: " << mapResult.errorText
                  << std::endl;
        showDialog(std::make_unique<MessageDialog>(
            width, height,
            "Failed while saving the game: " + mapResult.errorText));
        return;
    }

    showDialog(std::make_unique<MessageDialog>(width, height, "Saved"));
}
