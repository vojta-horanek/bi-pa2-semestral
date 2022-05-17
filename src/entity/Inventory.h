#ifndef TPOHB_INVENTORY_H
#define TPOHB_INVENTORY_H

#include "Entity.h"

class Inventory : public Entity {
  public:
    explicit Inventory(int maxItems);

    void render(GameState &state, Vec position) override;

  private:
    int m_MaxItems;
};

#endif // TPOHB_INVENTORY_H
