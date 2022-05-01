#ifndef TPOHB_AXE_H
#define TPOHB_AXE_H


#include "../Texture.h"
#include "Weapon.h"

class Axe : public Weapon {

public:
    Axe() : Weapon(Texture::create("resources/bitmaps/axe.bmp", true),
                   Texture::create("resources/bitmaps/player-axe.bmp", true)) {
        damage = 10;
    }

    bool onCollision(GameState &state) override;

};


#endif //TPOHB_AXE_H
