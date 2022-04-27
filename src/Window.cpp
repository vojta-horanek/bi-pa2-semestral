#include "Window.h"

#include <cassert>

void Window::show() {
    assert(renderer != nullptr);
    SDL_ShowWindow(window);
}

void Window::createRenderer() {
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
}

SDL_Renderer *Window::getRenderer() const {
    assert(renderer != nullptr);
    return renderer;
}
