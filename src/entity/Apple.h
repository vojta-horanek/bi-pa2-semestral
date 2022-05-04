#ifndef TPOHB_APPLE_H
#define TPOHB_APPLE_H

#include "Entity.h"
#include "../GameState.h"

class Apple : public Entity {
public:
    Apple();

    bool onCollision(GameState &state) override;
};

#endif //TPOHB_APPLE_H
