#include "MenuMainMenu.h"
#include "resources/strings/Paths.h"

MenuMainMenu::MenuMainMenu()
    : MenuItem(Texture(Paths::Bitmaps::menu_main_menu, true),
               Texture(Paths::Bitmaps::menu_main_menu_selected, true)) {}

MenuItem::Item MenuMainMenu::getType() { return MenuItem::Item::MAIN_MENU; }
