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

    AnimatedEntity(Texture texture, int frameCount, bool synchronized = false, int speed = 15);

    void nextAnimatedRender(Texture &texture, Vec position);

public:

    int scale = 1;

    void render(GameState &state, Vec position) override;

    /**
     * Synchronizes this animated entity with another one.
     * Makes it so both entities are currently on the same frame of their animation
     * @param other an entity to synchronize with
     */
    void syncWith(AnimatedEntity &other);

    void onCollision(GameState &state) override;
};


#endif //TPOHB_ANIMATEDENTITY_H
