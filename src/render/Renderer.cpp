#include "Renderer.h"
#include <cassert>
#include <memory>
#include <iostream>

std::unique_ptr<Renderer> Renderer::instance = nullptr;

Renderer::Renderer() = default;

Renderer::~Renderer() {

#ifdef MEM
    std::cout << m_Renderer << " D" << std::endl;
#endif
    SDL_DestroyRenderer(m_Renderer);
}

void Renderer::createRenderer(const Window &window) {
    if (m_Renderer != nullptr)
        return;
    m_Renderer = SDL_CreateRenderer(window.getWindow(), -1,
                                    SDL_RENDERER_ACCELERATED |
                                    SDL_RENDERER_PRESENTVSYNC);
#ifdef MEM
    std::cout << m_Renderer << " C" << std::endl;
#endif
    SDL_SetRenderDrawBlendMode(m_Renderer, SDL_BLENDMODE_BLEND);
}

Renderer &Renderer::getInstance() {
    if (instance == nullptr) {
        instance = std::unique_ptr<Renderer>(new Renderer());
    }
    return *instance;
}

void Renderer::render(SDL_Texture *texture, const Rect &sourceRect,
                      const Rect &destinationRect) const {
    assert(m_Renderer != nullptr);

    SDL_Rect src{sourceRect.m_Position.x, sourceRect.m_Position.y,
                 sourceRect.m_Size.x, sourceRect.m_Size.y};

    SDL_Rect dst{destinationRect.m_Position.x, destinationRect.m_Position.y,
                 destinationRect.m_Size.x, destinationRect.m_Size.y};

    SDL_RenderCopy(m_Renderer, texture, &src, &dst);
}

void Renderer::render(SDL_Texture *texture, const Rect &destinationRect) const {
    assert(m_Renderer != nullptr);

    SDL_Rect dst{destinationRect.m_Position.x, destinationRect.m_Position.y,
                 destinationRect.m_Size.x, destinationRect.m_Size.y};

    SDL_RenderCopy(m_Renderer, texture, nullptr, &dst);
}

void Renderer::render(SDL_Texture *texture) const {
    assert(m_Renderer != nullptr);
    SDL_RenderCopy(m_Renderer, texture, nullptr, nullptr);
}

void Renderer::drawRectangle(const Rect &destination, bool fill) const {
    SDL_Rect dest{destination.m_Position.x, destination.m_Position.y,
                  destination.m_Size.x, destination.m_Size.y};
    if (fill)
        SDL_RenderFillRect(m_Renderer, &dest);
    else
        SDL_RenderDrawRect(m_Renderer, &dest);
}

void Renderer::clear() const { SDL_RenderClear(m_Renderer); }

void Renderer::present() const { SDL_RenderPresent(m_Renderer); }

SDL_Texture *Renderer::createTexture(SDL_Surface *surface) const {
#ifdef MEM
    auto p = SDL_CreateTextureFromSurface(m_Renderer, surface);
    std::cout << p << " C" << std::endl;
    return p;
#else
    return SDL_CreateTextureFromSurface(m_Renderer, surface);
#endif
}

void Renderer::selectDrawColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a) const {
    SDL_SetRenderDrawColor(m_Renderer, r, g, b, a);
}