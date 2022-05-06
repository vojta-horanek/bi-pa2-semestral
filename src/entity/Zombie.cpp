#include "Zombie.h"
#include "../resources/strings/Paths.h"

Zombie::Zombie() : Monster(Texture(Paths::Bitmaps::zombie)) {
    currentHealth = Zombie::getMaxHealth();
}

int Zombie::getDamage() {
    return 10;
}

int Zombie::getMaxHealth() {
    return 100;
}
