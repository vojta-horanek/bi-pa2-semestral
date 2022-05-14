#include "Bricks.h"
#include "../resources/strings/Paths.h"

Bricks::Bricks() : BlockEntity(Texture(Paths::Bitmaps::bricks)) {}

EntityType Bricks::getType() const noexcept { return EntityType::BRICK; }
