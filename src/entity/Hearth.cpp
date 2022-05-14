#include "Hearth.h"

#include "../resources/strings/Paths.h"

Hearth::Hearth() : Entity(Texture(Paths::Bitmaps::hearth, true)) {}

EntityType Hearth::getType() const noexcept { return EntityType::HEARTH; }
