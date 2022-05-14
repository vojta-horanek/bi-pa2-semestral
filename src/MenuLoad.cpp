#include "MenuLoad.h"

#include "Texture.h"
#include "resources/strings/Paths.h"

MenuLoad::MenuLoad()
    : MenuItem(Texture(Paths::Bitmaps::menu_load, true),
               Texture(Paths::Bitmaps::menu_load_selected, true)) {}

MenuItem::Item MenuLoad::getType() { return MenuItem::Item::LOAD; }
