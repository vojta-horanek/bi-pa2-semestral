#include "MenuResume.h"

#include "resources/strings/L10n.h"

MenuResume::MenuResume() : MenuItem(L10n::resume) {}

MenuItem::Item MenuResume::getType() { return MenuItem::Item::RESUME; }
