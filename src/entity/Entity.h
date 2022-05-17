#ifndef TPOHB_ENTITY_H
#define TPOHB_ENTITY_H

#include "../EntityType.h"
#include "../GameState.h"
#include "../render/Texture.h"
#include "../render/Vec.h"
#include <iostream>

/**
 * A base class for all entities which are render to the screen
 */
class Entity {

  public:
    /**
     * Type of entity collision
     * NONE -> collision is ignored
     * SOFT -> collision triggers an onCollision method
     * HARD -> triggers onCollision & blocks player movement
     */
    enum class Collision { NONE, SOFT, HARD };

    /**
     * Type of the collision for this entity
     */
    Collision m_CollisionType = Collision::NONE;

    /**
     * If this flag is set to true, this entity will get removed from the map on
     * next turn of the game
     */
    bool m_RemoveOnNextTurn = false;

    Entity();

    explicit Entity(Texture texture);

    virtual ~Entity() = default;

    /**
     * A default implementation of the render method draws the m_Texture at the
     * current position of this entity
     * @param state current state of the game
     * @param position position to render at
     */
    virtual void render(GameState &state, Vec position);

    /**
     * A function that is called on collision with the entity
     * Default implementation does not do anything.
     * @param state current state of the game
     */
    virtual void onCollision(GameState &state);

    /**
     *
     * @return a type of the entity
     */
    virtual EntityType getType() const noexcept;

  protected:
    /**
     * A m_Texture of this entity
     */
    Texture m_Texture;
};

#endif // TPOHB_ENTITY_H
