#ifndef TPOHB_MOVINGENTITY_H
#define TPOHB_MOVINGENTITY_H


#include "AnimatedEntity.h"

class MovingEntity : public AnimatedEntity {
public:

    Vec position;

    MovingEntity(Texture texture,
                 int animationFrameCount,
                 bool animationSynchronized = false,
                 int animationSpeed = 15);

    explicit MovingEntity(Texture texture);

    virtual void onTurn(GameState & state);
};


#endif //TPOHB_MOVINGENTITY_H
