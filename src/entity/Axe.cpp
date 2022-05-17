#include "Axe.h"
#include "../resources/strings/Paths.h"

Axe::Axe()
    : Weapon(Texture(Paths::Bitmaps::axe, true),
             Texture(Paths::Bitmaps::player_axe, true)) {}

int Axe::getDamage() { return 15; }

EntityType Axe::getType() const noexcept { return EntityType::AXE; }