#ifndef TPOHB_ENTITY_H
#define TPOHB_ENTITY_H

#include "../Vec.h"
#include "../GameState.h"
#include "../Texture.h"
#include <SDL2/SDL.h>

class Entity {

protected:
    SDL_Texture *texture;

public:
    bool hasCollision = false;
    bool removeOnNextRender = false;

    explicit Entity(SDL_Texture *texture) : texture(texture) {}

    virtual ~Entity() {
        SDL_DestroyTexture(texture);
        texture = nullptr;
    }

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
