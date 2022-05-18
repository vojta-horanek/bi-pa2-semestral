#include "Dirt.h"

#include "../render/Texture.h"
#include "../resources/strings/Paths.h"

Dirt::Dirt() : BlockEntity(Texture(Paths::Bitmaps::dirt)) {}

EntityType Dirt::getType() const noexcept { return EntityType::DIRT; }
