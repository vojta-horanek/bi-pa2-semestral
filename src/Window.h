#ifndef TPOHB_WINDOW_H
#define TPOHB_WINDOW_H

#include "Constants.h"
#include "Vec.h"
#include <SDL2/SDL.h>
#include <string>

class Window {
  private:
    SDL_Window *window = nullptr;

    Vec m_Size;

  public:
    explicit Window(const std::string &title);

    ~Window();

    void show();

    SDL_Window *getWindow() const;

    Vec getSize() const;
};

#endif // TPOHB_WINDOW_H
