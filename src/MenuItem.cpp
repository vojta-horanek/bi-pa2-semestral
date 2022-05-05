#include "MenuItem.h"

void MenuItem::render(Vec position) {
    inactive.render(position, renderScale);
}

void MenuItem::renderActive(Vec position) {
    active.render(position, renderScale);
}

MenuItem::MenuItem(Texture inactive, Texture active) : inactive(inactive), active(active) {}

Vec MenuItem::getDestinationPosition(int position, int itemCount, int screenWidth, int screenHeight) const {
    return {screenWidth / 2 - width / 2 * renderScale,
            screenHeight / 2 - itemCount * height / 2 + position * height * renderScale};

}

MenuItem::~MenuItem() = default;
