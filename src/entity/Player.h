#ifndef TPOHB_PLAYER_H
#define TPOHB_PLAYER_H

#include "../GameState.h"
#include "../render/Texture.h"
#include "AnimatedEntity.h"
#include "MovingEntity.h"
#include <SDL2/SDL.h>

class Player : public MovingEntity {
  private:
    Vec m_Direction;

  public:
    Vec getNextPosition(Vec currentPosition) const;

    explicit Player();

    void setDirection(int dx, int dy);

    Vec getDirection();

    void render(GameState &state, Vec position) override;

    void onTurn(GameState &state, MapSection &section) override;

    void onFightBegin();

    void onFightEnd();
};

#endif // TPOHB_PLAYER_H
