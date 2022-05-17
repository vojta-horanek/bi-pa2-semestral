#ifndef TPOHB_TEXTURE_H
#define TPOHB_TEXTURE_H

#include "Vec.h"
#include <SDL2/SDL.h>
#include <map>
#include <memory>
#include <string>
#include <utility>

class Texture {

  public:
    Texture();

    /**
     * Creates a texture that can be rendered
     * @param path a path to the bmp file
     * @param useWhiteAsAlpha it #FFFFFF in the bmp should be considered as
     * transparent
     */
    explicit Texture(const std::string &path, bool useWhiteAsAlpha = false);

    /**
     * Renders the texture at position with the scale
     * @param position a position of the texture
     * @param scale scale of the rendered texture
     */
    void render(Vec position, int scale = 1) const;

    /**
     * Renders this texture in the whole window
     */
    void renderFullscreen() const;

    /**
     * Renders this texture as a block (16*16 pixels)
     * @param position
     * @param scale
     */
    void renderBlock(Vec position, int scale = 1) const;

    void renderBlockWithOffset(Vec position, int xOffset, int scale = 1) const;

    static void clearStore();

    Vec getSize() const;

    void setAlpha(int alpha) const;

    void setBlendMode(bool blend) const;

  private:
    static std::map<std::pair<std::string, bool>, SDL_Texture *> s_TextureStore;

    SDL_Texture *m_Texture = nullptr;
    Vec m_Size;

    static SDL_Texture *create(const std::string &path, bool useWhiteAsAlpha);

    static Vec querySize(SDL_Texture *texture);
};

#endif // TPOHB_TEXTURE_H
