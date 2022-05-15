#include "MenuResume.h"

#include "resources/strings/Paths.h"

MenuResume::MenuResume() : MenuItem("RESUME") {}

MenuItem::Item MenuResume::getType() { return MenuItem::Item::RESUME; }
