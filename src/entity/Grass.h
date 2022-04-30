#ifndef TPOHB_GRASS_H
#define TPOHB_GRASS_H

#include "Entity.h"

class Grass : public Entity {

public:
    Grass() : Entity(Texture::create("resources/bitmaps/grass.bmp")) {

    }
};


#endif //TPOHB_GRASS_H
