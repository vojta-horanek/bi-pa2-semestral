#include "MenuResume.h"

#include "resources/strings/Paths.h"

MenuResume::MenuResume() : MenuItem(
        Texture(Paths::Bitmaps::menu_resume, true),
        Texture(Paths::Bitmaps::menu_resume_selected, true)
        ) {

}

MenuItem::Item MenuResume::getType() {
    return MenuItem::Item::RESUME;
}
