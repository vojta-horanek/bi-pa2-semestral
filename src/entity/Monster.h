#ifndef TPOHB_MONSTER_H
#define TPOHB_MONSTER_H

#include "../Texture.h"
#include "MovingEntity.h"

/**
 * A base class for a monster. A monster is something that follows the player
 * and can attack
 */
class Monster : public MovingEntity {
  public:
    int currentHealth = 0;
    int health = 0;

    explicit Monster(Texture texture);

    explicit Monster(Texture texture, int animationFrameCount,
                     bool animationSynchronized = false,
                     int animationSpeed = 15);

    void onTurn(GameState &state, MapSection &section) override;

    bool onFight(GameState &state);

    virtual int getDamage() = 0;

    virtual int getMaxHealth() = 0;

    void onFightBegin();

    void onFightEnd();
};

#endif // TPOHB_MONSTER_H
