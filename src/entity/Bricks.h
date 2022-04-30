#ifndef TPOHB_BRICKS_H
#define TPOHB_BRICKS_H


#include "Entity.h"

class Bricks : public Entity {
public:
    Bricks() : Entity(Texture::create("resources/bitmaps/bricks.bmp")) {
        hasCollision = true;
    }

};


#endif //TPOHB_BRICKS_H
