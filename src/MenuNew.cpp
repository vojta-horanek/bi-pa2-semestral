#include "MenuNew.h"

#include "Texture.h"
#include "resources/strings/Paths.h"

MenuNew::MenuNew()
    : MenuItem(Texture(Paths::Bitmaps::menu_new, true),
               Texture(Paths::Bitmaps::menu_new_selected, true)) {}

MenuItem::Item MenuNew::getType() { return MenuItem::Item::NEW; }
