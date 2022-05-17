#include "Weapon.h"
#include "../EntityManager.h"

Weapon::Weapon(Texture texture, Texture playerTexture)
    : PickupEntity(texture, 2), playerTexture(playerTexture) {}

Weapon::~Weapon() = default;

void Weapon::renderOnPlayer(GameState &state, Vec position) {
    AnimatedEntity::nextAnimatedRender(playerTexture, position);
}

void Weapon::onPickup(GameState &state) {
    if (state.weapon == nullptr) {
        PickupEntity::onPickup(state);
        state.weapon = EntityManager::getWeapon(getType());
    }
}

void Weapon::onFightEnd() {
    scale = 1;
    resetAlpha();
    playerTexture.setAlpha(255);
}
