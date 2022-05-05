#include "Renderer.h"
#include <memory>
#include <cassert>

std::unique_ptr<Renderer> Renderer::instance = nullptr;

Renderer::Renderer() = default;

Renderer::~Renderer() {
    SDL_DestroyRenderer(renderer);
}

void Renderer::createRenderer(const Window &window) {
    if (renderer != nullptr) return;
    renderer = SDL_CreateRenderer(window.getWindow(), -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
}

Renderer &Renderer::getInstance() {
    if (instance == nullptr) {
        instance = std::unique_ptr<Renderer>(new Renderer());
    }
    return *instance;
}

void Renderer::render(SDL_Texture *texture, const Rect &sourceRect, const Rect &destinationRect) const {
    assert(renderer != nullptr);

    SDL_Rect src{
            sourceRect.position.x,
            sourceRect.position.y,
            sourceRect.size.x,
            sourceRect.size.y
    };

    SDL_Rect dst{
            destinationRect.position.x,
            destinationRect.position.y,
            destinationRect.size.x,
            destinationRect.size.y
    };

    SDL_RenderCopy(renderer, texture, &src, &dst);

}

void Renderer::clear() {
    SDL_RenderClear(renderer);
}

void Renderer::present() {
    SDL_RenderPresent(renderer);
}

SDL_Texture *Renderer::createTexture(SDL_Surface *surface) {
    return SDL_CreateTextureFromSurface(renderer, surface);
}
