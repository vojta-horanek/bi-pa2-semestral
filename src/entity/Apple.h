#ifndef TPOHB_APPLE_H
#define TPOHB_APPLE_H

#include "../GameState.h"
#include "PickupEntity.h"

class Apple : public PickupEntity {
  public:
    Apple();

    EntityType getType() const noexcept override;

    void onPickup(GameState &state) override;
};

#endif // TPOHB_APPLE_H
