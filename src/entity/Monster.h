#ifndef TPOHB_MONSTER_H
#define TPOHB_MONSTER_H


#include "MovingEntity.h"
#include "../Texture.h"

/**
 * A base class for a monster. A monster is something that follows the player
 */
class Monster : public MovingEntity {
public:
    int currentHealth = 0;

    explicit Monster(Texture texture);

    explicit Monster(Texture texture,
                     int animationFrameCount,
                     bool animationSynchronized = false,
                     int animationSpeed = 15);

    void onTurn(GameState &state, MapSection &section) override;

    virtual void onFight(GameState &state) = 0;

    virtual int getDamage() = 0;

    virtual int getMaxHealth() = 0;
};


#endif //TPOHB_MONSTER_H
