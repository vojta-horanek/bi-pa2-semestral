#ifndef TPOHB_SCREEN_H
#define TPOHB_SCREEN_H

#include <SDL_events.h>
#include <memory>
#include <string>
#include <vector>

class Screen {
  protected:
    Screen(int width, int height);

    std::vector<std::string> args;

    std::unique_ptr<Screen> navigationDestination = nullptr;

    int width, height;

  public:
    bool applicationQuitRequested = false;

    virtual ~Screen();

    void onLoop();

    virtual void onRender() = 0;

    virtual void onEvent(SDL_Event event) = 0;

    std::unique_ptr<Screen> getNavigationDestination();

    virtual bool popSelf();

    virtual bool clearBackStack();

    virtual void onResume();

    virtual void onCreate();

    void setArgs(const std::vector<std::string> &programArgs);
};

#endif // TPOHB_SCREEN_H
