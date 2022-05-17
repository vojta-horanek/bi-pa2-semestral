#ifndef TPOHB_MOVINGENTITY_H
#define TPOHB_MOVINGENTITY_H

#include "../MapSection.fwd.h"
#include "AnimatedEntity.h"

class MovingEntity : public AnimatedEntity {
  public:
    Vec m_Position;

    explicit MovingEntity(Texture texture);

    MovingEntity(Texture texture, int animationFrameCount);

    MovingEntity(Texture texture, int animationFrameCount,
                 bool animationSynchronized, int animationSpeed);

    virtual void onTurn(GameState &state, MapSection &section);
};

#endif // TPOHB_MOVINGENTITY_H
