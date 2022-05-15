#include "MenuLoad.h"

#include "Texture.h"
#include "resources/strings/Paths.h"

MenuLoad::MenuLoad()
    : MenuItem("LOAD") {}

MenuItem::Item MenuLoad::getType() { return MenuItem::Item::LOAD; }
