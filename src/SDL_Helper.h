#ifndef TPOHB_SDL_HELPER_H
#define TPOHB_SDL_HELPER_H

#include <SDL2/SDL.h>

struct SDL_Deleter {
    void operator()(SDL_Window *p) const;

    void operator()(SDL_Renderer *p) const;

    void operator()(SDL_Texture *p) const;
};

#endif //TPOHB_SDL_HELPER_H
