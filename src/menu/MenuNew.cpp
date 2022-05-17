#include "MenuNew.h"

#include "../resources/strings/L10n.h"

MenuNew::MenuNew() : MenuItem(L10n::newGame) {}

MenuItem::Item MenuNew::getType() { return MenuItem::Item::NEW; }
