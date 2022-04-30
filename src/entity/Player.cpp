#include "Player.h"
#include "../Game.h"

void Player::setDirection(int dx, int dy) {
    this->direction = Vec(dx, dy);
}

void Player::updateState(GameState &state) {
    state.playerPosition = getNextPosition(state.playerPosition);

    // TODO Improve performance
    if (state.weapon != nullptr) {
        texture = Texture::create("resources/bitmaps/player-sword.bmp", true);
    } else {
        texture = Texture::create("resources/bitmaps/player.bmp", true);
    }

    if (!direction.isOrigin()) {
        state.turnFinished = true;
    }

    setDirection(0, 0);
}
