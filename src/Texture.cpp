#include "Texture.h"

#include "Constants.h"
#include "resources/strings/L10n.h"
#include "Game.h"
#include <SDL2/SDL.h>
#include <iostream>

std::map<std::pair<std::string, bool>, SDL_Texture *> Texture::textureStore;

Texture::Texture(const std::string &path, bool useWhiteAsAlpha) {
    texture = create(path, useWhiteAsAlpha);
    if (texture == nullptr) {
        // Try to create a bitmap of last resort
        texture = create("resources/bitmaps/invalid.bmp", true);
    }
}

SDL_Texture *Texture::create(const std::string &path, bool useWhiteAsAlpha) {
    // If texture has been saved in the store, retrieve it
    auto existing = textureStore.find(std::make_pair(path, useWhiteAsAlpha));
    if (existing != textureStore.end()) return existing->second;

    // Otherwise, create the texture
    SDL_Surface *surface = SDL_LoadBMP(path.c_str());
    if (surface == nullptr) {
        SDL_Log(L10n::cannotLoadBitmap, SDL_GetError());
        return nullptr;
    }

    if (useWhiteAsAlpha) {
        SDL_SetColorKey(surface, SDL_GetColorKey(surface, nullptr), SDL_MapRGB(surface->format, 255, 255, 255));
    }

    SDL_Texture *texture = SDL_CreateTextureFromSurface(Game::getRenderer(), surface);
    if (texture == nullptr) {
        SDL_Log(L10n::cannotLoadBitmap, SDL_GetError());
        return nullptr;
    }
    SDL_FreeSurface(surface);

    textureStore[std::make_pair(path, useWhiteAsAlpha)] = texture;

    return texture;
}

void Texture::renderBlock(Vec position) const {
    Texture::renderBlock(position, 0);
}

void Texture::renderBlock(Vec position, int xOffset) const {

    if (texture == nullptr) return;

    Vec coords = position.getScaled();

    SDL_Rect dstRect;
    dstRect.w = BLOCK_SIZE * REAL_PIXEL_SIZE;
    dstRect.h = BLOCK_SIZE * REAL_PIXEL_SIZE;
    dstRect.x = coords.x;
    dstRect.y = coords.y;

    SDL_Rect srcRect;
    srcRect.w = BLOCK_SIZE;
    srcRect.h = BLOCK_SIZE * REAL_PIXEL_SIZE;
    srcRect.x = xOffset * BLOCK_SIZE;
    srcRect.y = 0;

    SDL_RenderCopy(Game::getRenderer(), texture, &srcRect, &dstRect);

}

void Texture::clearStore() {
    for (const auto &item: textureStore)
        if (item.second != nullptr) SDL_DestroyTexture(item.second);

    textureStore.clear();
}
