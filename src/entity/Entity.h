#ifndef TPOHB_ENTITY_H
#define TPOHB_ENTITY_H

#include "../Vec.h"
#include "../GameState.h"
#include "../Texture.h"
#include <SDL2/SDL.h>
#include <iostream>

class Entity {

protected:
    Texture texture;

public:

    enum class Collision {
        NONE, SOFT, HARD
    };

    Collision collisionType = Collision::NONE;

    bool removeOnNextTurn = false;

    Entity();

    explicit Entity(Texture texture);

    virtual ~Entity() = default;

    // A default implementation of the loop method draws the texture at the current position of this entity
    virtual void render(GameState &state, Vec position);

    virtual void updateState(GameState &state);

    virtual void onCollision(GameState &state);
};


#endif //TPOHB_ENTITY_H
