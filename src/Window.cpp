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
    SDL_DestroyWindow(window);
    window = nullptr;
}

void Window::show() {
    SDL_ShowWindow(window);
}

SDL_Window *Window::getWindow() const {
    return window;
}