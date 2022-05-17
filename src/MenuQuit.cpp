#include "MenuQuit.h"

#include "Texture.h"
#include "resources/strings/L10n.h"

MenuQuit::MenuQuit() : MenuItem(L10n::quit) {}

MenuItem::Item MenuQuit::getType() { return MenuItem::Item::QUIT; }
