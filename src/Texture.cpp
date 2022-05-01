#include "Texture.h"

#include <SDL2/SDL.h>
#include "resources/strings/L10n.h"
#include "Game.h"
#include <iostream>
#include "Constants.h"

SDL_Texture *Texture::create(const std::string &path, bool useWhiteAsAlpha) {
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
    return texture;
}

void Texture::renderBlock(SDL_Texture *texture, Vec position) {

    Vec coords = position.getScaled();

    SDL_Rect dstRect;
    dstRect.w = BLOCK_SIZE * REAL_PIXEL_SIZE;
    dstRect.h = BLOCK_SIZE * REAL_PIXEL_SIZE;
    dstRect.x = coords.x;
    dstRect.y = coords.y;

    SDL_RenderCopy(Game::getRenderer(), texture, nullptr, &dstRect);

}

void Texture::renderBlock(SDL_Texture *texture, Vec position, int xOffset) {

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
