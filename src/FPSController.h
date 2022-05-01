#ifndef TPOHB_FPSCONTROLLER_H
#define TPOHB_FPSCONTROLLER_H

#include <SDL2/SDL.h>

class FPSController {

    static const Uint32 FPS = 60;
    static const Uint32 delayTicks = 1000 / FPS;
    inline static Uint32 startTicks;

public:
    static void renderStart();
    static void renderEnd();
};


#endif //TPOHB_FPSCONTROLLER_H
