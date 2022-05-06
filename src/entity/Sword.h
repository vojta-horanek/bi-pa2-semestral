#ifndef TPOHB_SWORD_H
#define TPOHB_SWORD_H


#include "../GameState.h"
#include "Weapon.h"

class Sword : public Weapon {
public:
    Sword();

    void onCollision(GameState &state) override;
    int getDamage() override;
};


#endif //TPOHB_SWORD_H
