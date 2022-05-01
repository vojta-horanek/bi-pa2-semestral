#include "Axe.h"

bool Axe::onCollision(GameState &state) {
    removeOnNextRender = true;
    state.weapon = std::make_unique<Axe>();
    return false;
}
