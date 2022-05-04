#ifndef TPOHB_AXE_H
#define TPOHB_AXE_H


#include "../Texture.h"
#include "Weapon.h"

class Axe : public Weapon {

public:
    Axe();

    bool onCollision(GameState &state) override;
};


#endif //TPOHB_AXE_H
