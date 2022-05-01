#ifndef TPOHB_PLAYER_H
#define TPOHB_PLAYER_H

#include "AnimatedEntity.h"
#include <SDL2/SDL.h>
#include "../GameState.h"
#include "../Texture.h"

class Player : public AnimatedEntity {
private:
    Vec direction;
public:

    Vec getNextPosition(Vec currentPosition) const {
        return currentPosition + direction;
    }

    explicit Player() :
            AnimatedEntity(Texture::create("resources/bitmaps/player-anim.bmp", true), 2) {}

    void setDirection(int dx, int dy);
    Vec getDirection();

    void updateState(GameState &state) override;

    void render(GameState &state, Vec position) override;
};


#endif //TPOHB_PLAYER_H
