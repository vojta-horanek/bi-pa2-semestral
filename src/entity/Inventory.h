#ifndef TPOHB_INVENTORY_H
#define TPOHB_INVENTORY_H

#include "Entity.h"

class Inventory : public Entity {

private:
    void renderBackground(Vec position);
    size_t maxWidth;

public:

    explicit Inventory(size_t maxWidth) : Entity(Texture::create("resources/bitmaps/inventory.bmp")) {
        this->maxWidth = maxWidth;
    }

    void render(GameState &state, Vec position) override;


};


#endif //TPOHB_INVENTORY_H
