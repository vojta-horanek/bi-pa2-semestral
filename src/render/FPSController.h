#ifndef TPOHB_FPSCONTROLLER_H
#define TPOHB_FPSCONTROLLER_H

#include <SDL2/SDL.h>

/**
 * Class used for limiting the FPS count.
 */
class FPSController {

public:
    static void renderStart();

    static void renderEnd();

private:
    static const Uint32 FPS = 60;
    static const Uint32 s_DelayTicks = 1000 / FPS;
    inline static Uint32 s_StartTicks;
};

#endif // TPOHB_FPSCONTROLLER_H
