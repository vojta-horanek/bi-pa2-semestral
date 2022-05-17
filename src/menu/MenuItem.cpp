#include "MenuItem.h"
#include "../render/Renderer.h"

MenuItem::MenuItem(const std::string &text) : m_Text(Text(text, 64)) {}

MenuItem::~MenuItem() = default;

void MenuItem::render(Vec position) {
    m_Text.setColor(0, 0, 0);

    Vec textPosition =
        Vec(position.x + (m_TextPadding / 2), position.y + (m_TextPadding / 2));

    m_Text.render(textPosition);
}

void MenuItem::renderActive(Vec position) {

    m_Text.setColor(255, 255, 255);
    Renderer::getInstance().selectDrawColor(0, 0, 0, 255);
    Renderer::getInstance().drawRectangle(Rect{position, getTotalSize()}, true);

    Vec textPosition =
        Vec(position.x + (m_TextPadding / 2), position.y + (m_TextPadding / 2));

    m_Text.render(textPosition);
}

Vec MenuItem::getDestinationPosition(int position, int itemCount,
                                     int screenWidth, int screenHeight) const {
    return {screenWidth / 2 - getTotalSize().x / 2,
            screenHeight / 2 - itemCount * getTotalSize().y / 2 +
                position * getTotalSize().y};
}

Vec MenuItem::getTotalSize() const {
    return m_Text.getBoxSize() + m_TextPadding;
}