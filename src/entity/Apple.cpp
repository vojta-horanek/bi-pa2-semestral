#include "Apple.h"
#include "../resources/strings/Paths.h"

Apple::Apple() : Entity(Texture(Paths::Bitmaps::apple, true)) {
    hasCollision = true;
}

bool Apple::onCollision(GameState &state) {
    removeOnNextTurn = true;
    state.inventory.emplace_back(new Apple());
    return false;
}
