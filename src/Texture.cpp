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


Vec Texture::getAdjustedSize(SDL_Texture *texture) {
    Vec size;
    SDL_QueryTexture(texture, nullptr, nullptr, &size.x, &size.y);
    return size * REAL_PIXEL_SIZE;
}
