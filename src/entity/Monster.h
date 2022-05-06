#ifndef TPOHB_MONSTER_H
#define TPOHB_MONSTER_H


#include "MovingEntity.h"
#include "../Texture.h"

/**
 * A base class for a monster. A monster is something that follows the player
 */
class Monster : public MovingEntity {
public:
    int currentHealth;

    explicit Monster(Texture texture);

    void onTurn(GameState &state, MapSection &section) override;

    virtual int getDamage() = 0;

    virtual int getMaxHealth() = 0;
};


#endif //TPOHB_MONSTER_H
