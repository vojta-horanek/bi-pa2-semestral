#include "Sword.h"

bool Sword::onCollision(GameState &state) {
    removeOnNextRender = true;
    state.weapon = std::make_unique<Sword>();
    return false;
}
