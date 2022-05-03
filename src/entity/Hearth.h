#ifndef TPOHB_HEARTH_H
#define TPOHB_HEARTH_H

#include "Entity.h"

class Hearth : public Entity {

public:
    Hearth() : Entity(Texture("resources/bitmaps/hearth.bmp", true)) {

    }

};

#endif //TPOHB_HEARTH_H
