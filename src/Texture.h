#ifndef TPOHB_TEXTURE_H
#define TPOHB_TEXTURE_H

#include <SDL2/SDL.h>
#include <string>
#include <memory>
#include "Vec.h"

class Texture {
public:
    static SDL_Texture * create(const std::string &path, bool useWhiteAsAlpha = false);
    static Vec getAdjustedSize(SDL_Texture * texture);
};


#endif //TPOHB_TEXTURE_H
