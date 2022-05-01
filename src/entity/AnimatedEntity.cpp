#include "AnimatedEntity.h"

#include <cassert>

void AnimatedEntity::render(GameState &state, Vec position) {
    updateState(state);
    nextAnimatedRender(texture, position);
}

void AnimatedEntity::nextAnimatedRender(SDL_Texture * texture, Vec position) {
    // If this entity is not synchronized, it handles the animation frames itself
    if (!synchronized) {
        if (delay >= speed) {
            delay = 0;
            frame = (frame + 1) % frameCount;
        } else {
            delay++;
        }
    }

    Texture::renderBlock(texture, position, frame);
}

void AnimatedEntity::syncWith(AnimatedEntity &other) {
    assert(other.frameCount == frameCount);
    assert(synchronized);
    this->frame = other.frame;
}
