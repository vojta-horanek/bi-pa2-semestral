#include "Weapon.h"
#include "../EntityManager.h"

Weapon::Weapon(Texture texture, Texture playerTexture)
    : PickupEntity(texture, 2), playerTexture(playerTexture) {}

void Weapon::renderOnPlayer(GameState &state, Vec position) {
    AnimatedEntity::nextAnimatedRender(playerTexture, position);
}

void Weapon::onPickup(GameState &state) {
    if (state.m_Weapon == nullptr) {
        m_RemoveOnNextTurn = true;
        state.m_Weapon = EntityManager::getWeapon(getType());
    }
}

void Weapon::onFightEnd() {
    m_TextureScale = 1;
    resetAlpha();
    playerTexture.setAlpha(255);
}
