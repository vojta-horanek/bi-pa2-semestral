#ifndef TPOHB_WEAPON_H
#define TPOHB_WEAPON_H

#include "Entity.h"
#include "../GameState.h"
#include "AnimatedEntity.h"

class Weapon : public AnimatedEntity {

    Texture playerTexture;

protected:
    Weapon(Texture texture, Texture playerTexture);

public:
    virtual int getDamage() = 0;

    virtual void renderOnPlayer(GameState &state, Vec position);
};

#endif //TPOHB_WEAPON_H
