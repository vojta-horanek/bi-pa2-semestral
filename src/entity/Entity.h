#ifndef TPOHB_ENTITY_H
#define TPOHB_ENTITY_H

#include "../EntityType.h"
#include "../GameState.h"
#include "../Texture.h"
#include "../Vec.h"
#include <iostream>

class Entity {

  protected:
    Texture texture;

  public:
    enum class Collision { NONE, SOFT, HARD };

    Collision collisionType = Collision::NONE;

    bool removeOnNextTurn = false;

    Entity();

    explicit Entity(Texture texture);

    virtual ~Entity() = default;

    // A default implementation of the loop method draws the texture at the
    // current position of this entity
    virtual void render(GameState &state, Vec position);

    virtual void render(Vec position);

    virtual void updateState(GameState &state);

    virtual void onCollision(GameState &state);

    virtual EntityType getType() const noexcept;
};

#endif // TPOHB_ENTITY_H
