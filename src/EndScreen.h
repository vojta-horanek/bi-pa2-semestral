#ifndef TPOHB_ENDSCREEN_H
#define TPOHB_ENDSCREEN_H

#include "Screen.h"
#include "render/Texture.h"

class EndScreen : public Screen {
  private:
    Texture m_BackgroundTexture;
    bool m_IsVisible = true;

  public:
    EndScreen(bool hasWon, int screenWidth, int screenHeight);

    void onEvent(SDL_Event event) override;

    void onRender() override;

    bool shouldClearBackStack() override;
};

#endif // TPOHB_ENDSCREEN_H
