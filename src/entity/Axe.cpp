#include "Axe.h"
#include "../resources/strings/Paths.h"

Axe::Axe() : Weapon(Texture(Paths::Bitmaps::axe, true),
                    Texture(Paths::Bitmaps::player_axe, true)) {
    damage = 10;
}

bool Axe::onCollision(GameState &state) {
    removeOnNextTurn = true;
    state.weapon = std::make_unique<Axe>();
    return false;
}
