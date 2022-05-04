#include "Entity.h"

void Entity::render(GameState &state, Vec position) {
    updateState(state);
    texture.renderBlock(position);
}

bool Entity::onCollision(GameState &state) {
    return hasCollision;
}

void Entity::updateState(GameState &state) {}

Entity::Entity(Texture texture) : texture(texture) {}

Entity::Entity() : texture(Texture()) {}
