#include "PickupEntity.h"

PickupEntity::PickupEntity(Texture texture, int frameCount, bool synchronized,
                           int speed)
    : AnimatedEntity(texture, frameCount, synchronized, speed) {
    collisionType = Collision::SOFT;
}

PickupEntity::PickupEntity(Texture texture)
    : PickupEntity(texture, 1, true, 0) {}

void PickupEntity::onPickup(GameState &state) { removeOnNextTurn = true; }

void PickupEntity::onCollision(GameState &state) {
    AnimatedEntity::onCollision(state);
    onPickup(state);
}
