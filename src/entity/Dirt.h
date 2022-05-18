#ifndef TPOHB_DIRT_H
#define TPOHB_DIRT_H

#include "BlockEntity.h"

class Dirt : public BlockEntity {
  public:
    Dirt();

    EntityType getType() const noexcept override;
};

#endif // TPOHB_DIRT_H
