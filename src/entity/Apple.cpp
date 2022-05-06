#include "Apple.h"
#include "../resources/strings/Paths.h"

Apple::Apple() : Entity(Texture(Paths::Bitmaps::apple, true)) {
    collisionType = Collision::SOFT;
}

void Apple::onCollision(GameState &state) {
    removeOnNextTurn = true;
    state.inventory.emplace_back(new Apple());
}
