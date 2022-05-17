#include "MenuLoad.h"

#include "../render/Texture.h"
#include "../resources/strings/L10n.h"

MenuLoad::MenuLoad() : MenuItem(L10n::loadGame) {}

MenuItem::Item MenuLoad::getType() { return MenuItem::Item::LOAD; }
