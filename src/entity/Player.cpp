#include "Player.h"
#include "../Game.h"
#include "../render/Vec.h"
#include "../resources/strings/Paths.h"

Player::Player()
    : MovingEntity(Texture(Paths::Bitmaps::player_anim, true), 2) {}

void Player::setDirection(int dx, int dy) {
    m_Direction.x = dx;
    m_Direction.y = dy;
}

void Player::render(GameState &state, Vec position) {
    AnimatedEntity::render(state, position);
    if (state.m_Weapon != nullptr) {
        state.m_Weapon->syncWith(*this);
        state.m_Weapon->m_TextureScale = m_TextureScale;
        state.m_Weapon->renderOnPlayer(state, position);
    }
}

Vec Player::getDirection() { return m_Direction; }

void Player::onTurn(GameState &state, MapSection &section) {
    state.m_PlayerPosition = getNextPosition(state.m_PlayerPosition);
    setDirection(0, 0);
}

Vec Player::getNextPosition(Vec currentPosition) const {
    return currentPosition + m_Direction;
}

void Player::onFightBegin() { m_TextureScale = 2; }

void Player::onFightEnd() {
    m_TextureScale = 1;
    resetAlpha();
}
