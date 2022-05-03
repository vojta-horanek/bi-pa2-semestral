#ifndef TPOHB_TEXTURE_H
#define TPOHB_TEXTURE_H

#include <SDL2/SDL.h>
#include <string>
#include <memory>
#include <map>
#include "Vec.h"

class Texture {
private:
    static std::map<std::pair<std::string, bool>, SDL_Texture *> textureStore;

    SDL_Texture *texture = nullptr;

    static SDL_Texture *create(const std::string &path, bool useWhiteAsAlpha);

public:
    Texture() = default;

    explicit Texture(const std::string &path, bool useWhiteAsAlpha = false);

    void renderBlock(Vec position) const;

    void renderBlock(Vec position, int xOffset) const;

    static void clearStore();
};


#endif //TPOHB_TEXTURE_H
