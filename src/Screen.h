#ifndef TPOHB_SCREEN_H
#define TPOHB_SCREEN_H


#include <SDL_events.h>
#include <memory>

class Screen {
protected:
    Screen(int width, int height);

    int width, height;

    virtual bool shouldContinue() = 0;

public:
    virtual ~Screen();

    bool loop();

    virtual void onRender() = 0;

    virtual void onEvent(SDL_Event event) = 0;

    virtual std::unique_ptr<Screen> getNextScreen() = 0;
};


#endif //TPOHB_SCREEN_H
