#include "Sword.h"
#include "../resources/strings/Paths.h"


bool Sword::onCollision(GameState &state) {
    removeOnNextTurn = true;
    state.weapon = std::make_unique<Sword>();
    return false;
}

Sword::Sword() : Weapon(Texture(Paths::Bitmaps::sword, true),
                        Texture(Paths::Bitmaps::player_sword, true)) {
    damage = 15;
}