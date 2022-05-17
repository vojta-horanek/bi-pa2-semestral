#include "Hearth.h"

#include "../resources/strings/Paths.h"

Hearth::Hearth() : PickupEntity(Texture(Paths::Bitmaps::hearth, true)) {}

EntityType Hearth::getType() const noexcept { return EntityType::HEARTH; }

void Hearth::onPickup(GameState &state) {
    if (state.m_PlayerCurrentHealth < state.m_PlayerMaxHealth)
        state.m_PlayerCurrentHealth += 50;
    if (state.m_PlayerCurrentHealth > state.m_PlayerMaxHealth)
        state.m_PlayerCurrentHealth = state.m_PlayerMaxHealth;
    m_RemoveOnNextTurn = true;
}
