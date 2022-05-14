#include "Zombie.h"
#include "../resources/strings/Paths.h"

Zombie::Zombie() : Monster(Texture(Paths::Bitmaps::zombie, true), 4, false, 7) {
    currentHealth = Zombie::getMaxHealth();
}

int Zombie::getDamage() { return 10; }

int Zombie::getMaxHealth() { return 100; }

void Zombie::onFight(GameState &state) {
    if (state.fight == nullptr) {
        state.fight = std::make_unique<Zombie>();
    }
}

EntityType Zombie::getType() const noexcept { return EntityType::ZOMBIE; }
