#ifndef TPOHB_SWORD_H
#define TPOHB_SWORD_H


#include "../GameState.h"
#include "Weapon.h"

class Sword : public Weapon {

public:
    Sword() : Weapon(Texture("resources/bitmaps/sword.bmp", true),
                     Texture("resources/bitmaps/player-sword.bmp", true)) {
        damage = 15;
    }

    bool onCollision(GameState &state) override;

};


#endif //TPOHB_SWORD_H
