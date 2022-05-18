#ifndef TPOHB_GOLDENAPPLE_H
#define TPOHB_GOLDENAPPLE_H

#include "../GameState.h"
#include "PickupEntity.h"

class GoldenApple : public PickupEntity {
  public:
    GoldenApple();

    EntityType getType() const noexcept override;
};

#endif // TPOHB_GOLDENAPPLE_H
