#include "MenuSave.h"

#include "resources/strings/Paths.h"

MenuSave::MenuSave() : MenuItem("SAVE") {}

MenuItem::Item MenuSave::getType() { return MenuItem::Item::SAVE; }
