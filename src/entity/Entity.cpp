#include "Entity.h"

void Entity::render(GameState &state, Vec position) {
    updateState(state);
    texture.renderBlock(position);
}
