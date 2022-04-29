#ifndef TPOHB_PLAYER_H
#define TPOHB_PLAYER_H

#include "Entity.h"
#include <SDL2/SDL.h>
#include "../GameState.h"
#include "../Texture.h"

class Player : public Entity {
private:
    Vec direction;
public:

    explicit Player() :
            Entity(Texture::create("resources/bitmaps/player.bmp", true)) {}

    void setDirection(int dx, int dy);

    void updateState(GameState &state) override;

    void render(GameState &state) override;
};


#endif //TPOHB_PLAYER_H
