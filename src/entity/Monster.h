#ifndef TPOHB_MONSTER_H
#define TPOHB_MONSTER_H


#include "MovingEntity.h"

/**
 * A base class for a monster. A monster is something that follows the player
 */
class Monster : public MovingEntity {
public:
    Monster();

    void onTurn(GameState &state) override;
};


#endif //TPOHB_MONSTER_H
