#include "Weapon.h"

void Weapon::renderOnPlayer(GameState &state, Vec position) {
    AnimatedEntity::nextAnimatedRender(playerTexture, position);
}

Weapon::Weapon(Texture texture, Texture playerTexture) :
        PickupEntity(texture, 2, true),
        playerTexture(playerTexture) {
}

void Weapon::onPickup(GameState &state) {
    PickupEntity::onPickup(state);
}
