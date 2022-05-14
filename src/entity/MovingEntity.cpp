#include "MovingEntity.h"

MovingEntity::MovingEntity(Texture texture, int animationFrameCount,
                           bool animationSynchronized, int animationSpeed)
    : AnimatedEntity(texture, animationFrameCount, animationSynchronized,
                     animationSpeed) {}

MovingEntity::MovingEntity(Texture texture)
    : AnimatedEntity(texture, 1, true, 0) {}

void MovingEntity::onTurn(GameState &state, MapSection &section) {}
