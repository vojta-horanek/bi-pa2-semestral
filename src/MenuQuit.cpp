#include "MenuQuit.h"

#include "Texture.h"
#include "resources/strings/Paths.h"

MenuQuit::MenuQuit() : MenuItem("QUIT") {}

MenuItem::Item MenuQuit::getType() { return MenuItem::Item::QUIT; }
