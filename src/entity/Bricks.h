#ifndef TPOHB_BRICKS_H
#define TPOHB_BRICKS_H

#include "BlockEntity.h"

class Bricks : public BlockEntity {
  public:
    Bricks();

    EntityType getType() const noexcept override;
};

#endif // TPOHB_BRICKS_H
