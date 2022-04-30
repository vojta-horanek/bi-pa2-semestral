#ifndef TPOHB_SWORD_H
#define TPOHB_SWORD_H


#include "Entity.h"
#include "../GameState.h"

class Sword : public Entity {

public:
    Sword() : Entity(Texture::create("resources/bitmaps/sword.bmp", true)) {
        hasCollision = true;
    }

    bool onCollision(GameState &state) override {
        removeOnNextRender = true;
        state.weapon = std::make_unique<Sword>();
        return false;
    }

};


#endif //TPOHB_SWORD_H
