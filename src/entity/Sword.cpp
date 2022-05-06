#include "Sword.h"
#include "../resources/strings/Paths.h"

Sword::Sword() : Weapon(Texture(Paths::Bitmaps::sword, true),
                        Texture(Paths::Bitmaps::player_sword, true)) {
}

int Sword::getDamage() {
    return 15;
}

void Sword::onPickup(GameState &state) {
    Weapon::onPickup(state);
    state.weapon = std::make_unique<Sword>();
}
