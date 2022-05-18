#include "MainMenu.h"
#include "../Game.h"
#include "../GameCreationScreen.h"
#include "../MessageDialog.h"
#include "../SaveManager.h"
#include "../resources/strings/L10n.h"
#include "MenuHelp.h"
#include "MenuLoad.h"
#include "MenuNew.h"
#include "MenuQuit.h"

MainMenu::MainMenu(int width, int height)
    : Menu(width, height), m_TitleText(L10n::appNameShort, 128) {
    m_TitleText.setColor(0, 0, 0);
    m_TitleText.setWrapWidth(width - 40);
    m_MenuItems.emplace_back(std::make_unique<MenuNew>());

    if (!SaveManager::getSaveFilePath().empty())
        m_MenuItems.emplace_back(std::make_unique<MenuLoad>());

    m_MenuItems.emplace_back(std::make_unique<MenuHelp>());
    m_MenuItems.emplace_back(std::make_unique<MenuQuit>());
}

void MainMenu::onItemSelected(int activeIndex) {
    auto type = m_MenuItems[activeIndex]->getType();
    switch (type) {
        case MenuItem::Item::NEW:
            m_NavigationDestination = std::make_unique<GameCreationScreen>(
                m_ScreenWidth, m_ScreenHeight);
            break;
        case MenuItem::Item::LOAD:
            m_NavigationDestination = std::make_unique<Game>(
                m_ScreenWidth, m_ScreenHeight, SaveManager::getSaveFilePath());
            break;
        case MenuItem::Item::QUIT:
            m_IsUserInMenu = false;
            break;
        case MenuItem::Item::HELP:
            showDialog(std::make_unique<MessageDialog>(
                m_ScreenWidth, m_ScreenHeight, L10n::helpText));
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
    m_TitleText.render(Vec(m_ScreenWidth / 2 - m_TitleText.getBoxSize().x / 2,
                           m_TitleText.getBoxSize().y / 2));
}

int MainMenu::getItemsTopPadding() const { return m_TitleText.getBoxSize().y / 2; }