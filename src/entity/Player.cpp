#include "Player.h"
#include "../Game.h"
#include "../resources/strings/Paths.h"
#include "../Vec.h"

Player::Player() : MovingEntity(Texture(Paths::Bitmaps::player_anim, true), 2) {}

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

void Player::onTurn(GameState &state, MapSection &section) {
    state.playerPosition = getNextPosition(state.playerPosition);
    setDirection(0, 0);
}

Vec Player::getNextPosition(Vec currentPosition) const {
    return currentPosition + direction;
}
