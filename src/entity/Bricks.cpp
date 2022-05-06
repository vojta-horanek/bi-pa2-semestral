#include "Bricks.h"
#include "../resources/strings/Paths.h"

Bricks::Bricks() : Entity(Texture(Paths::Bitmaps::bricks)) {
    collisionType = Collision::HARD;
}
