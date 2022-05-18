#include "Apple.h"
#include "../resources/strings/Paths.h"

Apple::Apple() : PickupEntity(Texture(Paths::Bitmaps::apple, true)) {}

EntityType Apple::getType() const noexcept { return EntityType::APPLE; }

void Apple::onPickup(GameState &state) {
    state.m_PlayerDefaultDamage += 4;
    PickupEntity::onPickup(state);
}
