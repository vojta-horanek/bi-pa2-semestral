#include "Weapon.h"

void Weapon::renderOnPlayer(GameState &state, Vec position) {
    AnimatedEntity::nextAnimatedRender(playerTexture, position);
}
