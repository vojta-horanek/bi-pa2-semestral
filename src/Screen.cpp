#include "Screen.h"
#include "FPSController.h"

#include "Renderer.h"

Screen::Screen(int width, int height) : width(width), height(height) {}

Screen::~Screen() = default;

void Screen::onLoop() {
    FPSController::renderStart();

    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            applicationQuitRequested = true;
            return;
        } else {
            onEvent(event);
        }
    }

    Renderer::getInstance().clear();
    onRender();
    Renderer::getInstance().present();

    FPSController::renderEnd();
}
