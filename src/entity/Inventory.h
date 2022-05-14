#ifndef TPOHB_INVENTORY_H
#define TPOHB_INVENTORY_H

#include "Entity.h"

class Inventory : public Entity {

  private:
    size_t maxWidth;

  public:
    explicit Inventory(size_t maxWidth);

    void render(GameState &state, Vec position) override;
};

#endif // TPOHB_INVENTORY_H
