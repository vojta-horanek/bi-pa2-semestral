#include "Window.h"
#include "render/Texture.h"

#include <cassert>

Window::Window(const std::string &title) {
    m_Size = Vec(WINDOW_WIDTH * BLOCK_PIXELS, WINDOW_HEIGHT * BLOCK_PIXELS);
    window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED,
                              SDL_WINDOWPOS_CENTERED, m_Size.x, m_Size.y, 0);
}

Window::~Window() {
    Texture::clearStore();
    SDL_DestroyWindow(window);
    window = nullptr;
}

void Window::show() { SDL_ShowWindow(window); }

SDL_Window *Window::getWindow() const { return window; }

Vec Window::getSize() const { return m_Size; }