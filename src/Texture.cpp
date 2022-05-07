#include "Texture.h"

#include "Constants.h"
#include "resources/strings/L10n.h"
#include "resources/strings/Paths.h"
#include "Game.h"
#include "Rect.h"
#include "Renderer.h"
#include <SDL2/SDL.h>

std::map<std::pair<std::string, bool>, SDL_Texture *> Texture::textureStore;

Texture::Texture(const std::string &path, bool useWhiteAsAlpha) {
    texture = create(path, useWhiteAsAlpha);
    if (texture == nullptr) {
        // Try to create a bitmap of last resort
        texture = create(Paths::Bitmaps::invalid, true);
    }

    auto size = getSize(texture);
    width = size.first;
    height = size.second;
}

SDL_Texture *Texture::create(const std::string &path, bool useWhiteAsAlpha) {
    // If texture has been saved in the store, retrieve it
    auto existing = textureStore.find(std::make_pair(path, useWhiteAsAlpha));
    if (existing != textureStore.end()) return existing->second;

    // Otherwise, create the texture
    SDL_Surface *surface = SDL_LoadBMP(path.c_str());
    if (surface == nullptr) {
        SDL_Log(L10n::cannotLoadBitmap, path.c_str(), SDL_GetError());
        return nullptr;
    }

    if (useWhiteAsAlpha) {
        SDL_SetColorKey(surface, SDL_GetColorKey(surface, nullptr), SDL_MapRGB(surface->format, 255, 255, 255));
    }

    SDL_Texture *texture = Renderer::getInstance().createTexture(surface);

    if (texture == nullptr) {
        SDL_Log(L10n::cannotLoadBitmap, path.c_str(), SDL_GetError());
        return nullptr;
    }
    SDL_FreeSurface(surface);

    textureStore[std::make_pair(path, useWhiteAsAlpha)] = texture;

    return texture;
}

void Texture::renderBlock(Vec position, int scale) const {
    Texture::renderBlockWithOffset(position, 0, scale);
}

void Texture::renderBlockWithOffset(Vec position, int xOffset, int scale) const {

    if (texture == nullptr) return;

    Rect dstRect{
            position.getScaled(),
            Vec(BLOCK_SIZE * REAL_PIXEL_SIZE, BLOCK_SIZE * REAL_PIXEL_SIZE) * scale
    };

    Rect srcRect{
            Vec(xOffset * BLOCK_SIZE, 0),
            Vec(BLOCK_SIZE, BLOCK_SIZE * REAL_PIXEL_SIZE)
    };

    Renderer::getInstance().render(texture, srcRect, dstRect);
}


void Texture::render(Vec position, int scale) const {

    if (texture == nullptr) return;

    SDL_Point size;
    SDL_QueryTexture(texture, nullptr, nullptr, &size.x, &size.y);

    Rect dstRect{
            position,
            Vec(size.x, size.y) * scale
    };

    Renderer::getInstance().render(texture, dstRect);
}

void Texture::clearStore() {
    for (const auto &item: textureStore)
        if (item.second != nullptr) SDL_DestroyTexture(item.second);

    textureStore.clear();
}

void Texture::renderFullscreen() const {
    if (texture == nullptr) return;

    Renderer::getInstance().render(texture);
}

std::pair<int, int> Texture::getSize(SDL_Texture * texture) {
    int width, height;
    SDL_QueryTexture(texture, nullptr, nullptr, &width, &height);
    return {width, height};
}

int Texture::getWidth() const {
    return width;
}

int Texture::getHeight() const {
    return height;
}
