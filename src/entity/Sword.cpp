#include "Sword.h"

bool Sword::onCollision(GameState &state) {
    removeOnNextTurn = true;
    state.weapon = std::make_unique<Sword>();
    return false;
}
