#include "Entity.h"

Entity::Entity(Texture texture) : texture(texture) {}

Entity::Entity() : texture(Texture()) {}

void Entity::render(GameState &state, Vec position) {
    updateState(state);
    texture.renderBlock(position);
}

void Entity::render(Vec position) { texture.renderBlock(position); }

void Entity::onCollision(GameState &state) {}

void Entity::updateState(GameState &state) {}

EntityType Entity::getType() const noexcept { return EntityType::INVALID; }