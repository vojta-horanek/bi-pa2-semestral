#ifndef TPOHB_APPLE_H
#define TPOHB_APPLE_H

#include "PickupEntity.h"
#include "../GameState.h"

class Apple : public PickupEntity {
public:
    Apple();

    void onPickup(GameState &state) override;
};

#endif //TPOHB_APPLE_H
