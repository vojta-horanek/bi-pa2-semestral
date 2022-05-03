#ifndef TPOHB_WEAPON_H
#define TPOHB_WEAPON_H

#include "Entity.h"
#include "AnimatedEntity.h"

class Weapon : public AnimatedEntity {

    Texture playerTexture;

protected:
    Weapon(Texture texture, Texture playerTexture) :
            AnimatedEntity(std::move(texture), 2, true),
            playerTexture(std::move(playerTexture)) {
        hasCollision = true;
    }

public:
    int damage = 0;

    virtual void renderOnPlayer(GameState &state, Vec position);
};

#endif //TPOHB_WEAPON_H
