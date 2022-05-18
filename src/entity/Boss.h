#ifndef TPOHB_BOSS_H
#define TPOHB_BOSS_H


#include "Monster.h"

class Boss : public Monster {
public:
    Boss();

    int getDamage() override;

    int getMaxHealth() override;

    EntityType getType() const noexcept override;
};


#endif //TPOHB_BOSS_H
