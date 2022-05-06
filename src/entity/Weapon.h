#ifndef TPOHB_WEAPON_H
#define TPOHB_WEAPON_H

#include "Entity.h"
#include "../GameState.h"
#include "PickupEntity.h"

class Weapon : public PickupEntity {

    Texture playerTexture;

protected:
    Weapon(Texture texture, Texture playerTexture);

public:
    virtual int getDamage() = 0;

    void onPickup(GameState &state) override;

    virtual void renderOnPlayer(GameState &state, Vec position);
};

#endif //TPOHB_WEAPON_H
