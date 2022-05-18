#include "GoldenApple.h"
#include "../resources/strings/Paths.h"

GoldenApple::GoldenApple()
    : PickupEntity(Texture(Paths::Bitmaps::golden_apple, true)) {}

EntityType GoldenApple::getType() const noexcept {
    return EntityType::GOLDEN_APPLE;
}

void GoldenApple::onPickup(GameState &state) {
    state.m_Won = true;
    PickupEntity::onPickup(state);
}