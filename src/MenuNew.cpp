#include "MenuNew.h"

#include "Texture.h"
#include "resources/strings/Paths.h"

MenuNew::MenuNew() : MenuItem("NEW") {}

MenuItem::Item MenuNew::getType() { return MenuItem::Item::NEW; }
