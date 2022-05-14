#include "MenuQuit.h"

#include "Texture.h"
#include "resources/strings/Paths.h"

MenuQuit::MenuQuit()
    : MenuItem(Texture(Paths::Bitmaps::menu_quit, true),
               Texture(Paths::Bitmaps::menu_quit_selected, true)) {}

MenuItem::Item MenuQuit::getType() { return MenuItem::Item::QUIT; }
