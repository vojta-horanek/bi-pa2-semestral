#ifndef TPOHB_DIRT_H
#define TPOHB_DIRT_H

#include "Entity.h"

class Dirt : public Entity {
  public:
    Dirt();

    EntityType getType() const noexcept override;
};

#endif // TPOHB_DIRT_H
