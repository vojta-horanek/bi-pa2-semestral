#ifndef TPOHB_GRASS_H
#define TPOHB_GRASS_H

#include "Entity.h"

class Grass : public Entity {
  public:
    Grass();

    EntityType getType() const noexcept override;
};

#endif // TPOHB_GRASS_H
