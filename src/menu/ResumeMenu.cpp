#include "ResumeMenu.h"
#include "../MessageDialog.h"
#include "../SaveManager.h"
#include "MainMenu.h"
#include "MenuMainMenu.h"
#include "MenuResume.h"
#include "MenuSave.h"
#include <iostream>
#include <utility>

ResumeMenu::ResumeMenu(int width, int height) : Menu(width, height) {
    m_MenuItems.emplace_back(std::make_unique<MenuResume>());
    m_MenuItems.emplace_back(std::make_unique<MenuMainMenu>());
}

ResumeMenu::ResumeMenu(int width, int height,
                       std::shared_ptr<GameState> gameState,
                       std::shared_ptr<Map> map)
    : Menu(width, height), m_GameState(std::move(gameState)), m_Map(std::move(map)) {
    m_MenuItems.emplace_back(std::make_unique<MenuResume>());
    m_MenuItems.emplace_back(std::make_unique<MenuSave>());
    m_MenuItems.emplace_back(std::make_unique<MenuMainMenu>());
}

void ResumeMenu::onItemSelected(int activeIndex) {
    auto type = m_MenuItems[activeIndex]->getType();
    switch (type) {
        case MenuItem::Item::RESUME:
            m_IsUserInMenu = false;
            break;
        case MenuItem::Item::SAVE:
            saveGame();
            break;
        case MenuItem::Item::MAIN_MENU:
            m_GoToMainMenu = true;
            m_NavigationDestination =
                std::make_unique<MainMenu>(m_ScreenWidth, m_ScreenHeight);
            break;
        default:
            break;
    }
}

bool ResumeMenu::shouldClearBackStack() { return m_GoToMainMenu; }

void ResumeMenu::onEscapePressed() { m_IsUserInMenu = false; }

void ResumeMenu::saveGame() {
    SaveManager manager;
    std::string saveFilePath = SaveManager::getSaveFilePath();
    std::string mapFilePath = saveFilePath + "_map";
    Result saveResult = manager.saveGame(saveFilePath, mapFilePath, *m_GameState);
    if (saveResult.isError) {
        std::cerr << "Failed while saving the game: " << saveResult.errorText
                  << std::endl;
        showDialog(std::make_unique<MessageDialog>(
            m_ScreenWidth, m_ScreenHeight,
            "Failed while saving the game: " + saveResult.errorText));

        return;
    }

    Result mapResult = m_Map->saveToFile(mapFilePath, *m_GameState);
    if (mapResult.isError) {
        std::cerr << "Failed while saving the game: " << mapResult.errorText
                  << std::endl;
        showDialog(std::make_unique<MessageDialog>(
            m_ScreenWidth, m_ScreenHeight,
            "Failed while saving the game: " + mapResult.errorText));
        return;
    }

    showDialog(std::make_unique<MessageDialog>(m_ScreenWidth, m_ScreenHeight,
                                               "Saved"));
}
