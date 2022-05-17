#include "Screen.h"

#include "render/FPSController.h"

#include "render/Renderer.h"

Screen::Screen(int screenWidth, int screenHeight)
    : m_ScreenWidth(screenWidth), m_ScreenHeight(screenHeight) {}

Screen::~Screen() = default;

void Screen::onLoop() {
    FPSController::renderStart();

    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            m_ApplicationQuitRequested = true;
            return;
        } else {
            if (m_Dialog != nullptr) {
                m_Dialog->onEvent(event);
            } else {
                onEvent(event);
            }
        }
    }

    Renderer::getInstance().clear();
    onRender();

    if (m_Dialog != nullptr) {
        m_Dialog->onRender();

        if (!m_Dialog->getVisibility()) {
            m_Dialog = nullptr;
        }
    }

    Renderer::getInstance().present();

    FPSController::renderEnd();
}

std::unique_ptr<Screen> Screen::getNavigationDestination() {
    return std::move(m_NavigationDestination);
}

bool Screen::shouldPopSelf() { return false; }

bool Screen::shouldClearBackStack() { return false; }

void Screen::onResume() {}

void Screen::showDialog(std::unique_ptr<Dialog> dialog) {
    m_Dialog = std::move(dialog);
}
