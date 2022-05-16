#ifndef TPOHB_TEXT_H
#define TPOHB_TEXT_H

#include <SDL2/SDL_ttf.h>

#include "Vec.h"
#include <map>
#include <string>
#include <tuple>

class Text {
  public:
    Text();
    explicit Text(const std::string &text);
    Text(const std::string &text, int fontSize);
    ~Text();

    Text(Text &&other) noexcept;
    Text &operator=(Text &&other) noexcept;

    Text(const Text &other) = delete;
    Text &operator=(const Text &other) = delete;

    void render(Vec position) const;
    void setText(const std::string &text);
    void setColor(unsigned char r, unsigned char g, unsigned char b);
    void setFontSize(int fontSize);
    void setWrapWidth(int wrapWidth);

    Vec getBoxSize() const;
    int getFontSize() const;

    static bool initTTF();
    static void destroyTTF();

  private:
    std::string m_Text;
    SDL_Texture *m_FontTexture = nullptr;
    SDL_Color m_Color = {255, 255, 255, 255};
    Vec m_BoxSize;
    int m_FontSize;
    int m_WrapWidth = 0;
    SDL_Texture *createTexture();
    TTF_Font *getFont();
    void swapTexture();

    static std::map<int, TTF_Font *> s_Fonts;
};

#endif // TPOHB_TEXT_H