#include "Axe.h"

bool Axe::onCollision(GameState &state) {
    removeOnNextTurn = true;
    state.weapon = std::make_unique<Axe>();
    return false;
}
