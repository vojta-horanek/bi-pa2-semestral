#ifndef TPOHB_WINDOW_H
#define TPOHB_WINDOW_H

#include <SDL2/SDL.h>
#include <string>
#include "Constants.h"

class Window {
private:
    SDL_Window *window = nullptr;
public:
    explicit Window(const std::string &title);

    ~Window();

    void show();

    SDL_Window * getWindow() const;
};


#endif //TPOHB_WINDOW_H
