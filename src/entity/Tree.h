#ifndef TPOHB_TREE_H
#define TPOHB_TREE_H


#include "Entity.h"
#include "../Texture.h"

class Tree : public Entity {

public:
    Tree() : Entity(Texture("resources/bitmaps/tree-w.bmp", true)) {
        hasCollision = true;
    }

};


#endif //TPOHB_TREE_H
