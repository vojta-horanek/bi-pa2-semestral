#include "MenuMainMenu.h"
#include "resources/strings/L10n.h"


MenuMainMenu::MenuMainMenu() : MenuItem(L10n::mainMenu) {}

MenuItem::Item MenuMainMenu::getType() { return MenuItem::Item::MAIN_MENU; }
