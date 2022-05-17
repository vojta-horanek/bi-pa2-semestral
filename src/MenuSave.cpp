#include "MenuSave.h"

#include "resources/strings/L10n.h"

MenuSave::MenuSave() : MenuItem(L10n::saveGame) {}

MenuItem::Item MenuSave::getType() { return MenuItem::Item::SAVE; }
