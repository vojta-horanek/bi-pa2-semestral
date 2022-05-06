#include "Zombie.h"
#include "../resources/strings/Paths.h"

Zombie::Zombie() : Monster(Texture(Paths::Bitmaps::zombie, true)) {
    currentHealth = Zombie::getMaxHealth();
}

int Zombie::getDamage() {
    return 10;
}

int Zombie::getMaxHealth() {
    return 100;
}

void Zombie::onFight(GameState &state) {
    state.fight = std::make_unique<Zombie>();
}
