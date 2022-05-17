#include "AnimatedEntity.h"

#include <cassert>

AnimatedEntity::AnimatedEntity(Texture texture, int frameCount,
                               bool synchronized, int speed)
    : Entity(texture), m_Speed(speed), m_FrameCount(frameCount),
      m_Synchronized(synchronized) {}

AnimatedEntity::AnimatedEntity(Texture texture, int frameCount)
    : Entity(texture), m_FrameCount(frameCount) {}

void AnimatedEntity::render(GameState &state, Vec position) {
    nextAnimatedRender(m_Texture, position);
}

void AnimatedEntity::nextAnimatedRender(Texture &texture, Vec position) {
    // If this entity is not synchronized, it handles the animation frames
    // itself
    if (!m_Synchronized) {
        if (m_Delay >= m_Speed) {
            m_Delay = 0;
            m_Frame = (m_Frame + 1) % m_FrameCount;
        } else {
            m_Delay++;
        }
    }

    if (m_FadingOut) {
        texture.setAlpha(m_Alpha);
        m_Alpha -= 5;
    }
    texture.renderBlockWithOffset(position, m_Frame, m_TextureScale);
}

void AnimatedEntity::syncWith(AnimatedEntity &other) {
    assert(other.m_FrameCount == m_FrameCount);
    m_Synchronized = true;
    m_Frame = other.m_Frame;
}

void AnimatedEntity::unSync() {
    m_Synchronized = false;
    m_Frame = 0;
}

void AnimatedEntity::onCollision(GameState &state) {
    Entity::onCollision(state);
}

void AnimatedEntity::fadeOut() {
    m_FadingOut = true;
    m_Texture.setBlendMode(true);
}

bool AnimatedEntity::isFadeOut() const { return m_FadingOut && m_Alpha <= 0; }

void AnimatedEntity::resetAlpha() {
    m_FadingOut = false;
    m_Alpha = 255;
    m_Texture.setAlpha(m_Alpha);
}
