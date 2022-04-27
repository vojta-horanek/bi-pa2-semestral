#ifndef TPOHB_TEXTURE_H
#define TPOHB_TEXTURE_H

#include <SDL2/SDL.h>
#include <string>

class Texture {

private:
    SDL_Texture *texture = nullptr;
public:
    Texture(const std::string &path, SDL_Renderer *renderer);

    SDL_Texture *get();
    ~Texture();
};


#endif //TPOHB_TEXTURE_H
