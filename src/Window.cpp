#include "Window.h"

#include <cassert>

Window::Window(const std::string &title) {
    window = SDL_CreateWindow(
            title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
            GAME_WIDTH * BLOCK_SIZE * REAL_PIXEL_SIZE,
            (GAME_HEIGHT + 1) * BLOCK_SIZE * REAL_PIXEL_SIZE, 0
    );
}

Window::~Window() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    window = nullptr;
    renderer = nullptr;
}

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
