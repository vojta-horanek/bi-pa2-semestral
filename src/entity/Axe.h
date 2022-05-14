#ifndef TPOHB_AXE_H
#define TPOHB_AXE_H

#include "../Texture.h"
#include "Weapon.h"

class Axe : public Weapon {

  public:
    Axe();

    void onPickup(GameState &state) override;
    int getDamage() override;

    EntityType getType() const noexcept override;
};

#endif // TPOHB_AXE_H
