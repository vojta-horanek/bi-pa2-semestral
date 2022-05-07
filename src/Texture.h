#ifndef TPOHB_TEXTURE_H
#define TPOHB_TEXTURE_H

#include <SDL2/SDL.h>
#include <string>
#include <memory>
#include <map>
#include <utility>
#include "Vec.h"

class Texture {
private:
    static std::map<std::pair<std::string, bool>, SDL_Texture *> textureStore;

    SDL_Texture *texture = nullptr;
    int width, height;

    static SDL_Texture *create(const std::string &path, bool useWhiteAsAlpha);

    static std::pair<int, int> getSize(SDL_Texture *texture);

public:
    Texture() = default;

    explicit Texture(const std::string &path, bool useWhiteAsAlpha = false);

    void render(Vec position, int scale = 1) const;

    void renderFullscreen() const;

    void renderBlock(Vec position, int scale = 1) const;

    void renderBlockWithOffset(Vec position, int xOffset, int scale = 1) const;

    static void clearStore();

    int getWidth() const;

    int getHeight() const;
};


#endif //TPOHB_TEXTURE_H
