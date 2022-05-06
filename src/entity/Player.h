#ifndef TPOHB_PLAYER_H
#define TPOHB_PLAYER_H

#include "AnimatedEntity.h"
#include <SDL2/SDL.h>
#include "../GameState.h"
#include "../Texture.h"
#include "MovingEntity.h"

class Player : public MovingEntity {
private:
    Vec direction;
public:

    int health = 255;

    int defaultDamage = 5;

    Vec getNextPosition(Vec currentPosition) const;

    explicit Player();

    void setDirection(int dx, int dy);

    Vec getDirection();

    void updateState(GameState &state) override;

    void render(GameState &state, Vec position) override;

    void onTurn(GameState &state, MapSection &section) override;

    void onFightBegin();

    void onFightEnd();
};


#endif //TPOHB_PLAYER_H
