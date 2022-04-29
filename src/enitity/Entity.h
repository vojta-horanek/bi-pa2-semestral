#ifndef TPOHB_ENTITY_H
#define TPOHB_ENTITY_H

#include "../Vec.h"
#include "../GameState.h"
#include "../Texture.h"
#include <SDL2/SDL.h>

class Entity {

protected:
    SDL_Texture *texture;
    Vec position;

public:
    bool hasCollision = false;

    explicit Entity(SDL_Texture *texture) : texture(texture) {}

    virtual ~Entity() {
        SDL_DestroyTexture(texture);
        texture = nullptr;
    }

    // A default implementation of the render method draws the texture at the current position of this entity
    virtual void render(GameState &state);

    virtual void updateState(GameState &state) {}

    void setPosition(Vec _position) {
        position = _position;
    }

    void setPosition(int x, int y) {
        position.x = x;
        position.y = y;
    }

};


#endif //TPOHB_ENTITY_H
