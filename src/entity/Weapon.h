#ifndef TPOHB_WEAPON_H
#define TPOHB_WEAPON_H

#include "../GameState.h"
#include "Entity.h"
#include "PickupEntity.h"

class Weapon : public PickupEntity {

    Texture playerTexture;

  protected:
    Weapon(Texture texture, Texture playerTexture);

  public:
    virtual ~Weapon();
    virtual int getDamage() = 0;

    void onPickup(GameState &state) override;

    virtual void renderOnPlayer(GameState &state, Vec position);

    void onFightEnd();
};

#endif // TPOHB_WEAPON_H
