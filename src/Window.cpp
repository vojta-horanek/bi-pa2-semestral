#include "Window.h"
#include "render/Texture.h"

#include <cassert>

Window::Window(const std::string &title) {
    m_Size = Vec(WINDOW_WIDTH * BLOCK_PIXELS, WINDOW_HEIGHT * BLOCK_PIXELS);
    m_Window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED,
                                SDL_WINDOWPOS_CENTERED, m_Size.x, m_Size.y, SDL_WINDOW_HIDDEN);
}

Window::~Window() {
    Texture::clearStore();
    SDL_DestroyWindow(m_Window);
    m_Window = nullptr;
}

void Window::show() { SDL_ShowWindow(m_Window); }

SDL_Window *Window::getWindow() const { return m_Window; }

Vec Window::getSize() const { return m_Size; }