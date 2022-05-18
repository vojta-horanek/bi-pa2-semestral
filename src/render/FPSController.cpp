#include "FPSController.h"

void FPSController::renderStart() { s_StartTicks = SDL_GetTicks(); }

void FPSController::renderEnd() {
    Uint32 endTicks = SDL_GetTicks() - s_StartTicks;
    if (s_DelayTicks >= endTicks) {
        SDL_Delay(s_DelayTicks - endTicks);
    }
}
