#include "Player.h"
#include "../Game.h"

void Player::setDirection(int dx, int dy) {
    this->direction = Vec(dx, dy).getScaled();
}

void Player::updateState(GameState &state) {
    position += direction;
    state.playerPosition = position;
}

void Player::render(GameState &state) {

    updateState(state);

    Vec size = Texture::getAdjustedSize(texture);

    SDL_Rect dstRect;
    dstRect.w = size.x;
    dstRect.h = size.y;
    dstRect.x = position.x / 10;
    dstRect.y = position.y / 10;

    SDL_RenderCopy(Game::getRenderer(), texture, nullptr, &dstRect);
}
