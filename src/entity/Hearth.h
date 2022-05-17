#ifndef TPOHB_HEARTH_H
#define TPOHB_HEARTH_H

#include "../EntityType.h"
#include "PickupEntity.h"

class Hearth : public PickupEntity {
  public:
    Hearth();

    EntityType getType() const noexcept override;

    void onPickup(GameState &state) override;
};

#endif // TPOHB_HEARTH_H
