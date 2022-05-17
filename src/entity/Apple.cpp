#include "Apple.h"
#include "../resources/strings/Paths.h"

Apple::Apple() : PickupEntity(Texture(Paths::Bitmaps::apple, true)) {}

EntityType Apple::getType() const noexcept { return EntityType::APPLE; }