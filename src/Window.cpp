#include "Window.h"
#include "Texture.h"

#include <cassert>

Window::Window(const std::string &title) {
    window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED,
                              SDL_WINDOWPOS_CENTERED, GAME_WIDTH * BLOCK_PIXELS,
                              (GAME_HEIGHT + 1) * BLOCK_PIXELS, 0);
}

Window::~Window() {
    Texture::clearStore();
    SDL_DestroyWindow(window);
    window = nullptr;
}

void Window::show() { SDL_ShowWindow(window); }

SDL_Window *Window::getWindow() const { return window; }