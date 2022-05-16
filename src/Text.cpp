#include "Text.h"

#include "Rect.h"
#include "Renderer.h"
#include "resources/strings/Paths.h"
#include <SDL2/SDL.h>
#include <iostream>

Text::Text(const std::string &text, int fontSize)
    : m_Text(text), m_FontSize(fontSize) {
    m_FontTexture = createTexture();

    if (m_FontTexture == nullptr)
        std::cerr << "Failed while creating font texture" << std::endl;
}

Text::Text(const std::string &text) : Text(text, 24) {}

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

void Text::render(Vec position) const {

    if (m_FontTexture == nullptr)
        return;

    Rect destination{position, m_BoxSize};

    Renderer::getInstance().render(m_FontTexture, destination);
}

void Text::setColor(unsigned char r, unsigned char g, unsigned char b) {

    if (m_Color.r == r && m_Color.g == g && m_Color.b == b)
        return;
    m_Color = {r, g, b, 255};
    swapTexture();
}

void Text::setFontSize(int fontSize) {
    if (fontSize == m_FontSize)
        return;

    m_FontSize = fontSize;
    swapTexture();
}

void Text::setWrapWidth(int wrapWidth) {
    if (wrapWidth == m_WrapWidth)
        return;

    m_WrapWidth = wrapWidth;
    swapTexture();
}

void Text::swapTexture() {
    SDL_Texture *newFontTexture = createTexture();

    if (newFontTexture == nullptr)
        std::cerr << "Failed while creating font texture" << std::endl;

    SDL_DestroyTexture(m_FontTexture);

    m_FontTexture = newFontTexture;
}

SDL_Texture *Text::createTexture() {

    TTF_Font *font = getFont();

    if (font == nullptr)
        return nullptr;

    SDL_Surface *surface = TTF_RenderText_Solid_Wrapped(font, m_Text.c_str(),
                                                        m_Color, m_WrapWidth);
    if (surface == nullptr)
        return nullptr;

    SDL_Texture *fontTexture = Renderer::getInstance().createTexture(surface);

    if (fontTexture == nullptr)
        return nullptr;

    m_BoxSize.x = surface->w;
    m_BoxSize.y = surface->h;

    SDL_FreeSurface(surface);

    return fontTexture;
}

TTF_Font *Text::getFont() {

    // Try to find the font if it already exists
    auto foundFont = s_Fonts.find(m_FontSize);
    if (foundFont != s_Fonts.end())
        return foundFont->second;

    // Create a new font with the specified size
    TTF_Font *font = TTF_OpenFont(Paths::Fonts::pixel, m_FontSize);

    if (font == nullptr) {
        std::cerr << TTF_GetError() << std::endl;
        return nullptr;
    }

    s_Fonts[m_FontSize] = font;
    return font;
}

Vec Text::getBoxSize() const { return m_BoxSize; }

int Text::getFontSize() const { return m_FontSize; }

std::map<int, TTF_Font *> Text::s_Fonts;

bool Text::initTTF() {
    if (TTF_Init() < 0) {
        std::cerr << TTF_GetError() << std::endl;
        return false;
    }

    return true;
}
void Text::destroyTTF() {
    for (const auto &[_, font] : s_Fonts)
        TTF_CloseFont(font);

    s_Fonts.clear();
    TTF_Quit();
}
