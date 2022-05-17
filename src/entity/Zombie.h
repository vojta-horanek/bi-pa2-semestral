#ifndef TPOHB_ZOMBIE_H
#define TPOHB_ZOMBIE_H

#include "Monster.h"

class Zombie : public Monster {
  public:
    Zombie();

    int getDamage() override;

    int getMaxHealth() override;

    EntityType getType() const noexcept override;
};

#endif // TPOHB_ZOMBIE_H
