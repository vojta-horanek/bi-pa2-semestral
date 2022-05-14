#include "Grass.h"
#include "../resources/strings/Paths.h"

Grass::Grass() : Entity(Texture(Paths::Bitmaps::grass)) {}

EntityType Grass::getType() const noexcept { return EntityType::GRASS; }
