#include "Sword.h"
#include "../resources/strings/Paths.h"


void Sword::onCollision(GameState &state) {
    removeOnNextTurn = true;
    state.weapon = std::make_unique<Sword>();
}

Sword::Sword() : Weapon(Texture(Paths::Bitmaps::sword, true),
                        Texture(Paths::Bitmaps::player_sword, true)) {
}

int Sword::getDamage() {
    return 15;
}
