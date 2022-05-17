#include "Dialog.h"
#include "render/Rect.h"
#include "render/Renderer.h"

Dialog::Dialog(int screenWidth, int screenHeight)
    : m_ScreenWidth(screenWidth), m_ScreenHeight(screenHeight),
      m_Width(screenWidth / 2), m_Height(screenHeight / 2) {}

bool Dialog::getVisibility() const { return m_isVisible; }

void Dialog::onRender() {
    Vec position = getDialogPosition();

    Rect fillDestination{position, Vec(m_Width, m_Height)};

    position.x -= outlineThickness;
    position.y -= outlineThickness;

    Rect outlineDestination{position, Vec(m_Width + outlineThickness * 2,
                                          m_Height + outlineThickness * 2)};

    Renderer::getInstance().selectDrawColor(0x00, 0x00, 0x00, 0xff);
    Renderer::getInstance().drawRectangle(outlineDestination, true);
    Renderer::getInstance().selectDrawColor(0x8e, 0xa3, 0x48, 0xff);
    Renderer::getInstance().drawRectangle(fillDestination, true);
}

Vec Dialog::getDialogPosition() const {
    return {m_ScreenWidth / 2 - m_Width / 2, m_ScreenHeight / 2 - m_Height / 2};
}