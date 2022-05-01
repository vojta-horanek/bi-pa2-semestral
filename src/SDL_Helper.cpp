#include "SDL_Helper.h"

#include <SDL2/SDL.h>

void SDL_Deleter::operator()(SDL_Texture *p) const {
    SDL_DestroyTexture(p);
}

void SDL_Deleter::operator()(SDL_Renderer *p) const {
    SDL_DestroyRenderer(p);
}

void SDL_Deleter::operator()(SDL_Window *p) const {
    SDL_DestroyWindow(p);
}
