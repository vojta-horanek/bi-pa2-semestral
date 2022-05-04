#ifndef TPOHB_APPLE_H
#define TPOHB_APPLE_H

#include "Entity.h"
#include "../GameState.h"

class Apple : public Entity {

public:
    Apple() : Entity(Texture("resources/bitmaps/apple.bmp", true)) {
        hasCollision = true;
    }

    bool onCollision(GameState &state) override {
        removeOnNextTurn = true;
        state.inventory.emplace_back(new Apple());
        return false;
    }
};

#endif //TPOHB_APPLE_H
