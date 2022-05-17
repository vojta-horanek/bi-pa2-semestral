#include "MenuHelp.h"

#include "../render/Texture.h"
#include "../resources/strings/L10n.h"

MenuHelp::MenuHelp() : MenuItem(L10n::help) {}

MenuItem::Item MenuHelp::getType() { return MenuItem::Item::HELP; }
