#include "Weapon.h"

void Weapon::renderOnPlayer(GameState &state, Vec position) {
    AnimatedEntity::nextAnimatedRender(playerTexture, position);
}

Weapon::Weapon(Texture texture, Texture playerTexture) :
        AnimatedEntity(texture, 2, true),
        playerTexture(playerTexture) {
    collisionType = Collision::SOFT;
}