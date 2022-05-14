#ifndef TPOHB_APPLE_H
#define TPOHB_APPLE_H

#include "../GameState.h"
#include "PickupEntity.h"

class Apple : public PickupEntity {
  public:
    Apple();

    void onPickup(GameState &state) override;

    EntityType getType() const noexcept override;
};

#endif // TPOHB_APPLE_H
