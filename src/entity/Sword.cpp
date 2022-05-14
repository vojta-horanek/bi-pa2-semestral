#include "Sword.h"
#include "../resources/strings/Paths.h"

Sword::Sword()
    : Weapon(Texture(Paths::Bitmaps::sword, true),
             Texture(Paths::Bitmaps::player_sword, true)) {}

int Sword::getDamage() { return 25; }

void Sword::onPickup(GameState &state) {
    Weapon::onPickup(state);
    state.weapon = std::make_unique<Sword>();
}

EntityType Sword::getType() const noexcept { return EntityType::SWORD; }