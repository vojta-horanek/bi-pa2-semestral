#ifndef TPOHB_RENDERER_H
#define TPOHB_RENDERER_H

#include "../Window.h"
#include "Rect.h"
#include <SDL2/SDL_render.h>
#include <memory>

class Renderer {
    
public:
    ~Renderer();

    static Renderer &getInstance();

    void createRenderer(const Window &window);

    void render(SDL_Texture *texture, const Rect &sourceRect,
                const Rect &destinationRect) const;

    void render(SDL_Texture *texture, const Rect &destinationRect) const;

    void render(SDL_Texture *texture) const;

    void selectDrawColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a) const;

    void drawRectangle(const Rect &destination, bool fill) const;

    void clear() const;

    void present() const;

    SDL_Texture *createTexture(SDL_Surface *surface) const;

private:
    static std::unique_ptr<Renderer> instance;
    SDL_Renderer *m_Renderer = nullptr;

    Renderer();
};

#endif // TPOHB_RENDERER_H
