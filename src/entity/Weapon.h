#ifndef TPOHB_WEAPON_H
#define TPOHB_WEAPON_H

#include "Entity.h"
#include "AnimatedEntity.h"

class Weapon : public AnimatedEntity {

    SDL_Texture *playerTexture;

protected:
    Weapon(SDL_Texture *texture, SDL_Texture *playerTexture) : AnimatedEntity(texture, 2, true) {
        this->playerTexture = playerTexture;
        hasCollision = true;
    }

public:
    int damage = 0;

    virtual void renderOnPlayer(GameState &state, Vec position);

    ~Weapon() override {
        SDL_DestroyTexture(playerTexture);
        playerTexture = nullptr;
    }

};

#endif //TPOHB_WEAPON_H
