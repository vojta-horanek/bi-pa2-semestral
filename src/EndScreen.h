#ifndef TPOHB_ENDSCREEN_H
#define TPOHB_ENDSCREEN_H


#include "Screen.h"
#include "Texture.h"

class EndScreen : public Screen {
private:
    Texture background;
    std::unique_ptr<Screen> navigateTo;
    bool hide = false;
public:

    EndScreen(bool won, int width, int height);

    void onEvent(SDL_Event event) override;

    void onRender() override;

    bool clearBackStack() override;

    std::unique_ptr<Screen> getNavigationDestination() override;

};


#endif //TPOHB_ENDSCREEN_H
