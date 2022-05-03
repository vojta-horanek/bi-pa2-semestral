#ifndef TPOHB_TEXTURE_H
#define TPOHB_TEXTURE_H

#include <SDL2/SDL.h>
#include <string>
#include <memory>
#include <map>
#include "Vec.h"

class Texture {
private:
    static inline std::map<std::string, SDL_Texture *> textureStore;

    SDL_Texture *texture = nullptr;

    static SDL_Texture *create(const std::string &path, bool useWhiteAsAlpha);

public:
    Texture() = default;

    explicit Texture(const std::string &path, bool useWhiteAsAlpha = false);

    ~Texture();
//
//    Texture(Texture&& other) noexcept;
//    Texture& operator=(Texture&& other) noexcept;
//
//    Texture(const Texture& other) = delete;
//    Texture& operator=(const Texture& other) = delete;

    void renderBlock(Vec position) const;

    void renderBlock(Vec position, int xOffset) const;

    static void clearTextureStore();
};


#endif //TPOHB_TEXTURE_H
