#include "Zombie.h"
#include "../resources/strings/Paths.h"

Zombie::Zombie() : Monster(Texture(Paths::Bitmaps::zombie, true), 4, false, 7) {
    currentHealth = Zombie::getMaxHealth();
}

int Zombie::getDamage() { return 10; }

int Zombie::getMaxHealth() { return 100; }

EntityType Zombie::getType() const noexcept { return EntityType::ZOMBIE; }
