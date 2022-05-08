#include "Axe.h"
#include "../resources/strings/Paths.h"

Axe::Axe() : Weapon(Texture(Paths::Bitmaps::axe, true),
                    Texture(Paths::Bitmaps::player_axe, true)) {
}

int Axe::getDamage() {
    return 15;
}

void Axe::onPickup(GameState &state) {
    Weapon::onPickup(state);
    state.weapon = std::make_unique<Axe>();
}
