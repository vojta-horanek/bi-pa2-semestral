#include "Entity.h"

Entity::Entity(Texture texture) : m_Texture(texture) {}

Entity::Entity() : m_Texture(Texture()) {}

void Entity::render(GameState &state, Vec position) {
    m_Texture.renderBlock(position);
}

void Entity::onCollision(GameState &state) {}

EntityType Entity::getType() const noexcept { return EntityType::VOID; }