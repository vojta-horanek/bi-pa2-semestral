#include "Sword.h"
#include "../resources/strings/Paths.h"

Sword::Sword()
    : Weapon(Texture(Paths::Bitmaps::sword, true),
             Texture(Paths::Bitmaps::player_sword, true)) {}

int Sword::getDamage() { return 25; }

EntityType Sword::getType() const noexcept { return EntityType::SWORD; }