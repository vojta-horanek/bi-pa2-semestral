#include "FPSController.h"

void FPSController::renderStart() { startTicks = SDL_GetTicks(); }

void FPSController::renderEnd() {
    Uint32 endTicks = SDL_GetTicks() - startTicks;
    if (delayTicks >= endTicks) {
        SDL_Delay(delayTicks - endTicks);
    }
}
