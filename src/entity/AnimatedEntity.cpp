#include "AnimatedEntity.h"

#include <cassert>

AnimatedEntity::AnimatedEntity(Texture texture, int frameCount, bool synchronized, int speed) :
        Entity(texture),
        speed(speed),
        frameCount(frameCount),
        synchronized(synchronized) {
}

void AnimatedEntity::render(GameState &state, Vec position) {
    updateState(state);
    nextAnimatedRender(texture, position);
}

void AnimatedEntity::nextAnimatedRender(Texture &texture, Vec position) {
    // If this entity is not synchronized, it handles the animation frames itself
    if (!synchronized) {
        if (delay >= speed) {
            delay = 0;
            frame = (frame + 1) % frameCount;
        } else {
            delay++;
        }
    }

    if (fadingOut) {
        texture.setAlpha(alpha);
        alpha -= 5;
    }
    texture.renderBlockWithOffset(position, frame, scale);
}

void AnimatedEntity::syncWith(AnimatedEntity &other) {
    assert(other.frameCount == frameCount);
    this->synchronized = true;
    this->frame = other.frame;
}

void AnimatedEntity::onCollision(GameState &state) {
    Entity::onCollision(state);
}

void AnimatedEntity::fadeOut() {
    fadingOut = true;
    texture.setBlendMode(true);
}

bool AnimatedEntity::isFadeOut() const {
    return fadingOut && alpha <= 0;
}

void AnimatedEntity::resetAlpha() {
    fadingOut = false;
    alpha = 255;
    texture.setAlpha(alpha);
}

