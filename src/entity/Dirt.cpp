#include "Dirt.h"
#include "../resources/strings/Paths.h"

Dirt::Dirt() : Entity(Texture(Paths::Bitmaps::dirt)) {}

EntityType Dirt::getType() const noexcept { return EntityType::DIRT; }
