#include "Text.h"

#include "resources/strings/Paths.h"
#include <iostream>

TTF_Font *Text::s_Font = nullptr;

Text::Text(const std::string &text) : m_Text(text) {}
Text::~Text() {
    if (m_FontTexture != nullptr)
        SDL_DestroyTexture(m_FontTexture);
    m_FontTexture = nullptr;
}

Text::Text(Text &&other) noexcept
    : m_Text(other.m_Text), m_FontTexture(other.m_FontTexture),
      m_Color(other.m_Color) {
    other.m_FontTexture = nullptr;
}

Text &Text::operator=(Text &&other) noexcept {
    if (&other == this)
        return *this;
    if (m_FontTexture != nullptr)
        SDL_DestroyTexture(m_FontTexture);
    m_FontTexture = other.m_FontTexture;
    other.m_FontTexture = nullptr;
    return *this;
}

void Text::render(Vec position) {}

void Text::setColor(int r, int g, int b) { m_Color = std::make_tuple(r, g, b); }

bool Text::initTTF() {
    if (TTF_Init() < 0) {
        std::cerr << TTF_GetError() << std::endl;
        return false;
    }

    s_Font = TTF_OpenFont(Paths::Fonts::pixel, 16);
    if (s_Font == nullptr) {
        std::cerr << TTF_GetError() << std::endl;
        return false;
    }

    return true;
}
void Text::destroyTTF() {
    TTF_CloseFont(s_Font);
    s_Font = nullptr;
    TTF_Quit();
}
