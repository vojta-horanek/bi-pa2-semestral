#include "PickupEntity.h"
#include "../EntityManager.h"

PickupEntity::PickupEntity(Texture texture, int frameCount, bool synchronized,
                           int speed)
    : AnimatedEntity(texture, frameCount, synchronized, speed) {
    m_CollisionType = Collision::SOFT;
}

PickupEntity::PickupEntity(Texture texture)
    : PickupEntity(texture, 1, true, 0) {}

void PickupEntity::onPickup(GameState &state) {
    state.m_Inventory.emplace_back(
        std::move(EntityManager::getPickupEntity(getType())));
    m_RemoveOnNextTurn = true;
}

void PickupEntity::onCollision(GameState &state) {
    AnimatedEntity::onCollision(state);
    onPickup(state);
}
