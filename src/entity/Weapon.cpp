#include "Weapon.h"

Weapon::Weapon(Texture texture, Texture playerTexture)
    : PickupEntity(texture, 2), playerTexture(playerTexture) {}

void Weapon::renderOnPlayer(GameState &state, Vec position) {
    AnimatedEntity::nextAnimatedRender(playerTexture, position);
}

void Weapon::onPickup(GameState &state) { PickupEntity::onPickup(state); }


void Weapon::onFightEnd() {
    scale = 1;
    resetAlpha();
    playerTexture.setAlpha(255);
}
