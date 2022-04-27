#include "Texture.h"

#include <SDL2/SDL.h>
#include "resources/strings/L10n.h"
#include <cassert>
#include <iostream>

Texture::Texture(const std::string &path, SDL_Renderer *renderer) {
    SDL_Surface *surface = SDL_LoadBMP(path.c_str());
    if (surface == nullptr) {
        SDL_Log(L10n::cannotLoadBitmap, SDL_GetError());
        return;
    }
    texture = SDL_CreateTextureFromSurface(renderer, surface);
    if (texture == nullptr) {
        SDL_Log(L10n::cannotLoadBitmap, SDL_GetError());
        return;
    }
    SDL_FreeSurface(surface);
}

SDL_Texture *Texture::get() {
    assert(texture != nullptr);
    return texture;
}

Texture::~Texture() {
    SDL_DestroyTexture(texture);
    texture = nullptr;
}