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
    bool hasCollision = false;
    bool removeOnNextTurn = false;

    Entity() : texture(Texture()) {}

    explicit Entity(Texture texture) : texture(texture) {}

    virtual ~Entity() = default;

    // A default implementation of the loop method draws the texture at the current position of this entity
    virtual void render(GameState &state, Vec position);

    virtual void updateState(GameState &state) {}

    /**
     *
     * @param state
     * @return true if the collision should block the player, false otherwise
     */
    virtual bool onCollision(GameState &state) {
        return hasCollision;
    }
};


#endif //TPOHB_ENTITY_H
