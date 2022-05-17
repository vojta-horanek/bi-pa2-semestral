#ifndef TPOHB_DIALOG_H
#define TPOHB_DIALOG_H

#include "render/Vec.h"
#include <SDL2/SDL_events.h>

class Dialog {

  public:
    virtual void onRender();

    virtual void onEvent(SDL_Event event) = 0;

    bool getVisibility() const;

    virtual ~Dialog() = default;

  protected:
    Dialog(int screenWidth, int screenHeight);

    bool m_isVisible = true;
    int m_ScreenWidth, m_ScreenHeight;
    int m_Width, m_Height;

    Vec getDialogPosition() const;

  private:
    int outlineThickness = 5;
};

#endif // TPOHB_DIALOG_H