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

    texture.renderBlock(position, frame);
}

void AnimatedEntity::syncWith(AnimatedEntity &other) {
    assert(other.frameCount == frameCount);
    assert(synchronized);
    this->frame = other.frame;
}

void AnimatedEntity::onCollision(GameState &state) {
    Entity::onCollision(state);
}

