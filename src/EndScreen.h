#ifndef TPOHB_ENDSCREEN_H
#define TPOHB_ENDSCREEN_H


#include "Screen.h"
#include "Texture.h"

class EndScreen : public Screen {
private:
    Texture background;
    bool hide = false;
public:

    EndScreen(bool won, int width, int height);

    void onEvent(SDL_Event event) override;

    void onRender() override;

    bool clearBackStack() override;

};


#endif //TPOHB_ENDSCREEN_H
