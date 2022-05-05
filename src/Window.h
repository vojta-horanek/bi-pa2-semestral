#ifndef TPOHB_WINDOW_H
#define TPOHB_WINDOW_H

#include <SDL2/SDL.h>
#include <string>
#include "Constants.h"

class Window {
private:
    SDL_Window *window = nullptr;
    SDL_Renderer *renderer = nullptr;
public:
    explicit Window(const std::string &title);

    ~Window();

    void createRenderer();

    void show();

    SDL_Renderer *getRenderer() const;
};


#endif //TPOHB_WINDOW_H
