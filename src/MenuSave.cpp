#include "MenuSave.h"

#include "resources/strings/Paths.h"

MenuSave::MenuSave() : MenuItem(Texture(Paths::Bitmaps::menu_save, true),
                                Texture(Paths::Bitmaps::menu_save_selected, true)){

}

MenuItem::Item MenuSave::getType() {
    return MenuItem::Item::SAVE;
}
