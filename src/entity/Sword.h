#ifndef TPOHB_SWORD_H
#define TPOHB_SWORD_H

#include "../GameState.h"
#include "Weapon.h"

class Sword : public Weapon {
  public:
    Sword();

    int getDamage() override;

    EntityType getType() const noexcept override;
};

#endif // TPOHB_SWORD_H
