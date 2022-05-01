#ifndef TPOHB_ANIMATEDENTITY_H
#define TPOHB_ANIMATEDENTITY_H


#include "Entity.h"

class AnimatedEntity : public Entity {
    int delay = 0;
    int speed;
    int frameCount;
    bool synchronized;

protected:

    int frame = 0;

    AnimatedEntity(SDL_Texture *texture,
                   int frameCount,
                   bool synchronized = false,
                   int speed = 15) :
            Entity(texture),
            frameCount(frameCount),
            speed(speed),
            synchronized(synchronized) {
    }

    void nextAnimatedRender(SDL_Texture *texture, Vec position);

public:
    void render(GameState &state, Vec position) override;

    /**
     * Synchronizes this animated entity with another one.
     * Makes it so both entities are currently on the same frame of their animation
     * @param other an entity to synchronize with
     */
    void syncWith(AnimatedEntity &other);
};


#endif //TPOHB_ANIMATEDENTITY_H
