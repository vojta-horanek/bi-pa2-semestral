#include <iostream>
#include "ResumeMenu.h"
#include "MainMenu.h"
#include "MenuResume.h"
#include "MenuMainMenu.h"
#include "MenuSave.h"

ResumeMenu::ResumeMenu(int width, int height) : Menu(width, height) {
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
            // TODO
            std::cout << "Saving" << std::endl;
            break;
        case MenuItem::Item::MAIN_MENU:
            goToMainMenu = true;
            nextScreen = std::make_unique<MainMenu>(width, height);
            break;
        default:
            break;
    }
}

bool ResumeMenu::clearBackStack() {
    return goToMainMenu;
}

void ResumeMenu::onEscapePressed() {
    userInMenu = false;
}
