#include "Apple.h"
#include "../resources/strings/Paths.h"

Apple::Apple() : PickupEntity(Texture(Paths::Bitmaps::apple, true)) {}

void Apple::onPickup(GameState &state) {
    PickupEntity::onPickup(state);
    state.inventory.emplace_back(new Apple());
}

EntityType Apple::getType() const noexcept { return EntityType::APPLE; }