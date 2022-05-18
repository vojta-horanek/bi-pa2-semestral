#include "Texture.h"

#include "../Game.h"
#include "../resources/strings/L10n.h"
#include "../resources/strings/Paths.h"
#include "../utils/Constants.h"
#include "Rect.h"
#include "Renderer.h"
#include <SDL2/SDL.h>
#include <iostream>

std::map<std::pair<std::string, bool>, SDL_Texture *> Texture::s_TextureStore;

Texture::Texture() = default;

Texture::Texture(const std::string &path, bool useWhiteAsAlpha) {
    m_Texture = create(path, useWhiteAsAlpha);
    if (m_Texture == nullptr) {
        // Try to create a bitmap of last resort
        m_Texture = create(Paths::Bitmaps::invalid, true);
    }

    m_Size = querySize(m_Texture);
}

SDL_Texture *Texture::create(const std::string &path, bool useWhiteAsAlpha) {
    // If m_Texture has been saved in the store, retrieve it
    auto existing = s_TextureStore.find(std::make_pair(path, useWhiteAsAlpha));
    if (existing != s_TextureStore.end())
        return existing->second;

    // Otherwise, create the m_Texture
    SDL_Surface *surface = SDL_LoadBMP(path.c_str());

    if (surface == nullptr) {
        std::cerr << L10n::cannotLoadBitmap << " " << path.c_str() << " "
                  << SDL_GetError() << std::endl;
        return nullptr;
    }
#ifdef MEM
    std::cout << surface << " C" << std::endl;
#endif

    if (useWhiteAsAlpha) {
        SDL_SetColorKey(surface, SDL_GetColorKey(surface, nullptr),
                        SDL_MapRGB(surface->format, 255, 255, 255));
    }

    SDL_Texture *texture = Renderer::getInstance().createTexture(surface);

    if (texture == nullptr) {
        std::cerr << L10n::cannotLoadBitmap << " " << path.c_str() << " "
                  << SDL_GetError() << std::endl;
        return nullptr;
    }
    SDL_FreeSurface(surface);
#ifdef MEM
    std::cout << surface << " D" << std::endl;
#endif

    s_TextureStore[std::make_pair(path, useWhiteAsAlpha)] = texture;

    return texture;
}

void Texture::renderBlock(Vec position, int scale) const {
    Texture::renderBlockWithOffset(position, 0, scale);
}

void Texture::renderBlockWithOffset(Vec position, int xOffset,
                                    int scale) const {

    if (m_Texture == nullptr)
        return;

    Rect dstRect{position.getScaled(), Vec(BLOCK_PIXELS, BLOCK_PIXELS) * scale};

    Rect srcRect{Vec(xOffset * BLOCK_SIZE, 0), Vec(BLOCK_SIZE, BLOCK_PIXELS)};

    Renderer::getInstance().render(m_Texture, srcRect, dstRect);
}

void Texture::render(Vec position, int scale) const {

    if (m_Texture == nullptr)
        return;

    Rect dstRect{position, m_Size * scale};

    Renderer::getInstance().render(m_Texture, dstRect);
}

void Texture::clearStore() {
    for (const auto &item: s_TextureStore)
        if (item.second != nullptr) {
#ifdef MEM
            std::cout << item.second << " D" << std::endl;
#endif
            SDL_DestroyTexture(item.second);
        }

    s_TextureStore.clear();
}

void Texture::renderFullscreen() const {
    if (m_Texture == nullptr)
        return;

    Renderer::getInstance().render(m_Texture);
}

Vec Texture::querySize(SDL_Texture *texture) {
    int width, height;
    SDL_QueryTexture(texture, nullptr, nullptr, &width, &height);
    return {width, height};
}

Vec Texture::getSize() const { return m_Size; }

void Texture::setAlpha(int alpha) const {
    if (alpha < 0 || alpha > 255)
        return;
    SDL_SetTextureAlphaMod(m_Texture, alpha);
}

void Texture::setBlendMode(bool blend) const {
    if (blend) {
        SDL_SetTextureBlendMode(m_Texture, SDL_BLENDMODE_BLEND);
    } else {
        SDL_SetTextureBlendMode(m_Texture, SDL_BLENDMODE_NONE);
    }
}
