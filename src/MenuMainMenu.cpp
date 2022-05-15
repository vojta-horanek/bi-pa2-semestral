#include "MenuMainMenu.h"
#include "resources/strings/Paths.h"

MenuMainMenu::MenuMainMenu() : MenuItem("MENU") {}

MenuItem::Item MenuMainMenu::getType() { return MenuItem::Item::MAIN_MENU; }
