#include "BlockEntity.h"

BlockEntity::BlockEntity(Texture texture) : Entity(texture) {
    m_CollisionType = Collision::HARD;
}
