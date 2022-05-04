#include "Player.h"
#include "../Game.h"

void Player::setDirection(int dx, int dy) {
    this->direction = Vec(dx, dy);
}

void Player::updateState(GameState &state) {
}

void Player::render(GameState &state, Vec position) {
    AnimatedEntity::render(state, position);
    if (state.weapon != nullptr) {
        state.weapon->syncWith(*this);
        state.weapon->renderOnPlayer(state, state.playerPosition);
    }
}

Vec Player::getDirection() {
    return direction;
}

void Player::onTurn(GameState & state) {
    state.playerPosition = getNextPosition(state.playerPosition);
    setDirection(0, 0);
}
