#ifndef TPOHB_SCREEN_H
#define TPOHB_SCREEN_H


#include <SDL_events.h>
#include <memory>

class Screen {
protected:
    Screen(int width, int height);

    int width, height;
public:

    bool applicationQuitRequested = false;

    virtual ~Screen();

    void onLoop();

    virtual void onRender() = 0;

    virtual void onEvent(SDL_Event event) = 0;

    virtual std::unique_ptr<Screen> getNavigationDestination() = 0;

    virtual bool popSelf() = 0;

    virtual bool clearBackStack() = 0;
};


#endif //TPOHB_SCREEN_H
