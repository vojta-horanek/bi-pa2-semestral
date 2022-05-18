#ifndef TPOHB_WINDOW_H
#define TPOHB_WINDOW_H

#include "render/Vec.h"
#include "utils/Constants.h"
#include <SDL2/SDL.h>
#include <string>

class Window {
  public:
    explicit Window(const std::string &title);

    ~Window();

    void show();

    SDL_Window *getWindow() const;

    Vec getSize() const;

  private:
    SDL_Window *m_Window = nullptr;

    Vec m_Size;
};

#endif // TPOHB_WINDOW_H
