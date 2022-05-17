
#ifndef TPOHB_PICKUPENTITY_H
#define TPOHB_PICKUPENTITY_H

#include "../GameState.h"
#include "../render/Texture.h"
#include "AnimatedEntity.h"

class PickupEntity : public AnimatedEntity {
  private:
    void onCollision(GameState &state) override;

    static const int s_DefaultAnimationSpeed = 25;

  public:
    explicit PickupEntity(Texture texture);

    PickupEntity(Texture texture, int frameCount, bool synchronized = false,
                 int speed = s_DefaultAnimationSpeed);

    virtual void onPickup(GameState &state);
};

#endif // TPOHB_PICKUPENTITY_H
