
#ifndef TPOHB_PICKUPENTITY_H
#define TPOHB_PICKUPENTITY_H

#include "../GameState.h"
#include "../Texture.h"
#include "AnimatedEntity.h"

class PickupEntity : public AnimatedEntity {
  private:
    void onCollision(GameState &state) override;

  public:
    PickupEntity(Texture texture, int frameCount, bool synchronized = false,
                 int speed = 25);

    explicit PickupEntity(Texture texture);

    virtual void onPickup(GameState &state);
};

#endif // TPOHB_PICKUPENTITY_H
