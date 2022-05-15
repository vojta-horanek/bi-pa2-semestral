#ifndef TPOHB_TEXT_H
#define TPOHB_TEXT_H

#include <SDL2/SDL_ttf.h>

#include "Vec.h"
#include <string>
#include <tuple>

class Text {
  public:
    Text(const std::string &text);
    ~Text();

    Text(Text &&other) noexcept;
    Text &operator=(Text &&other) noexcept;

    Text(const Text &other) = delete;
    Text &operator=(const Text &other) = delete;

    void render(Vec position);
    void setColor(int r, int g, int b);

    static bool initTTF();
    static void destroyTTF();

  private:
    const std::string m_Text;
    SDL_Texture *m_FontTexture = nullptr;
    std::tuple<int, int, int> m_Color = std::make_tuple(255, 255, 255);

    static TTF_Font *s_Font;
};

#endif // TPOHB_TEXT_H