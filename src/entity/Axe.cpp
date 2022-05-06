#include "Axe.h"
#include "../resources/strings/Paths.h"

Axe::Axe() : Weapon(Texture(Paths::Bitmaps::axe, true),
                    Texture(Paths::Bitmaps::player_axe, true)) {
}

void Axe::onCollision(GameState &state) {
    removeOnNextTurn = true;
    state.weapon = std::make_unique<Axe>();
}

int Axe::getDamage() {
    return 10;
}
