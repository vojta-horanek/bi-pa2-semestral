#ifndef TPOHB_RENDERER_H
#define TPOHB_RENDERER_H

#include <SDL2/SDL_render.h>
#include "Window.h"
#include "Rect.h"
#include <memory>

class Renderer {
private:
    static std::unique_ptr<Renderer> instance;
    SDL_Renderer *renderer = nullptr;

    Renderer();

public:
    ~Renderer();

    static Renderer &getInstance();

    void createRenderer(const Window &window);

    void render(SDL_Texture *texture, const Rect &sourceRect, const Rect &destinationRect) const;

    void clear();

    void present();

    SDL_Texture * createTexture(SDL_Surface * surface);
};


#endif //TPOHB_RENDERER_H
