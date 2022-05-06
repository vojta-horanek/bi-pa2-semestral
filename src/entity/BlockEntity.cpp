#include "BlockEntity.h"

BlockEntity::BlockEntity(Texture texture) : Entity(texture) {
    collisionType = Collision::HARD;
}
